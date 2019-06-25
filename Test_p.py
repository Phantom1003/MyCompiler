import llvmlite.ir as ir
import llvmlite.binding as llvm
from ctypes import CFUNCTYPE

import sys

def main():
    m = ir.Module()
    func_ty = ir.FunctionType(ir.VoidType(), [])
    i32_ty = ir.IntType(32)
    func = ir.Function(m, func_ty, name="printer")

    voidptr_ty = ir.IntType(8).as_pointer()

    fmt = "Hello, %s! %i times!\n\0"
    c_fmt = ir.Constant(ir.ArrayType(ir.IntType(8), len(fmt)),
                        bytearray(fmt.encode("utf8")))
    global_fmt = ir.GlobalVariable(m, c_fmt.type, name="fstr")
    global_fmt.linkage = 'internal'
    global_fmt.global_constant = True
    global_fmt.initializer = c_fmt

    arg = "World\0"
    c_str_val = ir.Constant(ir.ArrayType(ir.IntType(8), len(arg)),
                            bytearray(arg.encode("utf8")))

    printf_ty = ir.FunctionType(ir.IntType(32), [voidptr_ty], var_arg=True)
    printf = ir.Function(m, printf_ty, name="printf")

    builder = ir.IRBuilder(func.append_basic_block('entry'))

    c_str = builder.alloca(c_str_val.type)
    builder.store(c_str_val, c_str)

    # this val can come from anywhere
    int_val = builder.add(i32_ty(5), i32_ty(3))

    fmt_arg = builder.bitcast(global_fmt, voidptr_ty)
    builder.call(printf, [fmt_arg, c_str, int_val])

    builder.ret_void()

    llvm.initialize()
    llvm.initialize_native_target()
    llvm.initialize_native_asmprinter()

    f = open("test.txt", "w")
    old = sys.stdout
    sys.stdout = f
    print(str(m))
    sys.stdout = old
    f.close()
    f = open("test.txt", "r")
    print(f.read())
    f.close()
    llvm_module = llvm.parse_assembly(str(m))
    tm = llvm.Target.from_default_triple().create_target_machine()

    with llvm.create_mcjit_compiler(llvm_module, tm) as ee:
        ee.finalize_object()
        fptr = ee.get_function_address("printer")
        py_func = CFUNCTYPE(None)(fptr)
        py_func()

if __name__ == "__main__":
    main()