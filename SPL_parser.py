import ply.yacc as yacc
from SPL_lexer import lexer, tokens
from llvmlite import ir



node_types = [
    "program",
    "program_head",
    "routine",
    "subroutine",
    "routine_head",
    "label_part",
    "const_part",
    "const_expr_list",
    "const_value",
    "type_part",
    "type_decl_list",
    "type_definition",
    "type_decl",
    "simple_type_decl",
    "array_type_decl",
    "record_type_decl",
    "field_decl_list",
    "field_decl",
    "name_list",
    "var_part",
    "var_decl_list",
    "var_decl",
    "routine_part",
    "function_decl",
    "function_head",
    "procedure_decl",
    "procedure_head",
    "parameters",
    "para_decl_list",
    "para_type_list",
    "var_para_list",
    "routine_body",
    "compound_stmt",
    "stmt_list",
    "stmt",
    "nonlabel_stmt",
    "assign_stmt",
    "proc_stmt",
    "if_stmt",
    "else_clause",
    "repeat_stmt",
    "while_stmt",
    "for_stmt",
    "direction",
    "case_stmt",
    "case_expr_list",
    "case_expr",
    "goto_stmt",
    "expression_list",
    "expression",
    "expr",
    "term",
    "factor",
    "args_list"
]

class Node:
    def __init__(self, children_list, type, name=""):
        self.children = children_list
        self.type = type
        self.name = name
        self.arg_list = [] # [ name, type ]

    def __repr__(self):
        return "(%s/%s)" % (self.type, self.name if self.name != "" else "NoName")


def p_program(p):
    'program : program_head routine DOT'
    p[0] = Node([p[1], p[2], Node([], "DOT")], "program")


def p_program_head(p):
    'program_head : PROGRAM NAME SEMI'
    p[0] = Node([Node([], "PROGRAM"), Node([], "NAME", p[2]), Node([], "SEMI")], "program_head")


def p_routine(p):
    'routine : routine_head routine_body'
    p[0] = Node([p[1], p[2]], "routine")


def p_sub_routine(p):
    'sub_routine : routine_head routine_body'
    p[0] = Node([p[1], p[2]], "subroutine")


def p_routine_head(p):
    'routine_head : label_part const_part type_part var_part routine_part'
    p[0] = Node([p[1], p[2], p[3], p[4], p[5]], "routine_head")


def p_label_part(p):
    'label_part : epsilon'
    p[0] = Node([p[1]], "label_part")


def p_const_part(p):
    'const_part : CONST const_expr_list'
    p[0] = Node([Node([], "CONST"), p[2]], "const_part")


def p_const_part_e(p):
    'const_part : epsilon'
    p[0] = Node([p[1]], "const_part")


def p_const_expr_list_1(p):
    'const_expr_list : const_expr_list NAME EQUAL const_value SEMI'
    p[0] = Node([p[1], Node([], "NAME", p[2]), Node([], "EQUAL"), p[4], Node([], "SEMI")], "const_expr_list")
    p[0].arg_list = p[1].arg_list + [[p[2], p[4].children[0].type]]


def p_const_expr_list_2(p):
    'const_expr_list : NAME EQUAL const_value SEMI'
    p[0] = Node([Node([], "NAME", p[1]), Node([], "EQUAL"), p[3], Node([], "SEMI")], "const_expr_list")
    p[0].arg_list = [[p[1], p[3].children[0].type]]

def p_const_value_1(p):
    'const_value : INTEGER'
    p[0] = Node([Node([], "INTEGER", p[1])], "const_value")


def p_const_value_2(p):
    'const_value : REAL'
    p[0] = Node([Node([], "REAL", p[1])], "const_value")


def p_const_value_3(p):
    'const_value : CHAR'
    p[0] = Node([Node([], "CHAR", p[1])], "const_value")


def p_const_value_4(p):
    'const_value : STRING'
    p[0] = Node([Node([], "STRING", p[1])], "const_value")


def p_const_value_5(p):
    'const_value : SYS_CON'
    p[0] = Node([Node([], "SYS_CON", p[1])], "const_value")


def p_type_part(p):
    'type_part : TYPE type_decl_list'
    p[0] = Node([Node([], "TYPE"), p[2]], "type_part")


def p_type_part_e(p):
    'type_part : epsilon'
    p[0] = Node([p[1]], "type_part")


def p_type_decl_list_1(p):
    'type_decl_list : type_decl_list type_definition'
    p[0] = Node([p[1], p[2]], "type_decl_list")


def p_type_decl_list_2(p):
    'type_decl_list : type_definition'
    p[0] = Node([p[1]], "type_decl_list")


def p_type_definition(p):
    'type_definition : NAME EQUAL type_decl SEMI'
    p[0] = Node([Node([], "NAME", p[1]), Node([], "EQUAL"), p[3], Node([], "SEMI")], "type_definition")
    t = p[3].children[0]
    if t.type == "simple_type_decl" and t.children[0].type in ["NAME", "SYS_TYPE"]:
        p[0].arg_list = [p[1], t.children[0].type]


def p_type_decl_1(p):
    'type_decl : simple_type_decl'
    p[0] = Node([p[1]], "type_decl")


def p_type_decl_2(p):
    'type_decl : array_type_decl'
    p[0] = Node([p[1]], "type_decl")


def p_type_decl_3(p):
    'type_decl : record_type_decl'
    p[0] = Node([p[1]], "type_decl")


def p_simple_type_decl_1(p):
    'simple_type_decl : SYS_TYPE'
    p[0] = Node([Node([], "SYS_TYPE", p[1])], "simple_type_decl")


def p_simple_type_decl_2(p):
    'simple_type_decl : NAME'
    p[0] = Node([Node([], "NAME", p[1])], "simple_type_decl")


def p_simple_type_decl_3(p):
    'simple_type_decl : LP name_list RP'
    p[0] = Node([Node([], "LP"), p[2], Node([], "RP")], "simple_type_decl")


def p_simple_type_decl_4(p):
    'simple_type_decl : const_value DOTDOT const_value'
    p[0] = Node([p[1], Node([], "DOTDOT"), p[3]], "simple_type_decl")


def p_simple_type_decl_5(p):
    'simple_type_decl : MINUS const_value DOTDOT const_value'
    p[2].children[0].name = p[2].children[0].name
    p[0] = Node([Node([], "MINUS"), p[2], Node([], "DOTDOT"), p[4]], "simple_type_decl")


def p_simple_type_decl_6(p):
    'simple_type_decl : MINUS const_value DOTDOT MINUS const_value'
    # p[2].children[0].name = str(- int(p[2].children[0].name))
    # p[5].children[0].name = str(- int(p[5].children[0].name))
    p[2].children[0].name = p[2].children[0].name
    p[5].children[0].name = p[5].children[0].name
    p[0] = Node([Node([], "MINUS"), p[2], Node([], "DOTDOT"), Node([], "MINUS"), p[5]], "simple_type_decl")


def p_simple_type_decl_7(p):
    'simple_type_decl : NAME  DOTDOT  NAME'
    p[0] = Node([Node([], "NAME", p[1]), Node([], "DOTDOT"), Node([], "NAME", p[3])], "simple_type_decl")


def p_array_type_decl(p):
    'array_type_decl : ARRAY LB simple_type_decl RB OF type_decl'
    p[0] = Node([Node([], "ARRAY"), Node([], "LB"), p[3], Node([], "RB"), Node([], "OF"), p[6]], "array_type_decl")


def p_record_type_decl(p):
    'record_type_decl : RECORD field_decl_list END'
    p[0] = Node([Node([], "RECORD"), p[2], Node([], "END")], "record_type_decl")


def p_field_decl_list_1(p):
    'field_decl_list : field_decl_list field_decl'
    p[0] = Node([p[1], p[2]], "field_decl_list")


def p_field_decl_list_2(p):
    'field_decl_list : field_decl'
    p[0] = Node([p[1]], "field_decl_list")


def p_field_decl(p):
    'field_decl : name_list COLON type_decl SEMI'
    p[0] = Node([p[1], Node([], "COLON"), p[3], Node([], "SEMI")], "field_decl")


def p_name_list_1(p):
    'name_list : name_list COMMA NAME'
    p[0] = Node([p[1], Node([], "COMMA"), Node([], "NAME", p[3])], "name_list")


def p_name_list_2(p):
    'name_list : NAME'
    p[0] = Node([Node([], "NAME", p[1])], "name_list")


def p_var_part(p):
    'var_part : VAR var_decl_list'
    p[0] = Node([Node([], "VAR"), p[2]], "var_part")


def p_var_part_e(p):
    'var_part : epsilon'
    p[0] = Node([p[1]], "var_part")


def p_var_decl_list_1(p):
    'var_decl_list : var_decl_list var_decl'
    p[0] = Node([p[1], p[2]], "var_decl_list")


def p_var_decl_list_2(p):
    'var_decl_list : var_decl'
    p[0] = Node([p[1]], "var_decl_list")


def p_var_decl(p):
    'var_decl : name_list COLON type_decl SEMI'
    p[0] = Node([p[1], Node([], "COLON"), p[3], Node([], "SEMI")], "var_decl")


def p_routine_part_1(p):
    'routine_part : routine_part function_decl'
    p[0] = Node([p[1], p[2]], "routine_part")


def p_routine_part_2(p):
    'routine_part : routine_part procedure_decl'
    p[0] = Node([p[1], p[2]], "routine_part")


def p_routine_part_3(p):
    'routine_part : function_decl'
    p[0] = Node([p[1]], "routine_part")


def p_routine_part_4(p):
    'routine_part : procedure_decl'
    p[0] = Node([p[1]], "routine_part")


def p_routine_part_5(p):
    'routine_part : epsilon'
    p[0] = Node([p[1]], "routine_part")


def p_function_decl(p):
    'function_decl : function_head SEMI sub_routine SEMI'
    p[0] = Node([p[1], Node([], "SEMI"), p[3], Node([], "SEMI")], "function_decl")


def p_function_head(p):
    'function_head : FUNCTION NAME parameters COLON simple_type_decl'
    p[0] = Node([Node([], "FUNCTION"), Node([], "NAME", p[2]), p[3], Node([], "COLON"), p[5]], "function_head")
    p[0].arg_list = p[3].arg_list

def p_procedure_decl(p):
    'procedure_decl : procedure_head SEMI sub_routine SEMI'
    p[0] = Node([p[1], Node([], "SEMI"), p[3], Node([], "SEMI")], "procedure_decl")


def p_procedure_head(p):
    'procedure_head : PROCEDURE NAME parameters'
    p[0] = Node([Node([], "PROCEDURE"), Node([], "NAME", p[2]), p[3]], "procedure_head")


def p_parameters(p):
    'parameters : LP para_decl_list RP'
    p[0] = Node([Node([], "LP"), p[2], Node([], "RP")], "parameters")
    p[0].arg_list = p[2].arg_list


def p_parameters_e(p):
    'parameters : epsilon'
    p[0] = Node([p[1]], "parameters")


def p_para_decl_list_1(p):
    'para_decl_list : para_decl_list SEMI para_type_list'
    p[0] = Node([p[1], Node([], "SEMI"), p[3]], "para_decl_list")
    p[0].arg_list = p[1].arg_list + p[3].arg_list


def p_para_decl_list_2(p):
    'para_decl_list : para_type_list'
    p[0] = Node([p[1]], "para_decl_list")
    p[0].arg_list = p[1].arg_list


def p_para_type_list_1(p):
    'para_type_list : var_para_list COLON simple_type_decl'
    p[0] = Node([p[1], Node([], "COLON"), p[3]], "para_type_list")


def p_para_type_list_2(p):
    'para_type_list : val_para_list COLON simple_type_decl'
    p[0] = Node([p[1], Node([], "COLON"), p[3]], "para_type_list")


def p_var_para_list(p):
    'var_para_list : VAR name_list'
    p[0] = Node([Node([], "VAR"), p[2]], "var_para_list")


def p_val_para_list(p):
    'val_para_list : name_list'
    p[0] = Node([p[1]], "val_para_list")


def p_routine_body(p):
    'routine_body : compound_stmt'
    p[0] = Node([p[1]], "routine_body")


def p_compound_stmt(p):
    'compound_stmt : BEGIN stmt_list END'
    p[0] = Node([Node([], "BEGIN"), p[2], Node([], "END")], "compound_stmt")


def p_stmt_list(p):
    'stmt_list : stmt_list stmt SEMI'
    p[0] = Node([p[1], p[2], Node([], "SEMI")], "stmt_list")


def p_stmt_list_e(p):
    'stmt_list : epsilon'
    p[0] = Node([p[1]], "stmt_list")


def p_stmt_1(p):
    'stmt : INTEGER COLON non_label_stmt'
    p[0] = Node([Node([], "INTEGER", p[1]), Node([], "COLON"), p[3]], "stmt")


def p_stmt_2(p):
    'stmt : non_label_stmt'
    p[0] = Node([p[1]], "stmt")


def p_non_label_stmt_1(p):
    'non_label_stmt : assign_stmt'
    p[0] = Node([p[1]], "non_label_stmt")


def p_non_label_stmt_2(p):
    'non_label_stmt : proc_stmt'
    p[0] = Node([p[1]], "non_label_stmt")


def p_non_label_stmt_3(p):
    'non_label_stmt : compound_stmt'
    p[0] = Node([p[1]], "non_label_stmt")


def p_non_label_stmt_4(p):
    'non_label_stmt : if_stmt'
    p[0] = Node([p[1]], "non_label_stmt")


def p_non_label_stmt_5(p):
    'non_label_stmt : repeat_stmt'
    p[0] = Node([p[1]], "non_label_stmt")


def p_non_label_stmt_6(p):
    'non_label_stmt : while_stmt'
    p[0] = Node([p[1]], "non_label_stmt")


def p_non_label_stmt_7(p):
    'non_label_stmt : for_stmt'
    p[0] = Node([p[1]], "non_label_stmt")


def p_non_label_stmt_8(p):
    'non_label_stmt : case_stmt'
    p[0] = Node([p[1]], "non_label_stmt")


def p_non_label_stmt_9(p):
    'non_label_stmt : goto_stmt'
    p[0] = Node([p[1]], "non_label_stmt")


def p_assign_stmt_1(p):
    'assign_stmt : NAME ASSIGN expression'
    p[0] = Node([Node([], "NAME", p[1]), Node([], "ASSIGN"), p[3]], "assign_stmt")


def p_assign_stmt_2(p):
    'assign_stmt : NAME LB expression RB ASSIGN expression'
    p[0] = Node([Node([], "NAME", p[1]), Node([], "LB"), p[3], Node([], "RB"), Node([], "ASSIGN"), p[6]], "assign_stmt")


def p_assign_stmt_3(p):
    'assign_stmt : NAME DOT NAME ASSIGN expression'
    p[0] = Node([Node([], "NAME", p[1]), Node([], "DOT"), Node([], "NAME", p[3]), Node([], "ASSIGN"), p[5]], "assign_stmt")


def p_proc_stmt_1(p):
    'proc_stmt : NAME'
    p[0] = Node([Node([], "NAME", p[1])], "proc_stmt")


def p_proc_stmt_2(p):
    'proc_stmt : NAME LP args_list RP'
    p[0] = Node([Node([], "NAME", p[1]), Node([], "LP"), p[3], Node([], "RP")], "proc_stmt")


def p_proc_stmt_3(p):
    'proc_stmt : SYS_PROC'
    p[0] = Node([Node([], "SYS_PROC", p[1])], "proc_stmt")


def p_proc_stmt_4(p):
    'proc_stmt : SYS_PROC LP expression_list RP'
    p[0] = Node([Node([], "SYS_PROC", p[1]), Node([], "LP"), p[3], Node([], "RP")], "proc_stmt")


def p_proc_stmt_5(p):
    'proc_stmt : READ LP factor RP'
    p[0] = Node([Node([], "READ"), Node([], "LP"), p[3], Node([], "RP")], "proc_stmt")


def p_if_stmt(p):
    'if_stmt : IF expression THEN stmt else_clause'
    p[0] = Node([Node([], "IF"), p[2], Node([], "THEN"), p[4], p[5]], "if_stmt")


def p_else_clause(p):
    'else_clause : ELSE stmt'
    p[0] = Node([Node([], "ELSE"), p[2]], "else_clause")


def p_else_clause_e(p):
    'else_clause : epsilon'
    p[0] = Node([p[1]], "else_clause")

def p_repeat_stmt(p):
    'repeat_stmt : REPEAT stmt_list UNTIL expression'
    p[0] = Node([Node([], "REPEAT"), p[2], Node([], "UNTIL"), p[4]], "repeat_stmt")


def p_while_stmt(p):
    'while_stmt : WHILE expression DO stmt'
    p[0] = Node([Node([], "WHILE"), p[2], Node([], "DO"), p[4]], "while_stmt")


def p_for_stmt(p):
    'for_stmt : FOR NAME ASSIGN expression direction expression DO stmt'
    p[0] = Node([Node([], "FOR"), Node([], "NAME", p[2]), Node([], "ASSIGN"), p[4], p[5], p[6], Node([], "DO"), p[8]], "for_stmt")


def p_direction_1(p):
    'direction : TO'
    p[0] = Node([Node([], "TO")], "direction")


def p_direction_2(p):
    'direction : DOWNTO'
    p[0] = Node([Node([], "DOWNTO")], "direction")


def p_case_stmt(p):
    'case_stmt : CASE expression OF case_expr_list END'
    p[0] = Node([Node([], "CASE"), p[2], Node([], "OF"), p[4], Node([], "END")], "case_stmt")


def p_case_expr_list_1(p):
    'case_expr_list : case_expr_list case_expr'
    p[0] = Node([p[1], p[2]], "case_expr_list")


def p_case_expr_list_2(p):
    'case_expr_list : case_expr'
    p[0] = Node([p[1]], "case_expr_list")


def p_case_expr_1(p):
    'case_expr : const_value COLON stmt SEMI'
    p[0] = Node([p[1], Node([], "COLON"), p[3], Node([], "SEMI")], "case_expr")


def p_case_expr_2(p):
    'case_expr : NAME COLON stmt SEMI'
    p[0] = Node([Node([], "NAME", p[1]), Node([], "COLON"), p[3], Node([], "SEMI")], "case_expr")


def p_goto_stmt(p):
    'goto_stmt : GOTO INTEGER'
    p[0] = Node([Node([], "GOTO"), Node([], "INTEGER", p[2])], "goto_stmt")


def p_expression_list_1(p):
    'expression_list : expression_list COMMA expression'
    p[0] = Node([p[1], Node([], "COMMA"), p[3]], "expression_list")


def p_expression_list_2(p):
    'expression_list : expression'
    p[0] = Node([p[1]], "expression_list")


def p_expression_1(p):
    'expression : expression GE expr'
    p[0] = Node([p[1], Node([], "GE"), p[3]], "expression")


def p_expression_2(p):
    'expression : expression GT expr'
    p[0] = Node([p[1], Node([], "GT", p[2]), p[3]], "expression")


def p_expression_3(p):
    'expression : expression LE expr'
    p[0] = Node([p[1], Node([], "LE", p[2]), p[3]], "expression")


def p_expression_4(p):
    'expression : expression LT expr'
    p[0] = Node([p[1], Node([], "LT", p[2]), p[3]], "expression")


def p_expression_5(p):
    'expression : expression EQUAL expr'
    p[0] = Node([p[1], Node([], "EQUAL", p[2]), p[3]], "expression")


def p_expression_6(p):
    'expression : expression UNEQUAL expr'
    p[0] = Node([p[1], Node([], "UNEQUAL", p[2]), p[3]], "expression")


def p_expression_7(p):
    'expression : expr'
    p[0] = Node([p[1]], "expression")


def p_expr_1(p):
    'expr : expr PLUS term'
    p[0] = Node([p[1], Node([], "PLUS"), p[3]], "expr")


def p_expr_2(p):
    'expr : expr MINUS term'
    p[0] = Node([p[1], Node([], "MINUS"), p[3]], "expr")


def p_expr_3(p):
    'expr : expr OR term'
    p[0] = Node([p[1], Node([], "OR"), p[3]], "expr")


def p_expr_4(p):
    'expr : term'
    p[0] = Node([p[1]], "expr")


def p_term_1(p):
    'term : term MUL factor'
    p[0] = Node([p[1], Node([], "MUL", p[2]), p[3]], "term")


def p_term_2(p):
    'term : term DIV factor '
    p[0] = Node([p[1], Node([], "DIV", p[2]), p[3]], "term")


def p_term_3(p):
    'term : term MOD factor'
    p[0] = Node([p[1], Node([], "MOD", p[2]), p[3]], "term")


def p_term_4(p):
    'term : term AND factor'
    p[0] = Node([p[1], Node([], "AND", p[2]), p[3]], "term")


def p_term_5(p):
    'term : factor'
    p[0] = Node([p[1]], "term")


def p_factor_1(p):
    'factor : NAME'
    p[0] = Node([Node([], "NAME", p[1])], "factor")


def p_factor_2(p):
    'factor : NAME LP args_list RP'
    p[0] = Node([Node([], "NAME", p[1]), Node([], "LP"), p[3], Node([], "RP")], "factor")


def p_factor_3(p):
    'factor : SYS_FUNCT'
    p[0] = Node([Node([], "SYS_FUNCT")], "factor")


def p_factor_4(p):
    'factor : SYS_FUNCT  LP  args_list RP'
    p[0] = Node([Node([], "SYS_FUNC"), Node([], "LP"), p[3], Node([], "RP")], "factor")


def p_factor_5(p):
    'factor : const_value'
    p[0] = Node([p[1]], "factor")


def p_factor_6(p):
    'factor : LP expression RP'
    p[0] = Node([Node([], "LP"), p[2], Node([], "RP")], "factor")


def p_factor_7(p):
    'factor : NOT factor'
    p[0] = Node([Node([], "NOT"), p[2]], "factor")


def p_factor_8(p):
    'factor : MINUS factor'
    p[0] = Node([Node([], "MINUS"), p[2]], "factor")


def p_factor_9(p):
    'factor : NAME LB expression RB'
    p[0] = Node([Node([], "NAME", p[1]), Node([], "LB"), p[3], Node([], "RB")], "factor")


def p_factor_10(p):
    'factor : NAME DOT NAME '
    p[0] = Node([Node([], "NAME", p[1]), Node([], "DOT"), Node([], "NAME", p[3])], "factor")


def p_args_list_1(p):
    'args_list : args_list COMMA expression'
    p[0] = Node([p[1], Node([], "COMMA"), p[3]], "args_list")


def p_args_list_2(p):
    'args_list : expression'
    p[0] = Node([p[1]], "args_list")


def p_epsilon(p):
    'epsilon : '
    p[0] = Node([], "epsilon")


def p_error(p):
    print("Syntax error in input!", p)


parser = yacc.yacc()

