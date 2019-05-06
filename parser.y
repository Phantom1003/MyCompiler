%{
#include "AST.hpp"

#define YYERROR_VERBOSE 1
#define YYDEBUG 1

extern int yylex();
extern int yylineno;
Program * astRoot;
extern char * yytext;

void yyerror (char const *msg) {
  std::cerr << "[yyerror]: " << std::string(msg) << " yytext: [" << std::string(yytext) << "] Line: " << yylineno << std::endl;
}

%}

%union {
  int type;
  std::string * content;
   
  Program*     program;
  ProgramHead* programHead;
  Routine*     routine;
  RoutineHead* routineHead;
  SubRoutine*  subRoutine;
  LabelPart*   labelPart;
  ConstPart*   constPart;
  ConstExprList*  constExprList;
  ConstValue*     constValue;
  TypePart*       typePart;
  TypeDeclList*   typeDeclList;
  TypeDefinition* typeDefinition;
  TypeDecl*       typeDecl;
  SimpleTypeDecl* simpleTypeDecl;
  ArrayTypeDecl*  arrayTypeDecl;
  RecordTypeDecl* recordTypeDecl;
  FieldDeclList*  fieldDeclList;
  FieldDecl*   fieldDecl;
  NameList*    nameList;
  VarPart*     varPart;
  VarDeclList* varDeclList;
  VarDecl*     varDecl;
  RoutinePart* routinePart;
  FunctionDecl*  functionDecl;
  FunctionHead*  functionHead;
  ProcedureDecl* procedureDecl;
  ProcedureHead* procedureHead;
  Parameters*    parameters;
  ParaDeclList*  paraDeclList;
  ParaTypeList*  paraTypeList;
  VarParaList*   varParaList;
  ValParaList*   valParaList;
  RoutineBody*   routineBody;
  CompoundStmt*  compoundStmt;
  StmtList*      stmtList;
  Stmt*          stmt;
  NonLabelStmt*  nonLabelStmt;
  AssignStmt*    assignStmt;
  ProcStmt*      procStmt;
  IfStmt*        ifStmt;
  ElseClause* elseClause;
  RepeatStmt* repeatStmt;
  WhileStmt*  whileStmt;
  ForStmt*    forStmt;
  Direction*  direction;
  CaseStmt*   caseStmt;
  CaseExprList* caseExprList;
  CaseExpr*     caseExpr;
  GotoStmt*       gotoStmt;
  ExpressionList* expressionList;
  Expression*     expression;
  Expr*     expr;
  Term*     term;
  Factor*   factor;
  ArgsList* argsList;
}
%token NAME INTEGER REAL CHAR STRING
%token LP RP LB RB DOT COMMA COLON MUL DIV UNEQUAL NOT PLUS MINUS
%token GE GT LE LT EQUAL ASSIGN MOD DOTDOT SEMI SYS_CON SYS_FUNCT 
%token SYS_PROC SYS_TYPE READ AND ARRAY BEGIN_T END
%token CASE CONST DO DOWNTO ELSE FOR FUNCTION GOTO IF IN OF OR PACKED
%token PROCEDURE PROGRAM RECORD REPEAT SET THEN TO TYPE UNTIL VAR WHILE WITH

%type <program>     program
%type <programHead> program_head
%type <routine>     routine
%type <routineHead> routine_head
%type <subRoutine>  sub_routine
%type <labelPart>   label_part
%type <constPart>   const_part
%type <constExprList>  const_expr_list
%type <constValue>     const_value
%type <typePart>       type_part
%type <typeDeclList>   type_decl_list
%type <typeDefinition> type_definition
%type <typeDecl>       type_decl
%type <simpleTypeDecl> simple_type_decl
%type <arrayTypeDecl>  array_type_decl
%type <recordTypeDecl> record_type_decl
%type <fieldDeclList>  field_decl_list
%type <fieldDecl>   field_decl
%type <nameList>    name_list
%type <varPart>     var_part
%type <varDeclList> var_decl_list
%type <varDecl>     var_decl
%type <routinePart> routine_part
%type <functionDecl>  function_decl
%type <functionHead>  function_head
%type <procedureDecl> procedure_decl
%type <procedureHead> procedure_head
%type <parameters>    parameters
%type <paraDeclList> para_decl_list
%type <paraTypeList> para_type_list
%type <varParaList>  var_para_list
%type <valParaList>  val_para_list
%type <routineBody>  routine_body
%type <compoundStmt> compound_stmt
%type <stmtList>     stmt_list
%type <stmt>         stmt
%type <nonLabelStmt> non_label_stmt
%type <assignStmt>   assign_stmt
%type <procStmt>   proc_stmt
%type <ifStmt>     if_stmt
%type <elseClause> else_clause
%type <repeatStmt> repeat_stmt
%type <whileStmt>  while_stmt
%type <forStmt>    for_stmt
%type <direction>  direction
%type <caseStmt>   case_stmt
%type <caseExprList> case_expr_list
%type <caseExpr>     case_expr
%type <gotoStmt>     goto_stmt
%type <expressionList> expression_list
%type <expression>     expression
%type <expr>     expr
%type <term>     term
%type <factor>   factor
%type <argsList> args_list



%%
program: 
	program_head routine DOT  {astRoot = new Program($1, $2);}
;
program_head: 
	PROGRAM NAME SEMI         {$$ = new ProgramHead(*$<content>2);}
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
  | epsilon               {$$ = new ConstPart();}
;
const_expr_list: 
	  const_expr_list NAME EQUAL const_value SEMI {$$ = new ConstExprList(*$<content>2, $1, $4);}
  | NAME EQUAL const_value SEMI                 {$$ = new ConstExprList(*$<content>1, $3);}
;
const_value: 
	  INTEGER {$$ = new ConstValue($<type>1, *$<content>1);}
  | REAL    {$$ = new ConstValue($<type>1, *$<content>1);}
  | CHAR    {$$ = new ConstValue($<type>1, *$<content>1);}
  | STRING  {$$ = new ConstValue($<type>1, *$<content>1);}
  | SYS_CON {$$ = new ConstValue($<type>1, *$<content>1);}
;
type_part: 
    TYPE type_decl_list {$$ = new TypePart($2);}
  | epsilon             {$$ = new TypePart();}
;
type_decl_list: 
    type_decl_list type_definition {$$ = new TypeDeclList($1, $2);}
  | type_definition                {$$ = new TypeDeclList($1);}
;
type_definition: 
	NAME EQUAL type_decl SEMI {$$ = new TypeDefinition(*$<content>1, $3);}
;
type_decl:
    simple_type_decl {$$ = new TypeDecl($1);}
  | array_type_decl  {$$ = new TypeDecl($1);}
  | record_type_decl {$$ = new TypeDecl($1);}
;
simple_type_decl: 
    SYS_TYPE                       {$$ = new SimpleTypeDecl($<type>1, *$<content>1);}
  | NAME                           {$$ = new SimpleTypeDecl($<type>1, *$<content>1);}
  | LP name_list RP                {$$ = new SimpleTypeDecl($2);}
  | const_value DOTDOT const_value {$$ = new SimpleTypeDecl($1, $3);}
  | MINUS const_value DOTDOT const_value       {$$ = new SimpleTypeDecl($2->neg(), $4);}
  | MINUS const_value DOTDOT MINUS const_value {$$ = new SimpleTypeDecl($2->neg(), $5->neg());}
  | NAME  DOTDOT  NAME                         {$$ = new SimpleTypeDecl(*$<content>1, *$<content>3);}
;
array_type_decl:
    ARRAY LB simple_type_decl RB OF type_decl {$$ = new ArrayTypeDecl($3, $6);}
;
record_type_decl:
    RECORD field_decl_list END {$$ = new RecordTypeDecl($2);}
;
field_decl_list:
    field_decl_list field_decl {$$ = new FieldDeclList($1, $2);}
  | field_decl                 {$$ = new FieldDeclList($1);}
;
field_decl:
    name_list COLON type_decl SEMI {$$ = new FieldDecl($1, $3);}
;
name_list:
    name_list COMMA NAME {$$ = new NameList(*$<content>3, $1);}
  | NAME                 {$$ = new NameList(*$<content>1);}
;
var_part: 
	  VAR var_decl_list {$$ = new VarPart($2);}
  | epsilon           {$$ = new VarPart();}
;
var_decl_list :
    var_decl_list var_decl {$$ = new VarDeclList($1, $2);}
  | var_decl               {$$ = new VarDeclList($1);}
;
var_decl:
    name_list COLON type_decl SEMI {$$ = new VarDecl($1, $3);}
;
routine_part: 
	routine_part function_decl    {$$ = new RoutinePart($1, $2);}
  | routine_part procedure_decl {$$ = new RoutinePart($1, $2);}
  | function_decl               {$$ = new RoutinePart($1);}
  | procedure_decl              {$$ = new RoutinePart($1);}  
  | epsilon                     {$$ = new RoutinePart();}
;
function_decl :
    function_head SEMI sub_routine SEMI {$$ = new FunctionDecl($1, $3);}
;
function_head :
    FUNCTION NAME parameters COLON simple_type_decl {$$ = new FunctionHead(*$<content>2, $3, $5);}
;
procedure_decl :
    procedure_head SEMI sub_routine SEMI {$$ = new ProcedureDecl($1, $3);}
;
procedure_head :
    PROCEDURE NAME parameters {$$ = new ProcedureHead(*$<content>2, $3);}
;
parameters:
    LP para_decl_list RP {$$ = new Parameters($2);}
  | epsilon              {$$ = new Parameters( );}
;
para_decl_list:
    para_decl_list SEMI para_type_list {$$ = new ParaDeclList($1, $3);}
  | para_type_list                     {$$ = new ParaDeclList($1);}
;
para_type_list:
    var_para_list COLON simple_type_decl {$$ = new ParaTypeList($1, $3);}
  | val_para_list COLON simple_type_decl {$$ = new ParaTypeList($1, $3);}
;
var_para_list:
    VAR name_list {$$ = new VarParaList($2);}
;
val_para_list:
   name_list      {$$ = new ValParaList($1);}
;
routine_body: 
	compound_stmt   {$$ = new RoutineBody($1);}
;
compound_stmt: 
	BEGIN_T stmt_list END {$$ = new CompoundStmt($2);}
;
stmt_list:
    stmt_list stmt SEMI {$$ = new StmtList($1, $2);}
  | epsilon             {$$ = new StmtList();}
;
stmt:
    INTEGER COLON non_label_stmt {$$ = new Stmt($3);}
  | non_label_stmt               {$$ = new Stmt($1);}
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
	  NAME ASSIGN expression                  {$$ = new AssignStmt(*$<content>1, $3);}
  | NAME LB expression RB ASSIGN expression {$$ = new AssignStmt(*$<content>1, $3, $6);}
  | NAME DOT NAME ASSIGN expression         {$$ = new AssignStmt(*$<content>1, *$<content>3, $5);}
;
proc_stmt:     
	  NAME                           {$$ = new ProcStmt($<type>1, *$<content>1);}
  | NAME LP args_list RP           {$$ = new ProcStmt(*$<content>1, $3);}
  | SYS_PROC                       {$$ = new ProcStmt($<type>1, *$<content>1);}
  | SYS_PROC LP expression_list RP {$$ = new ProcStmt(*$<content>1, $3);}
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
	REPEAT stmt_list UNTIL expression {$$ = new RepeatStmt($2, $4);}
;
while_stmt: 
	WHILE expression DO stmt {$$ = new WhileStmt($2, $4);}
;
for_stmt:     
	FOR NAME ASSIGN expression direction expression DO stmt {$$ = new ForStmt(*$<content>2, $4, $5, $6, $8);}
;
direction:     
	  TO     {$$ = new Direction(*$<content>1);}
  | DOWNTO {$$ = new Direction(*$<content>1);}
;
case_stmt:     
	CASE expression OF case_expr_list END {$$ = new CaseStmt($2, $4);}
;
case_expr_list: 
	  case_expr_list case_expr {$$ = new CaseExprList($1, $2);}
  | case_expr                {$$ = new CaseExprList($1);}
;
case_expr:     
	  const_value COLON stmt SEMI {$$ = new CaseExpr($1, $3);}
  | NAME COLON stmt SEMI        {$$ = new CaseExpr(*$<content>1, $3);}
;
goto_stmt: 
	GOTO INTEGER {$$ = new GotoStmt(*$<content>2);} 
;
expression_list: 
	expression_list COMMA expression {$$ = new ExpressionList($1, $3);}
  | expression                     {$$ = new ExpressionList($1);}
;
expression: 
	  expression GE expr      {$$ = new Expression($1, *$<content>2, $3);}
  | expression GT expr      {$$ = new Expression($1, *$<content>2, $3);}
  | expression LE expr      {$$ = new Expression($1, *$<content>2, $3);}
  | expression LT expr      {$$ = new Expression($1, *$<content>2, $3);}
  | expression EQUAL expr   {$$ = new Expression($1, *$<content>2, $3);}
  | expression UNEQUAL expr {$$ = new Expression($1, *$<content>2, $3);}
  | expr                    {$$ = new Expression($1);}
;
expr: 
	  expr PLUS term  {$$ = new Expr($1, *$<content>2, $3);}
  | expr MINUS term {$$ = new Expr($1, *$<content>2, $3);}
  | expr OR term    {$$ = new Expr($1, *$<content>2, $3);}
  | term            {$$ = new Expr($1);}
;
term: 
	  term MUL factor {$$ = new Term($1, *$<content>2, $3);}
  | term DIV factor {$$ = new Term($1, *$<content>2, $3);}
  | term MOD factor {$$ = new Term($1, *$<content>2, $3);}
  | term AND factor {$$ = new Term($1, *$<content>2, $3);}
  | factor          {$$ = new Term($1);}
;
factor:
	  NAME                         {$$ = new Factor($<type>1, *$<content>1);}
  | NAME LP args_list RP         {$$ = new Factor($<type>1, *$<content>1, $3);}
  | SYS_FUNCT                    {$$ = new Factor($<type>1, *$<content>1);}
  | SYS_FUNCT  LP  args_list  RP {$$ = new Factor($<type>1, *$<content>1, $3);}
  | const_value                  {$$ = new Factor($1);}
  | LP expression RP             {$$ = new Factor($2);}
  | NOT factor                   {$$ = new Factor($<type>1, $2);}
  | MINUS factor                 {$$ = new Factor($<type>1, $2);}
  | NAME LB expression RB        {$$ = new Factor(*$<content>1, $3);}
  | NAME DOT NAME                {$$ = new Factor(*$<content>1, *$<content>3);}
;
args_list:
	  args_list COMMA expression {$$ = new ArgsList($1, $3);}
  | expression                 {$$ = new ArgsList($1);}

epsilon: { }

%%
