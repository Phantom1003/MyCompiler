import ply.lex as lex
from CompilerError import *

reserved = {
    'and': 'AND', 'array': 'ARRAY', 'begin': 'BEGIN', 'case': 'CASE',
    'const': 'CONST', 'do': 'DO', 'downto': 'DOWNTO', 'else': 'ELSE',
    'end': 'END', 'for': 'FOR', 'function': 'FUNCTION', 'goto': 'GOTO',
    'if': 'IF', 'in': 'IN', 'of' : 'OF', 'packed': 'PACKED',
    'procedure' : 'PROCEDURE', 'program': 'PROGRAM', 'record': 'RECORD', 'repeat': 'REPEAT',
    'set': 'SET', 'then': 'THEN', 'to': 'TO', 'while': 'WHILE',
    'type': 'TYPE', 'until': 'UNTIL', 'var': 'VAR', 'NOT': 'NOT',
    'with': 'WITH', 'MOD': 'MOD',   'true': 'SYS_CON', 'maxint': 'SYS_CON',
    'false': 'SYS_CON', 'abs': 'SYS_FUNCT', 'chr': 'SYS_FUNCT', 'odd': 'SYS_FUNCT',
    'ord': 'SYS_FUNCT', 'pred': 'SYS_FUNCT', 'sqr': 'SYS_FUNCT', 'succ': 'SYS_FUNCT',
    'sqrt': 'SYS_FUNCT', 'writeln': 'SYS_PROC', 'write': 'SYS_PROC', 'boolean': 'SYS_TYPE',
    'char': 'SYS_TYPE', 'integer': 'SYS_TYPE', 'real': 'SYS_TYPE', 'string': 'SYS_TYPE',
    'read': 'READ'
}

tokens = [
    "NAME", "LP", "RP", "LB", "RB", "DOT", "COMMA", "COLON", "MUL", "DIV", "UNEQUAL", "NOT",
    "PLUS", "MINUS", "GE", "GT", "LE", "LT", "EQUAL", "ASSIGN", "MOD", "DOTDOT", "SEMI",
    "SYS_CON", "SYS_FUNCT", "SYS_PROC", "SYS_TYPE", "READ", "INTEGER", "REAL", "CHAR", "STRING",
    "AND", "ARRAY", "BEGIN", "CASE", "CONST", "DO", "DOWNTO", "ELSE", "END", "FOR", "FUNCTION",
    "GOTO", "IF", "IN", "OF", "OR", "PACKED", "PROCEDURE", "PROGRAM", "RECORD", "REPEAT", "SET",
    "THEN", "TO", "TYPE", "UNTIL", "VAR", "WHILE", "WITH" ]

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

def t_NAME(t):
    r"[a-zA-Z_][a-zA-Z0-9_]*"
    t.type = reserved.get(t.value, 'NAME')
    return t

def t_newline(t):
    r"\n+"
    t.lexer.lineno += len(t.value)
t_ignore  = ' \t'

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

def t_error(t):
    print("Invalid Token:", t.value[0])
    t.lexer.skip(1)
    raise LexError(["Invalid Token: %s at %d" % (t.value[0], t.lineno)])

lexer = lex.lex()
