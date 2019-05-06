/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NAME = 258,
     INTEGER = 259,
     REAL = 260,
     CHAR = 261,
     STRING = 262,
     LP = 263,
     RP = 264,
     LB = 265,
     RB = 266,
     DOT = 267,
     COMMA = 268,
     COLON = 269,
     MUL = 270,
     DIV = 271,
     UNEQUAL = 272,
     NOT = 273,
     PLUS = 274,
     MINUS = 275,
     GE = 276,
     GT = 277,
     LE = 278,
     LT = 279,
     EQUAL = 280,
     ASSIGN = 281,
     MOD = 282,
     DOTDOT = 283,
     SEMI = 284,
     SYS_CON = 285,
     SYS_FUNCT = 286,
     SYS_PROC = 287,
     SYS_TYPE = 288,
     READ = 289,
     AND = 290,
     ARRAY = 291,
     BEGIN_T = 292,
     END = 293,
     CASE = 294,
     CONST = 295,
     DO = 296,
     DOWNTO = 297,
     ELSE = 298,
     FOR = 299,
     FUNCTION = 300,
     GOTO = 301,
     IF = 302,
     IN = 303,
     OF = 304,
     OR = 305,
     PACKED = 306,
     PROCEDURE = 307,
     PROGRAM = 308,
     RECORD = 309,
     REPEAT = 310,
     SET = 311,
     THEN = 312,
     TO = 313,
     TYPE = 314,
     UNTIL = 315,
     VAR = 316,
     WHILE = 317,
     WITH = 318
   };
#endif
/* Tokens.  */
#define NAME 258
#define INTEGER 259
#define REAL 260
#define CHAR 261
#define STRING 262
#define LP 263
#define RP 264
#define LB 265
#define RB 266
#define DOT 267
#define COMMA 268
#define COLON 269
#define MUL 270
#define DIV 271
#define UNEQUAL 272
#define NOT 273
#define PLUS 274
#define MINUS 275
#define GE 276
#define GT 277
#define LE 278
#define LT 279
#define EQUAL 280
#define ASSIGN 281
#define MOD 282
#define DOTDOT 283
#define SEMI 284
#define SYS_CON 285
#define SYS_FUNCT 286
#define SYS_PROC 287
#define SYS_TYPE 288
#define READ 289
#define AND 290
#define ARRAY 291
#define BEGIN_T 292
#define END 293
#define CASE 294
#define CONST 295
#define DO 296
#define DOWNTO 297
#define ELSE 298
#define FOR 299
#define FUNCTION 300
#define GOTO 301
#define IF 302
#define IN 303
#define OF 304
#define OR 305
#define PACKED 306
#define PROCEDURE 307
#define PROGRAM 308
#define RECORD 309
#define REPEAT 310
#define SET 311
#define THEN 312
#define TO 313
#define TYPE 314
#define UNTIL 315
#define VAR 316
#define WHILE 317
#define WITH 318




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 18 "parser.y"
{
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
/* Line 1529 of yacc.c.  */
#line 236 "yac.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

