%{  
#include <stdio.h>  

enum TokenType {
    NAME, 
    LP, RP, LB, RB, DOT, COMMA, COLON, MUL, DIV, UNEQUAL, NOT, PLUS, MINUS, GE, GT, LE, LT, EQUAL, ASSIGN, MOD, DOTDOT, SEMI, 
    SYS_CON, SYS_FUNCT, SYS_PROC, SYS_TYPE, READ,
    INTEGER, REAL, CHAR,
    AND, ARRAY, BEGIN_TOKEN, CASE, CONST, DO, DOWNTO, ELSE, END, FOR, FUNCTION, GOTO, IF, IN, OF, OR, PACKED, PROCEDURE, 
    PROGRAM, RECORD, REPEAT, SET, THEN, TO, TYPE, UNTIL, VAR, WHILE, WITH    
};

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
char        {"'"[a-zA-Z]"'"}

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
{lp}            {return LP;}
{rp}            {return RP;}
{lb}            {return LB;}
{rb}            {return RB;}
{dot}           {return DOT;}
{comma}         {return COMMA;}
{colon}         {return COLON;}
{mul}           {return MUL;}
{div}           {return DIV;}
{unequal}       {return UNEQUAL;}
{not}           {return NOT;}
{plus}          {return PLUS;}
{minus}         {return MINUS;}
{ge}            {return GE;}
{gt}            {return GT;}
{le}            {return LE;}
{lt}            {return LT;}
{equal}         {return EQUAL;}
{assign}        {return ASSIGN;}
{mod}           {return MOD;}
{dotdot}        {return DOTDOT;}
{semi}          {return SEMI;}

{integer}       {return INTEGER;}
{real}          {return REAL;}
{char}          {return CHAR;}

{sys_con}       {return SYS_CON;}
{sys_funct}     {return SYS_FUNCT;}   
{sys_proc}      {return SYS_PROC;}
{sys_type}      {return SYS_TYPE;}
{read}          {return READ;}

{and}           {return AND;}
{array}         {return ARRAY;}
{begin}         {return BEGIN_TOKEN;}
{case}          {return CASE;}
{const}         {return CONST;}
{do}            {return DO;}
{downto}        {return DOWNTO;}
{else}          {return ELSE;}
{end}           {return END;}
{for}           {return FOR;}
{function}      {return FUNCTION;}
{goto}          {return GOTO;}
{if}            {return IF;}
{in}            {return IN;}
{mod}           {return MOD;}
{of}            {return OF;}
{or}            {return OR;}
{packed}        {return PACKED;}
{procedure}     {return PROCEDURE;}
{program}       {return PROGRAM;}
{record}        {return RECORD;}
{repeat}        {return REPEAT;}
{set}           {return SET;}
{then}          {return THEN;}
{to}            {return TO;}
{type}          {return TYPE;}
{until}         {return UNTIL;}
{var}           {return VAR;}
{while}         {return WHILE;}
{with}          {return WITH;}

{name}          {return NAME;}
[\n]            {line_num++;}
{whitespace}    {/*do nothing*/}
%%

int yywrap(void){return 1;} 

int main(int argc, char* argv[]) {
    yylex();
    return 0;
}