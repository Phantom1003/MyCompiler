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
	PROGRAM NAME SEMI { $$ = new programHead($2, $1);}
;
routine: 
	routine_head routine_body {$$ = new Routine($1, $2);}
;
sub_routine: 
	routine_head routine_body {$$ = new subRoutine($1, $2);}
;
routine_head: 
	label_part const_part type_part var_part routine_part {$$ = new routineHead($1, $2, $3, $4, $5);}
;
label_part: 
	epsilon {$$ = new labelPart(?);}
;
const_part: 
	CONST const_expr_list {$$ = new constPart($1, $2);}
  | epsilon {}
;
const_expr_list: 
	const_expr_list NAME EQUAL const_value SEMI {$$ = new constExprList(?);}
  | NAME EQUAL const_value SEMI {$$ = new constExprList(?);}
;
const_value: 
	INTEGER {$$ = new constValue(?);}
  | REAL {$$ = new constValue(?);}
  | CHAR {$$ = new constValue(?);}
  | STRING {$$ = new constValue(?);}
  | SYS_CON {$$ = new constValue(?);}
;
type_part: 
	TYPE type_decl_list {$$ = new typePart(?);}
  | epsilon{$$ = new typePart(?);}
;
type_decl_list: 
	type_decl_list type_definition {$$ = new typeDeclList(?);}
  | type_definition {$$ = new typeDeclList(?);}
;
type_definition: 
	NAME EQUAL type_decl SEMI {$$ = new typeDefinition(?);}
;
type_decl:
    simple_type_decl {$$ = new typeDecl(?);}
  | array_type_decl {$$ = new typeDecl(?);}
  | record_type_decl {$$ = new typeDecl(?);}
;
simple_type_decl: 
    SYS_TYPE {$$ = new simpleTypeDecl(?);}
  | NAME {$$ = new simpleTypeDecl(?);}
  | LP name_list RP {$$ = new simpleTypeDecl(?);}
  | const_value DOTDOT const_value {$$ = new simpleTypeDecl(?);}
  | MINUS const_value DOTDOT const_value {$$ = new simpleTypeDecl(?);}
  | MINUS const_value DOTDOT MINUS const_value {$$ = new simpleTypeDecl(?);}
  | NAME  DOTDOT  NAME {$$ = new simpleTypeDecl(?);}
;
array_type_decl:
    ARRAY LB simple_type_decl RB OF type_decl {$$ = new arrayTypeDecl(?);}
;
record_type_decl:
    RECORD field_decl_list END {$$ = new recordTypeDecl(?);}
;
field_decl_list:
    field_decl_list field_decl {$$ = new fieldDeclList(?);}
  | field_decl {$$ = new fieldDeclList(?);}
;
field_decl:
    name_list COLON type_decl SEMI {$$ = new fieldDecl(?);}
;
name_list:
    name_list COMMA NAME {$$ = new nameList(?);}
  | NAME {$$ = new nameList(?);}
;
var_part: 
	VAR var_decl_list {$$ = new varPart(?);}
  | epsilon {}
;
var_decl_list :
    var_decl_list var_decl {$$ = new varDeclList(?);}
  | var_decl {$$ = new varDeclList(?);}
;
var_decl:
    name_list COLON type_decl  SEMI {$$ = new varDecl(?);}
;
routine_part: 
	routine_part function_decl  {$$ = new routinePart(?);}
  | routine_part procedure_decl {$$ = new routinePart(?);}
  | function_decl {$$ = new routinePart(?);}
  | procedure_decl {$$ = new routinePart(?);}  
  | epsilon {$$ = new routinePart(?);}
;
function_decl :
    function_head SEMI sub_routine SEMI {$$ = new functionDecl(?);}
;
function_head :
    FUNCTION NAME parameters COLON simple_type_decl {$$ = new functionHead(?);}
;
procedure_decl :
    procedure_head SEMI sub_routine SEMI {$$ = new procedureDecl(?);}
;
procedure_head :
    PROCEDURE NAME parameters {$$ = new procedureHead(?);}
;
parameters:
    LP para_decl_list RP {$$ = new Parameters(?);}
  | epsilon {}
;
para_decl_list:
    para_decl_list SEMI para_type_list {$$ = new paraDeclList(?);}
  | para_type_list {$$ = new paraDeclList(?);}
;
para_type_list:
    var_para_list COLON simple_type_decl {$$ = new paraTypeList(?);}
;
var_para_list:
    VAR name_list {$$ = new varParaList(?);}
  | name_list {$$ = new varParaList(?);}
;
routine_body: 
	compound_stmt {$$ = new routineBody(?);}
;
compound_stmt: 
	BEGIN stmt_list END {$$ = new compoundStmt(?);}
;
stmt_list:
    stmt_list stmt SEMI {}
  | epsilon {}
;
stmt:
    INTEGER COLON non_label_stmt {}
  | non_label_stmt {}
;
non_label_stmt:
    assign_stmt {}
  | proc_stmt {}
  | compound_stmt {}
  | if_stmt {}
  | repeat_stmt {}
  | while_stmt {}
  | for_stmt {}
  | case_stmt {}
  | goto_stmt {}
;
assign_stmt: 
	NAME ASSIGN expression {}
  | NAME LB expression RB ASSIGN expression {}
  | NAME DOT NAME ASSIGN expression {}
;
proc_stmt:     
	NAME {}
  | NAME LP args_list RP {}
  | SYS_PROC {}
  | SYS_PROC LP expression_list RP {}
  | READ LP factor RP {}
;
if_stmt: 
	IF expression THEN stmt else_clause {}
;
else_clause:
    ELSE stmt  {}
  | epsilon {}
;
repeat_stmt: 
	REPEAT stmt_list UNTIL expression {}
;
while_stmt: 
	WHILE expression DO stmt {}
;
for_stmt:     
	FOR NAME ASSIGN expression direction expression DO stmt {}
;
direction:     
	TO {}
  | DOWNTO {}
;
case_stmt:     
	CASE expression OF case_expr_list END {}
;
case_expr_list: 
	case_expr_list case_expr {}
  | case_expr {}
;
case_expr:     
	const_value COLON stmt SEMI {}
  | NAME COLON stmt SEMI {}
;
goto_stmt: 
	GOTO  INTEGER {} 
;
expression_list: 
	expression_list COMMA expression {}
  | expression { }
;
expression: 
	expression GE expr {}
  | expression GT expr {}
  | expression LE expr {}
  | expression LT expr {}
  | expression EQUAL expr {}
  | expression UNEQUAL expr {}
  | expr {}
;
expr: 
	expr PLUS term {}
  | expr MINUS term {}
  | expr OR term {}
  | term {}
;
term: 
	term MUL factor {}
  | term DIV factor {}
  | term MOD factor {}
  | term AND factor {}
  | factor {}
;
factor:
	NAME {}
  | NAME LP args_list RP {}
  | SYS_FUNCT {}
  | SYS_FUNCT  LP  args_list  RP {}
  | const_value {}
  | LP expression RP {}
  | NOT factor {}
  | MINUS factor {}
  | NAME LB expression RB {}
  | NAME DOT NAME {}
;
args_list:
	args_list COMMA expression {}
  | expression {}

epsilon: {}

%%




