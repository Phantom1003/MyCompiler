from llvmlite import ir
from random import randint
import llvmlite.binding as llvm
from ctypes import *
from ctypes import CFUNCTYPE, c_double, c_int32
from symbol_table import SymTab
from CompilerError import *


type_t = {
    "INTEGER": ir.IntType(32),
    "REAL": ir.DoubleType(),
    "CHAR": ir.IntType(8),
    "BOOLEAN": ir.IntType(1),
}

ir_type_t = {
    "INTEGER": ir.IntType(32)(0).type,
    "REAL": ir.DoubleType()(0).type,
    "CHAR": ir.IntType(8)(0).type,
    "BOOLEAN": ir.IntType(1)(0).type,
}


class Codegen:
    def __init__(self, root, debug=False):
        self.root = root
        self.debug = debug
        self.symbol_table = SymTab()
        self.module = ir.Module(root.children[0].children[1].name)
        self.caselist = []
        self.default = None

    def codegen(self):
        self._codegen(self.root)
        llvm_ir = self.module.__repr__()
        llvm.initialize()
        llvm.initialize_native_target()
        llvm.initialize_native_asmprinter()
        self.mod = llvm.parse_assembly(llvm_ir)
        # mod.verify()
        target = llvm.Target.from_default_triple()
        target_machine = target.create_target_machine()
        asm = target_machine.emit_assembly(self.mod)
        return asm

    def irshow(self):
        self._codegen(self.root)
        return self.module


    def crun(self, func, args, ctype=c_int32):
        target = llvm.Target.from_default_triple()
        target_machine = target.create_target_machine()
        # And an execution engine with an empty backing module
        backing_mod = llvm.parse_assembly("")
        engine = llvm.create_mcjit_compiler(backing_mod, target_machine)
        engine.add_module(self.mod)
        engine.finalize_object()
        engine.run_static_constructors()
        func_ptr = engine.get_function_address(func)
        cfunc = CFUNCTYPE(ctype)(func_ptr)

        res = cfunc(*args)

        return res

    def _codegen(self, node):
        method = node.type
        return getattr(self, method)(node)


    def info(self, node):
        print("Debug: Node { %s, %s, %s}" % (node.type, node.name, node.children))

    def program(self, node):
        self.symbol_table.create_tab()
        self.main_type = ir.FunctionType(ir.VoidType(), ())
        self.main_func = ir.Function(self.module, self.main_type, name=node.children[0].children[1].name)
        self.block = self.main_func.append_basic_block('main')
        self.builder = ir.IRBuilder(self.block)
        self._codegen(node.children[1])
        self.builder.ret_void()
        # print(self.module)

    def routine(self, node):
        for n in node.children:
            self._codegen(n)

    def subroutine(self, node):
        for n in node.children:
            self._codegen(n)

    def routine_head(self, node):
        for n in node.children:
            self._codegen(n)

    def label_part(self, node):
        pass

    def const_part(self, node):
        if len(node.children) < 2:
            return
        else:
            self._codegen(node.children[1])

    def const_expr_list(self, node):
        paralist = node.children[-4:]
        name = paralist[0].name
        const_v = self._codegen(paralist[2])
        # addr = self.builder.alloca(const_v.type)
        # self.builder.store(const_v, addr)
        # self.symbol_table.insert([name, addr])

        if len(self.symbol_table.tables) > 1:
            addr = self.builder.alloca(const_v.type)
            self.builder.store(const_v, addr)
        else:
            addr = ir.GlobalVariable(self.module, const_v.type, name)
            try:
                if const_v.type.intrinsic_name == 'i32':
                    addr.initializer = ir.Constant(ir.IntType(32), int(const_v.constant))
                elif const_v.type.intrinsic_name == 'f64':
                    addr.initializer = ir.Constant(ir.DoubleType(), float(const_v.constant))
                elif const_v.type.intrinsic_name == 'i8':
                    addr.initializer = ir.Constant(ir.IntType(8), int(const_v.constant))
            except AttributeError:
                addr.initializer = const_v
            addr.global_constant = True

        self.symbol_table.insert([name, addr])

        if len(node.children) == 5:
            self._codegen(node.children[0])

    def const_value(self, node):
        t = node.children[0].type
        value = node.children[0].name
        if t in type_t.keys():
            ir_type = type_t[t]
            if ir_type.intrinsic_name == 'i8':
                value = ord(value[1])
            const_v = ir.Constant(ir_type, value)
            return const_v
        else:
            value = bytes(value.strip('"'), encoding='utf-8').decode('unicode-escape')
            value += '\0'
            c_str = ir.Constant(ir.ArrayType(ir.IntType(8), len(value)), bytearray(value.encode("utf8")))
            return c_str

    def type_part(self, node):
        self._codegen(node.children[-1])

    def var_part(self, node):
        self._codegen(node.children[-1])

    def var_decl_list(self, node):
        for n in node.children:
            self._codegen(n)

    def type_decl_list(self, node):
        for n in node.children:
            self._codegen(n)

    def var_decl(self, node):
        namelist = self.name_list(node.children[0])
        if (node.children[2].children[0].type == "simple_type_decl"):
            ir_type = self.type_decl(node.children[2])
            for name in namelist:
                # addr = self.builder.alloca(ir_type)
                # # addr = ir.GlobalVariable(self.module, ir_type, node.children[0].children[0].name)
                # # addr.initializer = ir.Constant(ir.IntType(32), 0)
                # self.symbol_table.insert([name, addr])
                if len(self.symbol_table.tables) > 1:
                    addr = self.builder.alloca(ir_type)
                else:
                    addr = ir.GlobalVariable(self.module, ir_type, name)
                    if ir_type.intrinsic_name == 'i32':
                        addr.initializer = ir.Constant(ir.IntType(32), 0)
                    elif ir_type.intrinsic_name == 'f64':
                        addr.initializer = ir.Constant(ir.DoubleType(), 0)
                    elif ir_type.intrinsic_name == 'i8':
                        addr.initializer = ir.Constant(ir.IntType(8), 0)
                self.symbol_table.insert([name, addr])
        elif (node.children[2].children[0].type == "array_type_decl"):
            array_list = self.type_decl(node.children[2])
            array_type = ir.ArrayType(array_list[1], int(array_list[2]) + 1)  # x integers of element
            for name in namelist:
                addr = self.builder.alloca(array_type)  # pointer to array
                self.symbol_table.insert([name, addr])
        elif (node.children[2].children[0].type == "record_type_decl"):
            field_list = self.type_decl(node.children[2])
            i32 = ir.IntType(32)
            for name in namelist:
                field_body = [i32]
                count = 1
                for f in field_list[1]:
                    field_body += [f[1]]
                    index = ir.Constant(i32, count)
                    try:
                        self.symbol_table.insert([name + "." + f[0], index], 0)
                    except MultiDefinedError as error:
                        pass
                    count += 1
                str_list = ir.LiteralStructType(field_body)
                addr = self.builder.alloca(str_list)  # pointer to array
                self.symbol_table.insert([name, addr])

    def type_definition(self, node):
        name = node.children[0].name
        if (node.children[2].children[0].type == "array_type_decl"):
            array_list = self.type_decl(node.children[2])
            array_type = ir.ArrayType(array_list[1], int(array_list[2])+1)    # x integers of element
            addr = self.builder.alloca(array_type)                          # pointer to array
            self.symbol_table.insert([name, addr])
        elif (node.children[2].children[0].type == "record_type_decl"):
            field_list = self.type_decl(node.children[2])
            i32 = ir.IntType(32)
            field_body = [i32]
            count = 1
            for f in field_list[1]:
                field_body += [f[1]]
                index = ir.Constant(i32, count)
                self.symbol_table.insert([name + "." + f[0], index])
                count += 1
            str_list = ir.LiteralStructType(field_body)
            addr = self.builder.alloca(str_list)  # pointer to array
            self.symbol_table.insert([name, addr])


    def name_list(self, node):
        if len(node.children) > 1:
            namelist = self.name_list(node.children[0])
        else:
            namelist = []
        name = [node.children[-1].name]
        return namelist + name

    def type_decl(self, node):
        if node.children[0].type == "simple_type_decl":
            return self.simple_type_decl(node.children[0])
        elif node.children[0].type == "array_type_decl":
            return self.array_type_decl(node.children[0])
        elif node.children[0].type == "record_type_decl":
            return self.record_type_decl(node.children[0])

    def simple_type_decl(self, node):
        if node.children[0].type == "SYS_TYPE":
            spl_type = node.children[0].name.upper()
            ir_type = type_t[spl_type]
            return ir_type

    def array_type_decl(self, node):
        if node.children[2].children[0].children[0].name == "1":
            spl_type = node.children[5].children[0].children[0].name.upper()
            ir_type = type_t[spl_type]
            return ["array", ir_type, node.children[2].children[2].children[0].name]
        else:
            raise SplTypeError(["Cannot create array"])

    def record_type_decl(self, node):
        return ["record", self._codegen(node.children[1])]

    def field_decl_list(self, node):
        field_list = []
        for n in node.children:
            field_list +=self._codegen(n)
        return field_list

    def field_decl(self, node):
        namelist = self.name_list(node.children[0])
        ir_type = self.type_decl(node.children[2])
        field_list = []
        for name in namelist:
            field_list += [[name, ir_type]]
        return field_list

    def routine_part(self, node):
        for n in node.children:
            self._codegen(n)

    def procedure_decl(self, node):
        name, paralist = self.procedure_head(node.children[0])
        namelist = []
        ir_type_list = []
        for t in paralist:
            if t[0][0] == "var":
                for i in range(1, len(t[0])):
                    ir_type_list.append(t[1].as_pointer())
                    namelist.append(("var", t[0][i]))
            else:
                for i in range(1, len(t[0])):
                    ir_type_list.append(t[1])
                    namelist.append(("val", t[0][i]))


        func_type = ir.FunctionType(ir.VoidType(), ir_type_list)
        func = ir.Function(self.module, func_type, name=name)
        self.symbol_table.insert([name, func])
        self.symbol_table.create_tab()

        stored_builder = self.builder
        block = func.append_basic_block(name=name)
        self.builder = ir.IRBuilder(block)

        func_args = func.args
        for i in range(len(func_args)):
            if namelist[i][0] == "val":
                addr = self.builder.alloca(ir_type_list[i])
                self.builder.store(func_args[i], addr)
                self.symbol_table.insert([namelist[i][1], addr])
            if namelist[i][0] == "var":
                addr = func_args[i]
                self.symbol_table.insert([namelist[i][1], addr])

        self.subroutine(node.children[2])
        self.builder.ret_void()
        self.builder = stored_builder
        self.symbol_table.pop()

    def procedure_head(self, node):
        name = node.children[1].name
        paralist = self._codegen(node.children[2])  # [(['a'], (ir_type, spl_type))]
        return name, paralist  # name(str), paralist([(paraname_list, irtype), ..]), ret(type)

    def function_decl(self, node):
        name, paralist, ret = self.function_head(node.children[0])
        namelist = []
        ir_type_list = []
        for t in paralist:
            if t[0][0] == "var":
                for i in range(1, len(t[0])):
                    ir_type_list.append(t[1].as_pointer())
                    namelist.append(("var", t[0][i]))
            else:
                for i in range(1, len(t[0])):
                    ir_type_list.append(t[1])
                    namelist.append(("val", t[0][i]))

        ret_ir_type = type_t[node.children[0].children[-1].children[0].name.upper()]

        func_type = ir.FunctionType(ret_ir_type, ir_type_list)
        func = ir.Function(self.module, func_type, name=name)
        self.symbol_table.insert([name, func])
        self.symbol_table.create_tab()

        stored_builder = self.builder
        block = func.append_basic_block(name=name)
        self.builder = ir.IRBuilder(block)

        retaddr = self.builder.alloca(ret_ir_type)
        self.symbol_table.insert([name+"_return", retaddr])

        func_args = func.args
        for i in range(len(func_args)):
            if namelist[i][0] == "val":
                addr = self.builder.alloca(ir_type_list[i])
                self.builder.store(func_args[i], addr)
                self.symbol_table.insert([namelist[i][1], addr])
            if namelist[i][0] == "var":
                addr = func_args[i]
                self.symbol_table.insert([namelist[i][1], addr])

        self.subroutine(node.children[2])
        retval = self.builder.load(retaddr)
        self.builder.ret(retval)

        self.builder = stored_builder
        self.symbol_table.pop()

    def function_head(self, node):
        name = node.children[1].name
        paralist = self._codegen(node.children[2])  # [(['a'], (ir_type, spl_type))]
        ret = self._codegen(node.children[4])
        return name, paralist, ret  # name(str), paralist([(paraname_list, irtype), ..]), ret(type)

    def parameters(self, node):
        return self._codegen(node.children[1])

    def para_decl_list(self, node):
        if len(node.children) > 1:
            pre_list = self.para_decl_list(node.children[0])
        else:
            pre_list = []
        paralist = pre_list + [self.para_type_list(node.children[-1])]
        return paralist

    def para_type_list(self, node):  # (paraname_list, ir_type)
        paraname_list = self._codegen(node.children[0])  # val_para_list only [str, ..]
        ir_type = self._codegen(node.children[-1])
        if node.children[0].type == "var_para_list":
            paraname_list.insert(0, "var")
        else:
            paraname_list.insert(0, "val")
        return paraname_list, ir_type

    def val_para_list(self, node):
        return self._codegen(node.children[0])

    def var_para_list(self, node):
        return self._codegen(node.children[1])

    def routine_body(self, node):
        self.compound_stmt(node.children[0])

    def compound_stmt(self, node):
        self.stmt_list(node.children[1])

    def stmt_list(self, node):
        if len(node.children) > 1:
            self._codegen(node.children[0])
            self._codegen(node.children[1])
        else:
            self.epsilon(node.children[0])

    def stmt(self, node):
        self._codegen(node.children[-1])

    def non_label_stmt(self, node):
        self._codegen(node.children[0])

    def assign_stmt(self, node):
        if node.children[1].type == "ASSIGN":
            name = node.children[0].name
            lhs = self.symbol_table.find(name)['entry']
            rhs = self.expression(node.children[2])

            if type(lhs) == ir.Function:
                # self.builder.ret(rhs)
                lhs = self.symbol_table.find(name+'_return')['entry']
                self.builder.store(rhs, lhs)
            else:
                if str(lhs.type)[:-1] != str(rhs.type):
                    raise SplTypeError(["Cannot assign %s to %s" % (str(rhs.type), str(lhs.type)[:-1])])
                self.builder.store(rhs, lhs)
        elif node.children[1].type == "LB":
            name = node.children[0].name
            lhs = self.symbol_table.find(name)['entry']
            rhs = self.expression(node.children[5])
            index = self.expression(node.children[2])
            i32 = ir.IntType(32)
            i32_0 = ir.Constant(i32, 0)
            pointer_to_index = self.builder.gep(lhs, [i32_0, index])  # gets address of array[0]
            if str(pointer_to_index.type)[:-1] != str(rhs.type):
                raise SplTypeError(["Cannot assign %s to %s" % (str(rhs.type), str(pointer_to_index.type)[:-1])])
            self.builder.store(rhs, pointer_to_index)
        elif node.children[1].type == "DOT":
            name = node.children[0].name
            lhs = self.symbol_table.find(name)['entry']
            rhs = self.expression(node.children[4])
            index = node.children[2].name
            offset = self.symbol_table.find(name + "." + index)["entry"]
            i32 = ir.IntType(32)
            i32_0 = ir.Constant(i32, 0)
            pointer_to_index = self.builder.gep(lhs, [i32_0, offset])  # gets address of array[0]
            if str(pointer_to_index.type)[:-1] != str(rhs.type):
                raise SplTypeError(["Cannot assign %s to %s" % (str(rhs.type), str(pointer_to_index.type)[:-1])])
            self.builder.store(rhs, pointer_to_index)

    def proc_stmt(self, node):
        if node.children[0].type == 'READ':
            addr = self.symbol_table.find(node.children[2].children[0].name)['entry']
            python_sca = ""
            ran = str(randint(0, 0x7FFFFFFF))
            voidptr_ty = ir.IntType(8).as_pointer()
            scanf = self.module.globals.get('scanf', None)
            if not scanf:
                scanf_ty = ir.FunctionType(ir.IntType(32), [voidptr_ty], var_arg=True)
                scanf = ir.Function(self.module, scanf_ty, name="scanf")
            if addr.type.pointee.intrinsic_name == 'i32':
                python_sca = python_sca + '%d\0'
            elif addr.type.pointee.intrinsic_name == 'f64':
                python_sca = python_sca + '%f\0'
            elif addr.type.pointee.intrinsic_name == 'i8':
                python_sca = python_sca + '%c\0'
            else:
                python_sca = python_sca + '%s\0'
            fmt_sca = ir.Constant(ir.ArrayType(ir.IntType(8), len(python_sca)), bytearray(python_sca.encode("utf8")))
            global_sca = ir.GlobalVariable(self.module, fmt_sca.type, name='sca'+ran)
            global_sca.linkage = 'internal'
            global_sca.global_constant = True
            global_sca.initializer = fmt_sca
            sca_arg = self.builder.bitcast(global_sca, voidptr_ty)
            self.builder.call(scanf, [sca_arg, addr])
            self.builder.load(addr)
            return

        args = self.args_list(node.children[2])
        if node.children[0].name == 'write':
            ran = str(randint(0, 0x7FFFFFFF))
            voidptr_ty = ir.IntType(8).as_pointer()
            printf = self.module.globals.get('printf', None)
            if not printf:
                printf_ty = ir.FunctionType(ir.IntType(32), [voidptr_ty], var_arg=True)
                printf = ir.Function(self.module, printf_ty, name="printf")
            python_str = "SPL >> "
            for i in args:
                if i.type.intrinsic_name == 'i32':
                    python_str = python_str + "%d "
                elif i.type.intrinsic_name == 'f64':
                    python_str = python_str + "%f "
                else:
                    python_str = python_str + "%s "
            python_str = python_str + "\0"
            fmt_str = ir.Constant(ir.ArrayType(ir.IntType(8), len(python_str)), bytearray(python_str.encode("utf8")))
            global_fmt = ir.GlobalVariable(self.module, fmt_str.type, name='fmt'+ran)
            global_fmt.linkage = 'internal'
            global_fmt.global_constant = True
            global_fmt.initializer = fmt_str
            fmt_arg = self.builder.bitcast(global_fmt, voidptr_ty)
            self.builder.call(printf, [fmt_arg] + args)

        elif node.children[0].name == 'writeln':
            ran = str(randint(0, 0x7FFFFFFF))
            voidptr_ty = ir.IntType(8).as_pointer()
            printf = self.module.globals.get('printf', None)
            if not printf:
                printf_ty = ir.FunctionType(ir.IntType(32), [voidptr_ty], var_arg=True)
                printf = ir.Function(self.module, printf_ty, name="printf")
            python_str = "SPL >> "
            for i in args:
                if i.type.intrinsic_name == 'i32':
                    python_str = python_str + "%d "
                elif i.type.intrinsic_name == 'f64':
                    python_str = python_str + "%f "
                else:
                    python_str = python_str + "%s "
            python_str = python_str + "\n\0"
            fmt_str = ir.Constant(ir.ArrayType(ir.IntType(8), len(python_str)), bytearray(python_str.encode("utf8")))
            global_fmt = ir.GlobalVariable(self.module, fmt_str.type, name='fmt'+ran)
            global_fmt.linkage = 'internal'
            global_fmt.global_constant = True
            global_fmt.initializer = fmt_str
            fmt_arg = self.builder.bitcast(global_fmt, voidptr_ty)
            self.builder.call(printf, [fmt_arg] + args)


        else:
            args = self.args_list(node.children[2])
            func = self.symbol_table.find(node.children[0].name)["entry"]
            args_type = func.args
            for i in range(len(args_type)):
                if args_type[i].type.is_pointer:
                    args[i] = self.find_addr(node.children[2], len(args) - i - 1)
            return self.builder.call(func, args)

    def find_addr(self, node, n):
        cur = node
        for i in range(n):
            cur = cur.children[0]
        return self.symbol_table.find(cur.children[-1].children[-1].children[-1].children[-1].children[-1].name)['entry']

    def if_stmt(self, node):
        pred = self._codegen(node.children[1])
        with self.builder.if_else(pred) as (then, otherwise):
            with then:
                # stored_builder = self.builder
                # block = self.builder.append_basic_block("then_"+str(ran))
                # self.builder = ir.IRBuilder(block)
                # self.builder.goto_block(then)
                self._codegen(node.children[3])
                # self.builder = stored_builder
            with otherwise:
                # stored_builder = self.builder
                # block = self.builder.append_basic_block("else_" + str(ran))
                # self.builder = ir.IRBuilder(block)
                self._codegen(node.children[4])
                # self.builder = stored_builder

    def else_clause(self, node):
        if len(node.children) > 1:
            self._codegen(node.children[-1])
        else:
            return

    def repeat_stmt(self, node):
        pass

    def case_stmt(self, node):
        ran = str(randint(0, 0x7FFFFFFF))
        expr = self._codegen(node.children[1])
        othercase = self._codegen(node.children[3])
        default = self.builder.append_basic_block('default_'+ran)
        self.default = default
        case_part = self.builder.switch(expr, default)
        for val, block in othercase:
            case_part.add_case(val, block)
            builder = ir.IRBuilder(block)
            builder.position_at_end(block)
            builder.branch(self.default)
        self.builder.position_at_end(default)

    def case_expr_list(self, node):
        if len(node.children) > 1:
            return self._codegen(node.children[0]) + [self._codegen(node.children[1])]
        else:
            return [self._codegen(node.children[0])]

    def case_expr(self, node):
        ran = str(randint(0, 0x7FFFFFFF))
        val = self._codegen(node.children[0])
        block = self.builder.append_basic_block('case_'+ran)
        stored_builder = self.builder
        self.builder = ir.IRBuilder(block)
        self._codegen(node.children[2])
        self.builder = stored_builder
        return val, block



    def while_stmt(self, node):
        ran = str(randint(0, 0x7FFFFFFF))

        whileblock = self.builder.append_basic_block("while_" + ran)
        stmt = self.builder.append_basic_block("stmt_" + ran)
        jumpout = self.builder.append_basic_block("jumpout")
        self.builder.branch(whileblock)

        w_builder = ir.IRBuilder(whileblock)
        stored = self.builder
        self.builder = w_builder
        cond = self._codegen(node.children[1])
        self.builder.cbranch(cond, stmt, jumpout)
        s_builder = ir.IRBuilder(stmt)
        self.builder = s_builder
        self._codegen(node.children[3])
        self.builder.branch(whileblock)
        self.builder = stored
        self.builder.position_at_end(jumpout)

    def for_stmt(self, node):
        ran = str(randint(0, 0x7FFFFFFF))
        self.symbol_table.create_tab()

        addr = self.builder.alloca(ir.IntType(32))
        init_value = self.expression(node.children[3])
        self.symbol_table.insert([node.children[1].name, addr])
        final_value = self.expression(node.children[5])
        self.builder.store(init_value, addr)

        forblock = self.builder.append_basic_block("for_" + ran)
        self.builder.branch(forblock)
        f_builder = ir.IRBuilder(forblock)

        stmt_block = f_builder.append_basic_block("stmt_" + ran)
        jumpout = f_builder.append_basic_block("jumpout_" + ran)

        init_value = f_builder.load(addr)
        direct = node.children[4].children[0].type
        if direct == "TO":
            cmp = ">"
        else:
            cmp = "<"
        cond = f_builder.icmp_signed(cmp, init_value, final_value)
        f_builder.cbranch(cond, jumpout, stmt_block)
        stmt_builder = ir.IRBuilder(stmt_block)
        stored_builder = self.builder
        self.builder = stmt_builder
        self._codegen(node.children[-1])
        self.builder = stored_builder
        one = ir.IntType(32)(1)
        if direct == "TO":
            inc_dec = stmt_builder.add(init_value, one)
        elif direct == "DOWNTO":
            inc_dec = stmt_builder.sub(init_value, one)
        else:
            raise NotDefinedError([direct])
        stmt_builder.store(inc_dec, addr)
        stmt_builder.branch(forblock)
        self.builder.position_at_end(jumpout)

        self.symbol_table.pop()

    def expression(self, node):
        if len(node.children) > 1:
            lhs = self.expression(node.children[0])
            rhs = self.expr(node.children[-1])
            op = node.children[1].name
            if op == "<>":
                op = "!="
            elif op == "=":
                op = "=="
            else:
                pass
            if lhs.type == rhs.type:
                if lhs.type == ir.IntType(32):
                    return self.builder.icmp_signed(op, lhs, rhs)
                elif lhs.type == ir.DoubleType():
                    return self.builder.fcmp_ordered(op, lhs, rhs)
                else:
                    raise SplTypeError(["None type %s" % (lhs.type)])
            else:
                raise SplTypeError(["types not equal %s ≠ %s" % (lhs.type, rhs.type)])
        elif len(node.children) == 1:
            return self.expr(node.children[-1])
        else:
            raise ExpressionError(["Expression error Num %d" % (len(node.children))])

    def expr(self, node):
        if len(node.children) > 1:
            lhs = self._codegen(node.children[0])
            rhs = self._codegen(node.children[2])
            op = node.children[1].type
            if lhs.type != rhs.type:
                raise SplTypeError(["types not equal %s ≠ %s" % (lhs.type, rhs.type)])
            if lhs.type == ir_type_t["INTEGER"]:
                if op == "PLUS":
                    try:
                        if (lhs.constant) and (rhs.constant):
                            return ir.Constant(ir.IntType(32), int(lhs.constant) + int(rhs.constant))
                    except:
                        return self.builder.add(lhs, rhs)
                elif op == "MINUS":
                    return self.builder.sub(lhs, rhs)
                elif op == "OR":
                    return self.builder.or_(lhs, rhs)
                elif op == "AND":
                    return self.builder.and_(lhs, rhs)
                elif op == "MUL":
                    return self.builder.mul(lhs, rhs)
                elif op == "DIV":
                    return self.builder.sdiv(lhs, rhs)
                elif op == "MOD":
                    return self.builder.urem(lhs, rhs)
                else:
                    raise SplTypeError(["%s on two different types, %s and %s" % (op, lhs.type, rhs.type)])
            if lhs.type == ir_type_t["REAL"]:
                if op == "PLUS":
                    return self.builder.fadd(lhs, rhs)
                elif op == "MINUS":
                    return self.builder.fsub(lhs, rhs)
                elif op == "MUL":
                    return self.builder.fmul(lhs, rhs)
                elif op == "DIV":
                    return self.builder.fdiv(lhs, rhs)
                elif op == "MOD":
                    return self.builder.frem(lhs, rhs)
                else:
                    raise SplTypeError(["%s on two different types, %s and %s" % (op, lhs.type, rhs.type)])
            elif lhs.type == ir_type_t["BOOLEAN"]:
                if op == "OR":
                    return self.builder.or_(lhs, rhs)
                elif op == "AND":
                    return self.builder.and_(lhs, rhs)
                else:
                    raise OpError(["Error Operation %s" % (op)])
            else:
                raise SplTypeError(["None type %s" % (lhs.type)])
        else:
            return self._codegen(node.children[0])

    def term(self, node):
        if len(node.children) > 1:
            lhs = self._codegen(node.children[0])
            rhs = self._codegen(node.children[2])
            op = node.children[1].type
            if lhs.type != rhs.type:
                raise SplTypeError(["%s on two different types, %s and %s" % (op, lhs.type, rhs.type)])
            if lhs.type == ir_type_t["INTEGER"]:
                if op == "MUL":
                    return self.builder.mul(lhs, rhs)
                elif op == "DIV":
                    return self.builder.sdiv(lhs, rhs)
                elif op == "MOD":
                    return self.builder.urem(lhs, rhs)
                else:
                    raise OpError(["Undefined op %s" % op])
            elif lhs.type == "double":
                if op == "MUL":
                    return self.builder.fmul(lhs, rhs)
                elif op == "DIV":
                    return self.builder.fdiv(lhs, rhs)
                elif op == "MOD":
                    return self.builder.frem(lhs, rhs)
                else:
                    raise OpError(["Undefined op %s" % op])
            else:
                raise OpError(["Error Operation %s" % (op)])
        else:
            return self._codegen(node.children[0])

    def factor(self, node):
        if len(node.children) == 1:
            return self._codegen(node.children[0])
        elif len(node.children) == 3:
            if node.children[1].type == "DOT":
                name = node.children[0].name
                lhs = self.symbol_table.find(name)['entry']
                index = node.children[2].name
                offset = self.symbol_table.find(name + "." + index)["entry"]
                i32 = ir.IntType(32)
                i32_0 = ir.Constant(i32, 0)
                pointer_to_index = self.builder.gep(lhs, [i32_0, offset])  # gets address of array[0]
                return self.builder.load(pointer_to_index)
            else:
                return self._codegen(node.children[1])
        elif len(node.children) == 4:
            if node.children[1].type == "LP":
                args = self.args_list(node.children[2])
                func = self.symbol_table.find(node.children[0].name)["entry"]
                args_type = func.args
                for i in range(len(args_type)):
                    if args_type[i].type.is_pointer:
                        args[i] = self.find_addr(node.children[2], len(args) - i - 1)
                ret = self.builder.call(func, args)
                return ret
            elif node.children[1].type == "LB":
                name = node.children[0].name
                lhs = self.symbol_table.find(name)['entry']
                index = self.expression(node.children[2])
                i32 = ir.IntType(32)
                i32_0 = ir.Constant(i32, 0)
                pointer_to_index = self.builder.gep(lhs, [i32_0, index])  # gets address of array[0]
                return self.builder.load(pointer_to_index)


    def args_list(self, node):
        if len(node.children) > 1:
            pre_list = self.args_list(node.children[0])
        else:
            pre_list = []
        current = [self._codegen(node.children[-1])]
        return pre_list + current

    def NAME(self, node):
        name = node.name
        addr = self.symbol_table.find(name)['entry']
        if type(addr) != ir.Function:
            var = self.builder.load(addr)
            return var
        else:
            # return addr
            addr = self.symbol_table.find(name+'_return')['entry']
            var = self.builder.load(addr)
            return var

    def epsilon(self, node):
        pass

