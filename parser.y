%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void yyerror(const char * msg){}
%}

// %union {
// 	int integer;
// 	double real;
// 	char ch;
// 	char * str
// }

%token <num_interger> INTEGER
%token <num_real> REAL
%token <ch> CHAR
%token NAME LP RP LB RB DOT COMMA COLON MUL DIV UNEQUAL NOT PLUS MINUS GE GT LE LT EQUAL ASSIGN MOD DOTDOT SEMI SYS_CON SYS_FUNCT SYS_PROC SYS_TYPE READ AND ARRAY BEGIN_TOKEN CASE CONST DO DOWNTO ELSE END FOR FUNCTION GOTO IF IN OF OR PACKED PROCEDURE PROGRAM RECORD REPEAT SET THEN TO TYPE UNTIL VAR WHILE WITH


%token NAME INTEGER REAL CHAR 
%token LP RP LB RB DOTDOT COMMA COLON SEMI