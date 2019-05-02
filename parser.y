%{
#include <iostream>
#include <string>
#include <math>

using namespace std;

void yyerror(const char *s) { 
	printf("[ERROR]: At line: %d\n 
			         %s\n ", yylineno, s); 
}

%}

%union {
	int type;
    string content;

}
%token NAME LP RP LB RB DOT COMMA COLON MUL DIV UNEQUAL NOT PLUS MINUS
%token GE GT LE LT EQUAL ASSIGN MOD DOTDOT SEMI SYS_CON SYS_FUNCT 
%token SYS_PROC SYS_TYPE READ INTEGER REAL CHAR STRING AND ARRAY BEGIN_TOKEN
%token CASE CONST DO DOWNTO ELSE END FOR FUNCTION GOTO IF IN OF OR PACKED
%token PROCEDURE PROGRAM RECORD REPEAT SET THEN TO TYPE UNTIL VAR WHILE WITH

%%
program: 
	program_head routine DOT {$$ = new Program($1, $2);}
;
program_head: 
	PROGRAM NAME SEMI { $$ = new ProgramHead($2.content);}
;
routine: 
	routine_head routine_body {$$ = new Routine($1, $2);}
;
sub_routine: 
	routine_head routine_body {$$ = new SubRoutine($1, $2);}
;
routine_head: 
	label_part const_part type_part var_part routine_part {$$ = new RoutineHead($1, $2, $3, $4, $5);}
;
label_part: 
	epsilon {$$ = new LabelPart();}
;
const_part: 
	CONST const_expr_list {$$ = new ConstPart($2);}
  | epsilon {$$ = new ConstPart();}
;
const_expr_list: 
	const_expr_list NAME EQUAL const_value SEMI {$$ = new ConstExprList($2.content, $1, $4);}
  | NAME EQUAL const_value SEMI {$$ = new ConstExprList($1.content, $3);}
;
const_value: 
	INTEGER {$$ = new ConstValue($1.type, $1.content);}
  | REAL    {$$ = new ConstValue($1.type, $1.content);}
  | CHAR    {$$ = new ConstValue($1.type, $1.content);}
  | STRING  {$$ = new ConstValue($1.type, $1.content);}
  | SYS_CON {$$ = new ConstValue($1.type, $1.content);}
;
type_part: 
	TYPE type_decl_list {$$ = new TypePart($1);}
  | epsilon{$$ = new TypePart();}
;
type_decl_list: 
	type_decl_list type_definition {$$ = new TypeDeclList($1, $2);}
  | type_definition {$$ = new TypeDeclList($1);}
;
type_definition: 
	NAME EQUAL type_decl SEMI {$$ = new TypeDefinition($1.content, $3);}
;
type_decl:
    simple_type_decl {$$ = new TypeDecl($1);}
  | array_type_decl  {$$ = new TypeDecl($1);}
  | record_type_decl {$$ = new TypeDecl($1);}
;
simple_type_decl: 
    SYS_TYPE {$$ = new SimpleTypeDecl($1.type, $1.content);}
  | NAME {$$ = new SimpleTypeDecl($1.type, $1.content);}
  | LP name_list RP {$$ = new SimpleTypeDecl($2);}
  | const_value DOTDOT const_value {$$ = new SimpleTypeDecl($1, $3);}
  | MINUS const_value DOTDOT const_value {$$ = new SimpleTypeDecl($2->neg(), $4);}
  | MINUS const_value DOTDOT MINUS const_value {$$ = new SimpleTypeDecl($2->neg(), $4->neg());}
  | NAME  DOTDOT  NAME {$$ = new SimpleTypeDecl($1.content, $3.content);}
;
array_type_decl:
    ARRAY LB simple_type_decl RB OF type_decl {$$ = new ArrayTypeDecl($3, $6);}
;
record_type_decl:
    RECORD field_decl_list END {$$ = new RecordTypeDecl($2);}
;
field_decl_list:
    field_decl_list field_decl {$$ = new FieldDeclList($1, $2);}
  | field_decl {$$ = new FieldDeclList($1);}
;
field_decl:
    name_list COLON type_decl SEMI {$$ = new FieldDecl($1, $3);}
;
name_list:
    name_list COMMA NAME {$$ = new NameList($3.content, $1);}
  | NAME {$$ = new NameList($1.content);}
;
var_part: 
	VAR var_decl_list {$$ = new VarPart($2);}
  | epsilon {$$ = new VarPart();}
;
var_decl_list :
    var_decl_list var_decl {$$ = new VarDeclList($1, $2);}
  | var_decl {$$ = new VarDeclList($1);}
;
var_decl:
    name_list COLON type_decl  SEMI {$$ = new VarDecl($1, $3);}
;
routine_part: 
	routine_part function_decl  {$$ = new RoutinePart($1, $2);}
  | routine_part procedure_decl {$$ = new RoutinePart($1, $2);}
  | function_decl {$$ = new RoutinePart($1);}
  | procedure_decl {$$ = new RoutinePart($1);}  
  | epsilon {$$ = new RoutinePart();}
;
function_decl :
    function_head SEMI sub_routine SEMI {$$ = new FunctionDecl($1, $3);}
;
function_head :
    FUNCTION NAME parameters COLON simple_type_decl {$$ = new FunctionHead($2.content, $3, $5);}
;
procedure_decl :
    procedure_head SEMI sub_routine SEMI {$$ = new ProcedureDecl($1, $3);}
;
procedure_head :
    PROCEDURE NAME parameters {$$ = new ProcedureHead($2.content, $3);}
;
parameters:
    LP para_decl_list RP {$$ = new Parameters($2);}
  | epsilon {$$ = new Parameters( );}
;
para_decl_list:
    para_decl_list SEMI para_type_list {$$ = new ParaDeclList($1, $3);}
  | para_type_list {$$ = new ParaDeclList($1);}
;
para_type_list:
    var_para_list COLON simple_type_decl {$$ = new ParaTypeList($1, $3);}
  | val_para_list COLON simple_type_decl {$$ = new ParaTypeList($1, $3);}
;
var_para_list:
    VAR name_list {$$ = new VarParaList($2);}
;
val_para_list:
   name_list {$$ = new ValParaList($1);}
;
routine_body: 
	compound_stmt {$$ = new RoutineBody($1);}
;
compound_stmt: 
	BEGIN stmt_list END {$$ = new CompoundStmt($2);}
;
stmt_list:
    stmt_list stmt SEMI {$$ = new StmtList($1, $2);}
  | epsilon {$$ = new StmtList();}
;
stmt:
    INTEGER COLON non_label_stmt {$$ = new Stmt($3);}
  | non_label_stmt {$$ = new Stmt($1);}
;
non_label_stmt:
    assign_stmt   {$$ = new NonLabelStmt($1);}
  | proc_stmt     {$$ = new NonLabelStmt($1);}
  | compound_stmt {$$ = new NonLabelStmt($1);}
  | if_stmt       {$$ = new NonLabelStmt($1);}
  | repeat_stmt   {$$ = new NonLabelStmt($1);}
  | while_stmt    {$$ = new NonLabelStmt($1);}
  | for_stmt      {$$ = new NonLabelStmt($1);}
  | case_stmt     {$$ = new NonLabelStmt($1);}
  | goto_stmt     {$$ = new NonLabelStmt($1);}
;
assign_stmt: 
	NAME ASSIGN expression                  {$$ = new AssignStmt($1.content, $3);}
  | NAME LB expression RB ASSIGN expression {$$ = new AssignStmt($1.content, $3, $6);}
  | NAME DOT NAME ASSIGN expression         {$$ = new AssignStmt($1.content, $3.content, $5);}
;
proc_stmt:     
	NAME                           {$$ = new ProcStmt($1.content);}
  | NAME LP args_list RP           {$$ = new ProcStmt($1.content, $3);}
  | SYS_PROC                       {$$ = new ProcStmt($1.content);}
  | SYS_PROC LP expression_list RP {$$ = new ProcStmt($1.content, $3);}
  | READ LP factor RP              {$$ = new ProcStmt($3);}
;
if_stmt: 
	IF expression THEN stmt else_clause {$$ = new IfStmt($2, $4, $5);}
;
else_clause:
    ELSE stmt  {$$ = new ElseClause($2);}
  | epsilon    {$$ = new ElseClause();}
;
repeat_stmt: 
	REPEAT stmt_list UNTIL expression {$$ = new RepeatStmt();}
;
while_stmt: 
	WHILE expression DO stmt {$$ = new ();}
;
for_stmt:     
	FOR NAME ASSIGN expression direction expression DO stmt {$$ = new ();}
;
direction:     
	TO {$$ = new ();}
  | DOWNTO {$$ = new ();}
;
case_stmt:     
	CASE expression OF case_expr_list END {$$ = new ();}
;
case_expr_list: 
	case_expr_list case_expr {$$ = new ();}
  | case_expr {$$ = new ();}
;
case_expr:     
	const_value COLON stmt SEMI {$$ = new ();}
  | NAME COLON stmt SEMI {$$ = new ();}
;
goto_stmt: 
	GOTO  INTEGER {$$ = new ();} 
;
expression_list: 
	expression_list COMMA expression {$$ = new ();}
  | expression { }
;
expression: 
	expression GE expr {$$ = new ();}
  | expression GT expr {$$ = new ();}
  | expression LE expr {$$ = new ();}
  | expression LT expr {$$ = new ();}
  | expression EQUAL expr {$$ = new ();}
  | expression UNEQUAL expr {$$ = new ();}
  | expr {$$ = new ();}
;
expr: 
	expr PLUS term {$$ = new ();}
  | expr MINUS term {$$ = new ();}
  | expr OR term {$$ = new ();}
  | term {$$ = new ();}
;
term: 
	term MUL factor {$$ = new ();}
  | term DIV factor {$$ = new ();}
  | term MOD factor {$$ = new ();}
  | term AND factor {$$ = new ();}
  | factor {$$ = new ();}
;
factor:
	NAME {$$ = new ();}
  | NAME LP args_list RP {$$ = new ();}
  | SYS_FUNCT {$$ = new ();}
  | SYS_FUNCT  LP  args_list  RP {$$ = new ();}
  | const_value {$$ = new ();}
  | LP expression RP {$$ = new ();}
  | NOT factor {$$ = new ();}
  | MINUS factor {$$ = new ();}
  | NAME LB expression RB {$$ = new ();}
  | NAME DOT NAME {$$ = new ();}
;
args_list:
	args_list COMMA expression {$$ = new ();}
  | expression {$$ = new ();}

epsilon: {$$ = new ();}

%%




