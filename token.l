%{  
#include <stdio.h>
#include "token.h"

enum TokenType {
    NAME = 258, 
    LP, RP, LB, RB, DOT, COMMA, COLON, MUL, DIV, UNEQUAL, NOT, PLUS, MINUS, GE, GT, LE, LT, EQUAL, ASSIGN, MOD, DOTDOT, SEMI, 
    SYS_CON, SYS_FUNCT, SYS_PROC, SYS_TYPE, READ,
    INTEGER, REAL, CHAR, STR, 
    AND, ARRAY, BEGIN_TOKEN, CASE, CONST, DO, DOWNTO, ELSE, END, FOR, FUNCTION, GOTO, IF, IN, OF, OR, PACKED, PROCEDURE, 
    PROGRAM, RECORD, REPEAT, SET, THEN, TO, TYPE, UNTIL, VAR, WHILE, WITH    
};

TOKEN yylval;

int line_num = 1;

%}
name    [a-zA-Z][_a-zA-Z0-9]*

lp          "("
rp          ")"
lb          "["
rb          "]"
dot         "."
comma       ","
colon       ":"
mul         "*"
div         "/"
unequal     "<>"
not         "not"
plus        "+"
minus       "-"
ge          ">="
gt          ">"
le          "<="
lt          "<"
equal       "="
assign      ":="
mod         "mod"
dotdot      ".."
semi        ";"

sys_con     "true"|"maxint"|"false"
sys_funct   "abs"|"chr"|"odd"|"ord"|"pred"|"sqr"|"sqrt"|"succ"
sys_proc    "write"|"writeln"
sys_type    "boolean"|"char"|"integer"|"real"
read        "read"

digit       [0-9]
integer     {digit}+
real        {digit}+(\.{digit}+)?(([E|e])[+\-]?{digit}+)?
char        '.'
str 		\".+?\"


and         "and"
array       "array"
begin       "begin"
case        "case"
const       "const"
do          "do"
downto      "downto"
else        "else"
end         "end"
for         "for"
function    "function"
goto        "goto"
if          "if"
in          "in"
of          "of"
or          "or"
packed      "packed"
procedure   "procedure"
program     "program"
record      "record"
repeat      "repeat"
set         "set"
then        "then"
to          "to"
type        "type"
until       "until"
var         "var"
while       "while"
with        "with"

delim       [ \t]
whitespace  {delim}+
%%


{lp}            {return makeToken(DELIMITER, LP);}
{rp}            {return makeToken(DELIMITER, RP);}
{lb}            {return makeToken(DELIMITER, LB);}
{rb}            {return makeToken(DELIMITER, RB);}
{dotdot}        {return makeToken(DELIMITER, DOTDOT);}
{comma}         {return makeToken(DELIMITER, COMMA);}
{colon}         {return makeToken(DELIMITER, COLON);}
{semi}          {return makeToken(DELIMITER, SEMI);}


{plus}          {return makeToken(OPERATOR, PLUS);}
{minus}         {return makeToken(OPERATOR, MINUS);}
{mul}           {return makeToken(OPERATOR, MUL);}
{div}           {return makeToken(OPERATOR, DIV);}
{mod}           {return makeToken(OPERATOR, MOD);}
{ge}            {return makeToken(OPERATOR, GE);}
{gt}            {return makeToken(OPERATOR, GT);}
{le}            {return makeToken(OPERATOR, LE);}
{lt}            {return makeToken(OPERATOR, LT);}
{equal}         {return makeToken(OPERATOR, EQUAL);}
{unequal}       {return makeToken(OPERATOR, UNEQUAL);}
{assign}        {return makeToken(OPERATOR, ASSIGN);}
{dot}        	{return makeToken(OPERATOR, DOT);}
{and}           {return makeToken(OPERATOR, AND);}
{or}            {return makeToken(OPERATOR, OR);}
{not}           {return makeToken(OPERATOR, NOT);}


{sys_con}       {return makeToken(RESERVED, SYS_CON);}
{sys_funct}     {return makeToken(RESERVED, SYS_FUNCT);}   
{sys_proc}      {return makeToken(RESERVED, SYS_PROC);}
{sys_type}      {return makeToken(RESERVED, SYS_TYPE);}
{read}          {return makeToken(RESERVED, READ);}

{array}         {return makeToken(RESERVED, ARRAY);}
{begin}         {return makeToken(RESERVED, BEGIN_TOKEN);}
{case}          {return makeToken(RESERVED, CASE);}
{const}         {return makeToken(RESERVED, CONST);}
{do}            {return makeToken(RESERVED, DO);}
{downto}        {return makeToken(RESERVED, DOWNTO);}
{else}          {return makeToken(RESERVED, ELSE);}
{end}           {return makeToken(RESERVED, END);}
{for}           {return makeToken(RESERVED, FOR);}
{function}      {return makeToken(RESERVED, FUNCTION);}
{goto}          {return makeToken(RESERVED, GOTO);}
{if}            {return makeToken(RESERVED, IF);}
{in}            {return makeToken(RESERVED, IN);}
{of}            {return makeToken(RESERVED, OF);}
{packed}        {return makeToken(RESERVED, PACKED);}
{procedure}     {return makeToken(RESERVED, PROCEDURE);}
{program}       {return makeToken(RESERVED, PROGRAM);}
{record}        {return makeToken(RESERVED, RECORD);}
{repeat}        {return makeToken(RESERVED, REPEAT);}
{set}           {return makeToken(RESERVED, SET);}
{then}          {return makeToken(RESERVED, THEN);}
{to}            {return makeToken(RESERVED, TO);}
{type}          {return makeToken(RESERVED, TYPE);}
{until}         {return makeToken(RESERVED, UNTIL);}
{var}           {return makeToken(RESERVED, VAR);}
{while}         {return makeToken(RESERVED, WHILE);}
{with}          {return makeToken(RESERVED, WITH);}


{name}          {return makeNameToken();}
{integer}       {return makeIntToken();}
{real}          {return makeRealToken();}
{char}          {return makeCharToken();}
{str}			{return makeStrToken();}

[\n]            {line_num++;}
{whitespace}    {/*do nothing*/}
%%


int makeToken(tokenType tok_t, int t) {
	yylval = (TOKEN) malloc(TOKENSIZE);
	yylval->token_t = tok_t;
	return t;
}

int makeNameToken() {
	yylval = (TOKEN) malloc(TOKENSIZE);
	yylval->token_t = TOKEN_NAME;
	yylval->name = (char *)malloc(strlen(yytext)+1);
	strcpy(yylval->name, yytext);
	return NAME;
}

int makeStrToken() {
	yylval = (TOKEN) malloc(TOKENSIZE);
	yylval->data_t = DATA_STR;
	yylval->tokenval.strval = (char *) malloc(strlen(yytext)-2+1);
	memcpy(yylval->tokenval.strval, yytext+1, strlen(yytext)-2);
	*(yylval->tokenval.strval+strlen(yytext)-2) = '\0';
	return STR;
}

int makeIntToken() {
	yylval = (TOKEN) malloc(TOKENSIZE);
	yylval->data_t = DATA_INT;
	yylval->tokenval.intval = atoi(yytext);
	return INTEGER;
}

int makeRealToken() {
	yylval = (TOKEN) malloc(TOKENSIZE);
	yylval->data_t = DATA_REAL;
	yylval->tokenval.realval = atof(yytext);
	return REAL;
}

int makeCharToken() {
	yylval = (TOKEN) malloc(TOKENSIZE);
	yylval->data_t = DATA_CHAR;
	yylval->tokenval.charval = yytext[1];
	return CHAR;
}

// int makeToken(tokenType tok_t, dataType dat_t, int t) {
// 	yylval = (TOKEN) malloc(TOKENSIZE);
// 	yylval->token_t = tok_t;
// 	switch(tok_t) {
// 		case OPERATOR:
// 			break;
// 		case DELIMITER:
// 			break;
// 		case RESERVED:
// 			break;
// 		case TOKEN_NAME:
// 			yylval->tokenval.strval = (char *) malloc(strlen(yytext));
// 			strcpy(yylval->tokenval.strval, yytext);
// 			return NAME;
// 			break;
// 		case TOKEN_STR:

// 			yylval->tokenval.strval = (char *) malloc(strlen(yytext)+1-2);
// 			memcpy(yylval->tokenval.strval, yytext+1, strlen(yytext)-2);
// 			*(yylval->tokenval.strval+strlen(yytext))
// 			return STR;
// 			break;
// 		case TOKEN_NUM:
// 			yylval->data_t = dat_t;
// 			if(dat_t == DATA_INT){
// 				yylval->tokenval.intval = atoi(yytext);
// 				return INTEGER;
// 			}
// 			else if(dat_t == DATA_REAL){
// 				yylval->tokenval.realval = atof(yytext);
// 				return REAL;
// 			}
// 			else
// 				return 0;
// 			break;
// 		case TOKEN_CHAR:
// 			yylval->tokenval.charval = yytext[1];
// 			break;
// 	}

// 	return t;
// }

int yywrap(void){return 1;} 

int main(int argc, char* argv[]) {
    yylex();
    printf("%d\n", line_num);
    return 0;
}