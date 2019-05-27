import ply.lex as lex

tokens = [
    "NAME", "LP", "RP", "LB", "RB", "DOT", "COMMA", "COLON", "MUL", "DIV", "UNEQUAL", "NOT",
    "PLUS", "MINUS", "GE", "GT", "LE", "LT", "EQUAL", "ASSIGN", "MOD", "DOTDOT", "SEMI",
    "SYS_CON", "SYS_FUNCT", "SYS_PROC", "SYS_TYPE", "READ", "INTEGER", "REAL", "CHAR", "STRING",
    "AND", "ARRAY", "BEGIN", "CASE", "CONST", "DO", "DOWNTO", "ELSE", "END", "FOR", "FUNCTION",
    "GOTO", "IF", "IN", "OF", "OR", "PACKED", "PROCEDURE", "PROGRAM", "RECORD", "REPEAT", "SET",
    "THEN", "TO", "TYPE", "UNTIL", "VAR", "WHILE", "WITH"
]

def t_REAL(t):
    r"(\d+\.\d+(([Ee])[+-]?\d+)?)|(\d+(([Ee])[-+]?\d+))"
    return t

def t_INTEGER(t):
    r'\d+'
    return t


def t_CHAR(t):
    r"\'.\'"
    return t

def t_STRING(t):
    r'\".*?\"'
    return t

t_LP          = r"\("
t_RP          = r"\)"
t_LB          = r"\["
t_RB          = r"\]"
t_DOT         = r"\."
t_COMMA       = r","
t_COLON       = r":"
t_MUL         = r"\*"
t_DIV         = r"/"
t_PLUS        = r"\+"
t_MINUS       = r"-"

t_GE          = r">="
t_GT          = r">"
t_LE          = r"<="
t_LT          = r"<"
t_EQUAL       = r"="
t_UNEQUAL     = r"<>"

t_ASSIGN      = r":="
t_DOTDOT      = r"\.\."
t_SEMI        = r";"
def t_NOT(t):
    r"not"
    return t
def t_MOD(t):
    r"mod"
    return t

def t_SYS_CON(t):
    r'true|maxint|false'
    return t
def t_SYS_FUNCT(t):
    r'abs|chr|odd|ord|pred|sqr|sqrt|succ'
    return t
def t_SYS_PROC(t):
    r'writeln|write'
    return t
def t_SYS_TYPE(t):
    r'boolean|char|integer|real|string'
    return t
def t_READ(t):
    r"read"
    return t





def t_AND(t):
    r"and"
    return t
def t_ARRAY(t):
    r"array"
    return t
def t_BEGIN(t):
    r"begin"
    return t
def t_CASE(t):
    r"case"
    return t
def t_CONST(t):
    r"const"
    return t
def t_DO(t):
    r"do"
    return t
def t_DOWNTO(t):
    r"downto"
    return t
def t_ELSE(t):
    r"else"
    return t
def t_END(t):
    r"end"
    return t
def t_FOR(t):
    r"for"
    return t
def t_FUNCTION(t):
    r"function"
    return t
def t_GOTO(t):
    r"goto"
    return t
def t_IF(t):
    r"if"
    return t
def t_IN(t):
    r"in"
    return t
def t_OF(t):
    r"of"
    return t
def t_OR(t):
    r"or"
    return t
def t_PACKED(t):
    r"packed"
    return t
def t_PROCEDURE(t):
    r"procedure"
    return t
def t_PROGRAM(t):
    r"program"
    return t
def t_RECORD(t):
    r"record"
    return t
def t_REPEAT(t):
    r"repeat"
    return t
def t_SET(t):
    r"set"
    return t
def t_THEN(t):
    r"then"
    return t
def t_TO(t):
    r"to"
    return t
def t_TYPE(t):
    r"type"
    return t
def t_UNTIL(t):
    r"until"
    return t
def t_VAR(t):
    r"var"
    return t
def t_WHILE(t):
    r"while"
    return t
def t_WITH(t):
    r"with"
    return t

def t_NAME(t):
    r"[_a-zA-Z][_a-zA-Z0-9]*"
    return t

def t_newline(t):
    r"\n+"
    t.lexer.lineno += len(t.value)
t_ignore  = ' \t'


def t_error(t):
    print("Invalid Token:", t.value[0])
    t.lexer.skip(1)

lexer = lex.lex()
