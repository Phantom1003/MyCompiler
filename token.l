%{  
#include <stdio.h>

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

"
{lp}            {return makeToken(yytext, LP);}
{rp}            {return makeToken(yytext, RP);}
{lb}            {return makeToken(yytext, LB);}
{rb}            {return makeToken(yytext, RB);}
{dotdot}        {return makeToken(yytext, DOTDOT);}
{comma}         {return makeToken(yytext, COMMA);}
{colon}         {return makeToken(yytext, COLON);}
{semi}          {return makeToken(yytext, SEMI);}


{plus}          {return makeToken(yytext, PLUS);}
{minus}         {return makeToken(yytext, MINUS);}
{mul}           {return makeToken(yytext, MUL);}
{div}           {return makeToken(yytext, DIV);}
{mod}           {return makeToken(yytext, MOD);}
{ge}            {return makeToken(yytext, GE);}
{gt}            {return makeToken(yytext, GT);}
{le}            {return makeToken(yytext, LE);}
{lt}            {return makeToken(yytext, LT);}
{equal}         {return makeToken(yytext, EQUAL);}
{unequal}       {return makeToken(yytext, UNEQUAL);}
{assign}        {return makeToken(yytext, ASSIGN);}
{dot}        	{return makeToken(yytext, DOT);}
{and}           {return makeToken(yytext, AND);}
{or}            {return makeToken(yytext, OR);}
{not}           {return makeToken(yytext, NOT);}


{sys_con}       {return makeToken(yytext, SYS_CON);}
{sys_funct}     {return makeToken(yytext, SYS_FUNCT);}   
{sys_proc}      {return makeToken(yytext, SYS_PROC);}
{sys_type}      {return makeToken(yytext, SYS_TYPE);}
{read}          {return makeToken(yytext, READ);}

{array}         {return makeToken(yytext, ARRAY);}
{begin}         {return makeToken(yytext, BEGIN_TOKEN);}
{case}          {return makeToken(yytext, CASE);}
{const}         {return makeToken(yytext, CONST);}
{do}            {return makeToken(yytext, DO);}
{downto}        {return makeToken(yytext, DOWNTO);}
{else}          {return makeToken(yytext, ELSE);}
{end}           {return makeToken(yytext, END);}
{for}           {return makeToken(yytext, FOR);}
{function}      {return makeToken(yytext, FUNCTION);}
{goto}          {return makeToken(yytext, GOTO);}
{if}            {return makeToken(yytext, IF);}
{in}            {return makeToken(yytext, IN);}
{of}            {return makeToken(yytext, OF);}
{packed}        {return makeToken(yytext, PACKED);}
{procedure}     {return makeToken(yytext, PROCEDURE);}
{program}       {return makeToken(yytext, PROGRAM);}
{record}        {return makeToken(yytext, RECORD);}
{repeat}        {return makeToken(yytext, REPEAT);}
{set}           {return makeToken(yytext, SET);}
{then}          {return makeToken(yytext, THEN);}
{to}            {return makeToken(yytext, TO);}
{type}          {return makeToken(yytext, TYPE);}
{until}         {return makeToken(yytext, UNTIL);}
{var}           {return makeToken(yytext, VAR);}
{while}         {return makeToken(yytext, WHILE);}
{with}          {return makeToken(yytext, WITH);}


{name}          {return makeToken(yytext, NAME);}
{integer}       {return makeToken(yytext, INTEGER);}
{real}          {return makeToken(yytext, REAL);}
{char}          {return makeToken(yytext, CHAR);}
{str}			{return makeToken(yytext, STR);}

[\n]            {line_num++;}
{whitespace}    {/*do nothing*/}
%%


int makeToken(char * str, int t) {
	yylval.content = new std::string(str);
	yylval.type = t;
	return t;
}

// int makeNameToken() {
// 	yylval = (TOKEN) malloc(TOKENSIZE);
// 	yylval->token_t = TOKEN_NAME;
// 	yylval->name = (char *)malloc(strlen(yytext)+1);
// 	strcpy(yylval->name, yytext);
// 	return NAME;
// }

// int makeStrToken() {
// 	yylval = (TOKEN) malloc(TOKENSIZE);
// 	yylval->data_t = DATA_STR;
// 	yylval->tokenval.strval = (char *) malloc(strlen(yytext)-2+1);
// 	memcpy(yylval->tokenval.strval, yytext+1, strlen(yytext)-2);
// 	*(yylval->tokenval.strval+strlen(yytext)-2) = '\0';
// 	return STR;
// }

// int makeIntToken() {
// 	yylval = (TOKEN) malloc(TOKENSIZE);
// 	yylval->data_t = DATA_INT;
// 	yylval->tokenval.intval = atoi(yytext);
// 	return INTEGER;
// }

// int makeRealToken() {
// 	yylval = (TOKEN) malloc(TOKENSIZE);
// 	yylval->data_t = DATA_REAL;
// 	yylval->tokenval.realval = atof(yytext);
// 	return REAL;
// }

// int makeCharToken() {
// 	yylval = (TOKEN) malloc(TOKENSIZE);
// 	yylval->data_t = DATA_CHAR;
// 	yylval->tokenval.charval = yytext[1];
// 	return CHAR;
// }

int yywrap(void){return 1;} 

int main(int argc, char* argv[]) {
    yylex();
    printf("%d\n", line_num);
    return 0;
}