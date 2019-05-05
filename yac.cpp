/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NAME = 258,
     LP = 259,
     RP = 260,
     LB = 261,
     RB = 262,
     DOT = 263,
     COMMA = 264,
     COLON = 265,
     MUL = 266,
     DIV = 267,
     UNEQUAL = 268,
     NOT = 269,
     PLUS = 270,
     MINUS = 271,
     GE = 272,
     GT = 273,
     LE = 274,
     LT = 275,
     EQUAL = 276,
     ASSIGN = 277,
     MOD = 278,
     DOTDOT = 279,
     SEMI = 280,
     SYS_CON = 281,
     SYS_FUNCT = 282,
     SYS_PROC = 283,
     SYS_TYPE = 284,
     READ = 285,
     INTEGER = 286,
     REAL = 287,
     CHAR = 288,
     STRING = 289,
     AND = 290,
     ARRAY = 291,
     BEGIN_T = 292,
     CASE = 293,
     CONST = 294,
     DO = 295,
     DOWNTO = 296,
     ELSE = 297,
     END = 298,
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
#define LP 259
#define RP 260
#define LB 261
#define RB 262
#define DOT 263
#define COMMA 264
#define COLON 265
#define MUL 266
#define DIV 267
#define UNEQUAL 268
#define NOT 269
#define PLUS 270
#define MINUS 271
#define GE 272
#define GT 273
#define LE 274
#define LT 275
#define EQUAL 276
#define ASSIGN 277
#define MOD 278
#define DOTDOT 279
#define SEMI 280
#define SYS_CON 281
#define SYS_FUNCT 282
#define SYS_PROC 283
#define SYS_TYPE 284
#define READ 285
#define INTEGER 286
#define REAL 287
#define CHAR 288
#define STRING 289
#define AND 290
#define ARRAY 291
#define BEGIN_T 292
#define CASE 293
#define CONST 294
#define DO 295
#define DOWNTO 296
#define ELSE 297
#define END 298
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




/* Copy the first part of user declarations.  */
#line 1 "parser.y"

#include "AST.hpp"
extern int yylex();
extern int yylineno;
Program * astRoot;


void yyerror(const char* s) { 
  printf("[ERROR]: At line: %d\n\t\t%s\n ", yylineno, s); 
}



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 14 "parser.y"
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
/* Line 193 of yacc.c.  */
#line 296 "yac.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 309 "yac.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   392

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  64
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  57
/* YYNRULES -- Number of rules.  */
#define YYNRULES  128
/* YYNRULES -- Number of states.  */
#define YYNSTATES  269

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   318

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,    11,    14,    17,    23,    25,    28,
      30,    36,    41,    43,    45,    47,    49,    51,    54,    56,
      59,    61,    66,    68,    70,    72,    74,    76,    80,    84,
      89,    95,    99,   106,   110,   113,   115,   120,   124,   126,
     129,   131,   134,   136,   141,   144,   147,   149,   151,   153,
     158,   164,   169,   173,   177,   179,   183,   185,   189,   193,
     196,   198,   200,   204,   208,   210,   214,   216,   218,   220,
     222,   224,   226,   228,   230,   232,   234,   238,   245,   251,
     253,   258,   260,   265,   270,   276,   279,   281,   286,   291,
     300,   302,   304,   310,   313,   315,   320,   325,   328,   332,
     334,   338,   342,   346,   350,   354,   358,   360,   364,   368,
     372,   374,   378,   382,   386,   390,   392,   394,   399,   401,
     406,   408,   412,   415,   418,   423,   427,   431,   433
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      65,     0,    -1,    66,    67,     8,    -1,    53,     3,    25,
      -1,    69,    97,    -1,    69,    97,    -1,    70,    71,    74,
      84,    87,    -1,   120,    -1,    39,    72,    -1,   120,    -1,
      72,     3,    21,    73,    25,    -1,     3,    21,    73,    25,
      -1,    31,    -1,    32,    -1,    33,    -1,    34,    -1,    26,
      -1,    59,    75,    -1,   120,    -1,    75,    76,    -1,    76,
      -1,     3,    21,    77,    25,    -1,    78,    -1,    79,    -1,
      80,    -1,    29,    -1,     3,    -1,     4,    83,     5,    -1,
      73,    24,    73,    -1,    16,    73,    24,    73,    -1,    16,
      73,    24,    16,    73,    -1,     3,    24,     3,    -1,    36,
       6,    78,     7,    49,    77,    -1,    54,    81,    43,    -1,
      81,    82,    -1,    82,    -1,    83,    10,    77,    25,    -1,
      83,     9,     3,    -1,     3,    -1,    61,    85,    -1,   120,
      -1,    85,    86,    -1,    86,    -1,    83,    10,    77,    25,
      -1,    87,    88,    -1,    87,    90,    -1,    88,    -1,    90,
      -1,   120,    -1,    89,    25,    68,    25,    -1,    45,     3,
      92,    10,    78,    -1,    91,    25,    68,    25,    -1,    52,
       3,    92,    -1,     4,    93,     5,    -1,   120,    -1,    93,
      25,    94,    -1,    94,    -1,    95,    10,    78,    -1,    96,
      10,    78,    -1,    61,    83,    -1,    83,    -1,    98,    -1,
      37,    99,    43,    -1,    99,   100,    25,    -1,   120,    -1,
      31,    10,   101,    -1,   101,    -1,   102,    -1,   103,    -1,
      98,    -1,   104,    -1,   106,    -1,   107,    -1,   108,    -1,
     110,    -1,   113,    -1,     3,    22,   115,    -1,     3,     6,
     115,     7,    22,   115,    -1,     3,     8,     3,    22,   115,
      -1,     3,    -1,     3,     4,   119,     5,    -1,    28,    -1,
      28,     4,   114,     5,    -1,    30,     4,   118,     5,    -1,
      47,   115,    57,   100,   105,    -1,    42,   100,    -1,   120,
      -1,    55,    99,    60,   115,    -1,    62,   115,    40,   100,
      -1,    44,     3,    22,   115,   109,   115,    40,   100,    -1,
      58,    -1,    41,    -1,    38,   115,    49,   111,    43,    -1,
     111,   112,    -1,   112,    -1,    73,    10,   100,    25,    -1,
       3,    10,   100,    25,    -1,    46,    31,    -1,   114,     9,
     115,    -1,   115,    -1,   115,    17,   116,    -1,   115,    18,
     116,    -1,   115,    19,   116,    -1,   115,    20,   116,    -1,
     115,    21,   116,    -1,   115,    13,   116,    -1,   116,    -1,
     116,    15,   117,    -1,   116,    16,   117,    -1,   116,    50,
     117,    -1,   117,    -1,   117,    11,   118,    -1,   117,    12,
     118,    -1,   117,    23,   118,    -1,   117,    35,   118,    -1,
     118,    -1,     3,    -1,     3,     4,   119,     5,    -1,    27,
      -1,    27,     4,   119,     5,    -1,    73,    -1,     4,   115,
       5,    -1,    14,   118,    -1,    16,   118,    -1,     3,     6,
     115,     7,    -1,     3,     8,     3,    -1,   119,     9,   115,
      -1,   115,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   141,   141,   144,   147,   150,   153,   156,   159,   160,
     163,   164,   167,   168,   169,   170,   171,   174,   175,   178,
     179,   182,   185,   186,   187,   190,   191,   192,   193,   194,
     195,   196,   199,   202,   205,   206,   209,   212,   213,   216,
     217,   220,   221,   224,   227,   228,   229,   230,   231,   234,
     237,   240,   243,   246,   247,   250,   251,   254,   255,   258,
     261,   264,   267,   270,   271,   274,   275,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   289,   290,   291,   294,
     295,   296,   297,   298,   301,   304,   305,   308,   311,   314,
     317,   318,   321,   324,   325,   328,   329,   332,   335,   336,
     339,   340,   341,   342,   343,   344,   345,   348,   349,   350,
     351,   354,   355,   356,   357,   358,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   373,   374,   376
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NAME", "LP", "RP", "LB", "RB", "DOT",
  "COMMA", "COLON", "MUL", "DIV", "UNEQUAL", "NOT", "PLUS", "MINUS", "GE",
  "GT", "LE", "LT", "EQUAL", "ASSIGN", "MOD", "DOTDOT", "SEMI", "SYS_CON",
  "SYS_FUNCT", "SYS_PROC", "SYS_TYPE", "READ", "INTEGER", "REAL", "CHAR",
  "STRING", "AND", "ARRAY", "BEGIN_T", "CASE", "CONST", "DO", "DOWNTO",
  "ELSE", "END", "FOR", "FUNCTION", "GOTO", "IF", "IN", "OF", "OR",
  "PACKED", "PROCEDURE", "PROGRAM", "RECORD", "REPEAT", "SET", "THEN",
  "TO", "TYPE", "UNTIL", "VAR", "WHILE", "WITH", "$accept", "program",
  "program_head", "routine", "sub_routine", "routine_head", "label_part",
  "const_part", "const_expr_list", "const_value", "type_part",
  "type_decl_list", "type_definition", "type_decl", "simple_type_decl",
  "array_type_decl", "record_type_decl", "field_decl_list", "field_decl",
  "name_list", "var_part", "var_decl_list", "var_decl", "routine_part",
  "function_decl", "function_head", "procedure_decl", "procedure_head",
  "parameters", "para_decl_list", "para_type_list", "var_para_list",
  "val_para_list", "routine_body", "compound_stmt", "stmt_list", "stmt",
  "non_label_stmt", "assign_stmt", "proc_stmt", "if_stmt", "else_clause",
  "repeat_stmt", "while_stmt", "for_stmt", "direction", "case_stmt",
  "case_expr_list", "case_expr", "goto_stmt", "expression_list",
  "expression", "expr", "term", "factor", "args_list", "epsilon", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    64,    65,    66,    67,    68,    69,    70,    71,    71,
      72,    72,    73,    73,    73,    73,    73,    74,    74,    75,
      75,    76,    77,    77,    77,    78,    78,    78,    78,    78,
      78,    78,    79,    80,    81,    81,    82,    83,    83,    84,
      84,    85,    85,    86,    87,    87,    87,    87,    87,    88,
      89,    90,    91,    92,    92,    93,    93,    94,    94,    95,
      96,    97,    98,    99,    99,   100,   100,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   102,   102,   102,   103,
     103,   103,   103,   103,   104,   105,   105,   106,   107,   108,
     109,   109,   110,   111,   111,   112,   112,   113,   114,   114,
     115,   115,   115,   115,   115,   115,   115,   116,   116,   116,
     116,   117,   117,   117,   117,   117,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   119,   119,   120
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     3,     2,     2,     5,     1,     2,     1,
       5,     4,     1,     1,     1,     1,     1,     2,     1,     2,
       1,     4,     1,     1,     1,     1,     1,     3,     3,     4,
       5,     3,     6,     3,     2,     1,     4,     3,     1,     2,
       1,     2,     1,     4,     2,     2,     1,     1,     1,     4,
       5,     4,     3,     3,     1,     3,     1,     3,     3,     2,
       1,     1,     3,     3,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     6,     5,     1,
       4,     1,     4,     4,     5,     2,     1,     4,     4,     8,
       1,     1,     5,     2,     1,     4,     4,     2,     3,     1,
       3,     3,     3,     3,     3,     3,     1,     3,     3,     3,
       1,     3,     3,     3,     3,     1,     1,     4,     1,     4,
       1,     3,     2,     2,     4,     3,     3,     1,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,   128,     0,     1,     0,     0,   128,     7,
       3,     2,   128,     4,    61,     0,   128,     9,     0,    64,
       0,     8,     0,   128,    18,    79,    81,     0,     0,     0,
      62,     0,     0,     0,   128,     0,    69,     0,    66,    67,
      68,    70,    71,    72,    73,    74,    75,     0,     0,     0,
      17,    20,     0,   128,    40,     0,     0,     0,     0,     0,
       0,     0,   116,     0,     0,     0,    16,   118,    12,    13,
      14,    15,   120,     0,   106,   110,   115,     0,    97,     0,
       0,     0,    63,     0,     0,     0,    19,    38,     0,    39,
      42,     0,     0,     6,    46,     0,    47,     0,    48,   127,
       0,     0,     0,    76,     0,    99,     0,    65,     0,     0,
       0,     0,   122,   123,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    11,     0,    26,     0,     0,    25,     0,
       0,     0,     0,    22,    23,    24,     0,     0,    41,   128,
     128,    44,    45,   128,   128,    80,     0,     0,     0,    82,
       0,    83,     0,     0,   125,   121,     0,   105,   100,   101,
     102,   103,   104,     0,     0,     0,    94,   107,   108,   109,
     111,   112,   113,   114,     0,   128,    87,    88,    10,     0,
       0,     0,     0,     0,    35,     0,     0,    21,    37,     0,
       0,     0,    54,    52,     0,     0,     0,   126,     0,    78,
      98,   117,   124,   119,     0,     0,    92,    93,    91,    90,
       0,     0,    84,    86,    31,    27,     0,     0,    33,    34,
       0,    28,    43,     0,    60,     0,    56,     0,     0,     0,
      49,     5,    51,    77,     0,     0,     0,    85,     0,    29,
       0,     0,    59,    53,     0,     0,     0,    50,    96,    95,
       0,    30,     0,    36,    55,    57,    58,    89,    32
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     6,   204,   205,     8,    16,    21,    72,
      23,    50,    51,   142,   143,   144,   145,   193,   194,    88,
      53,    89,    90,    93,    94,    95,    96,    97,   201,   235,
     236,   237,   238,    13,    36,    18,    37,    38,    39,    40,
      41,   222,    42,    43,    44,   220,    45,   175,   176,    46,
     104,    99,    74,    75,    76,   100,     9
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -189
static const yytype_int16 yypact[] =
{
     -42,    17,    59,  -189,    35,  -189,    77,    52,    53,  -189,
    -189,  -189,  -189,  -189,  -189,    90,    44,  -189,    18,  -189,
      88,   107,   112,    55,  -189,    19,   122,   123,   110,   257,
    -189,   136,   111,   257,  -189,   257,  -189,   118,  -189,  -189,
    -189,  -189,  -189,  -189,  -189,  -189,  -189,    65,   120,   127,
     112,  -189,   149,   -19,  -189,   257,   257,   152,   257,   257,
     257,   186,    71,   257,   257,   257,  -189,   153,  -189,  -189,
    -189,  -189,  -189,   245,     0,    46,  -189,   134,  -189,   104,
     116,   297,  -189,   139,    65,   223,  -189,  -189,    33,   149,
    -189,   156,   162,   -19,  -189,   141,  -189,   142,  -189,   365,
      25,   347,   146,   365,    61,   365,   165,  -189,   257,   257,
     169,   338,  -189,  -189,   257,   257,   257,   257,   257,   257,
     257,   275,   257,   257,   257,   257,   257,   257,   257,   257,
     166,   257,   166,  -189,   148,   150,   149,    65,  -189,   171,
     149,   158,   155,  -189,  -189,  -189,   181,   223,  -189,   183,
     183,  -189,  -189,  -189,  -189,  -189,   257,   163,   257,  -189,
     257,  -189,    67,   356,  -189,  -189,    78,     0,     0,     0,
       0,     0,     0,   178,   180,   203,  -189,    46,    46,    46,
    -189,  -189,  -189,  -189,   117,   160,   365,  -189,  -189,   188,
      79,   174,   266,     4,  -189,    43,    65,  -189,  -189,   170,
       2,   190,  -189,  -189,   182,    52,   192,   365,   257,   365,
     365,  -189,  -189,  -189,   166,   166,  -189,  -189,  -189,  -189,
     257,   166,  -189,  -189,  -189,  -189,   316,   198,  -189,  -189,
     223,  -189,  -189,   149,   202,    14,  -189,   208,   209,   266,
    -189,  -189,  -189,   365,   195,   197,   306,  -189,    65,  -189,
     176,   206,   202,  -189,     2,   266,   266,  -189,  -189,  -189,
     166,  -189,   223,  -189,  -189,  -189,  -189,  -189,  -189
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -189,  -189,  -189,  -189,    84,   237,  -189,  -189,  -189,   -47,
    -189,  -189,   193,  -144,  -188,  -189,  -189,  -189,    49,  -122,
    -189,  -189,   161,  -189,   151,  -189,   154,  -189,    95,  -189,
      -3,  -189,  -189,    48,    -6,   233,  -120,   207,  -189,  -189,
    -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,    97,  -189,
    -189,   -27,   272,   -10,   -20,   -86,     1
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      83,    14,    73,   199,   227,    87,    79,    87,    81,    17,
     185,     1,   187,    19,   190,   122,   123,    24,   195,   253,
       4,    25,   162,    55,    54,    56,    91,    57,   166,   101,
     155,   103,   105,    92,   156,    19,   111,   134,   141,   254,
     106,    58,   146,   147,   112,   113,    26,   228,    27,    28,
     124,   257,   146,   230,    98,    12,    29,   125,   126,     5,
      10,    30,    31,   233,    32,    33,   159,   265,   266,   127,
     160,   195,   211,    34,   174,   108,   156,   109,   234,   110,
      35,   128,   163,   213,   225,    11,   251,   156,   146,    12,
     191,    66,    15,    20,   244,   245,    68,    69,    70,    71,
     141,   247,   184,    22,   186,   180,   181,   182,   183,    47,
      48,   252,   177,   178,   179,    49,    52,   115,   268,    25,
      61,   116,   117,   118,   119,   120,    59,    60,   174,   207,
     115,   209,   234,   210,   116,   117,   118,   119,   120,    77,
     267,    84,    78,    82,    26,   141,    27,    28,    85,   231,
     202,   202,    87,    12,    29,   102,   129,   114,   218,   149,
      31,   130,    32,    33,   133,   150,   153,   154,   158,    25,
     161,    34,   164,   188,   189,   219,   131,   192,    35,   249,
     197,   243,   196,   141,   198,   208,   223,   200,   214,    25,
     215,   224,   141,   246,    26,   232,    27,    28,   226,    14,
     239,   261,   221,    12,    29,   250,   173,   240,   141,   141,
      31,   146,    32,    33,    26,   141,    27,   242,   255,   256,
     258,    34,   259,    12,    29,   262,   135,   136,    35,    66,
      31,   263,    32,    33,    68,    69,    70,    71,   206,   137,
       7,    34,   229,    86,   151,   203,   216,   152,    35,    66,
     148,   264,   138,   241,    68,    69,    70,    71,   115,   139,
      62,    63,   116,   117,   118,   119,   120,    80,   107,   135,
     136,    64,   217,    65,     0,     0,     0,   140,   173,     0,
       0,     0,   137,    66,    67,     0,     0,     0,    68,    69,
      70,    71,    66,     0,   121,   138,     0,    68,    69,    70,
      71,    66,     0,     0,     0,     0,    68,    69,    70,    71,
     115,     0,     0,     0,   116,   117,   118,   119,   120,   115,
       0,     0,     0,   116,   117,   118,   119,   120,     0,     0,
       0,     0,   248,     0,     0,     0,     0,   132,     0,     0,
       0,     0,    66,   165,     0,     0,   260,    68,    69,    70,
      71,   115,     0,     0,   157,   116,   117,   118,   119,   120,
     115,     0,     0,   212,   116,   117,   118,   119,   120,   115,
       0,     0,     0,   116,   117,   118,   119,   120,   115,     0,
       0,     0,   116,   117,   118,   119,   120,   167,   168,   169,
     170,   171,   172
};

static const yytype_int16 yycheck[] =
{
      47,     7,    29,   147,   192,     3,    33,     3,    35,     8,
     130,    53,   132,    12,   136,    15,    16,    16,   140,     5,
       3,     3,   108,     4,    23,     6,    45,     8,   114,    56,
       5,    58,    59,    52,     9,    34,    63,    84,    85,    25,
      60,    22,     9,    10,    64,    65,    28,    43,    30,    31,
      50,   239,     9,    10,    53,    37,    38,    11,    12,     0,
      25,    43,    44,    61,    46,    47,     5,   255,   256,    23,
       9,   193,     5,    55,   121,     4,     9,     6,   200,     8,
      62,    35,   109,     5,     5,     8,   230,     9,     9,    37,
     137,    26,    39,     3,   214,   215,    31,    32,    33,    34,
     147,   221,   129,    59,   131,   125,   126,   127,   128,    21,
       3,   233,   122,   123,   124,     3,    61,    13,   262,     3,
      10,    17,    18,    19,    20,    21,     4,     4,   175,   156,
      13,   158,   254,   160,    17,    18,    19,    20,    21,     3,
     260,    21,    31,    25,    28,   192,    30,    31,    21,   196,
     149,   150,     3,    37,    38,     3,    22,     4,    41,     3,
      44,    57,    46,    47,    25,     3,    25,    25,    22,     3,
       5,    55,     3,    25,    24,    58,    60,     6,    62,   226,
      25,   208,    24,   230,     3,    22,   185,     4,    10,     3,
      10,     3,   239,   220,    28,    25,    30,    31,    24,   205,
      10,   248,    42,    37,    38,     7,     3,    25,   255,   256,
      44,     9,    46,    47,    28,   262,    30,    25,    10,    10,
      25,    55,    25,    37,    38,    49,     3,     4,    62,    26,
      44,    25,    46,    47,    31,    32,    33,    34,   154,    16,
       3,    55,   193,    50,    93,   150,    43,    93,    62,    26,
      89,   254,    29,   205,    31,    32,    33,    34,    13,    36,
       3,     4,    17,    18,    19,    20,    21,    34,    61,     3,
       4,    14,   175,    16,    -1,    -1,    -1,    54,     3,    -1,
      -1,    -1,    16,    26,    27,    -1,    -1,    -1,    31,    32,
      33,    34,    26,    -1,    49,    29,    -1,    31,    32,    33,
      34,    26,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      13,    -1,    -1,    -1,    17,    18,    19,    20,    21,    13,
      -1,    -1,    -1,    17,    18,    19,    20,    21,    -1,    -1,
      -1,    -1,    16,    -1,    -1,    -1,    -1,    40,    -1,    -1,
      -1,    -1,    26,     5,    -1,    -1,    40,    31,    32,    33,
      34,    13,    -1,    -1,     7,    17,    18,    19,    20,    21,
      13,    -1,    -1,     7,    17,    18,    19,    20,    21,    13,
      -1,    -1,    -1,    17,    18,    19,    20,    21,    13,    -1,
      -1,    -1,    17,    18,    19,    20,    21,   115,   116,   117,
     118,   119,   120
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    53,    65,    66,     3,     0,    67,    69,    70,   120,
      25,     8,    37,    97,    98,    39,    71,   120,    99,   120,
       3,    72,    59,    74,   120,     3,    28,    30,    31,    38,
      43,    44,    46,    47,    55,    62,    98,   100,   101,   102,
     103,   104,   106,   107,   108,   110,   113,    21,     3,     3,
      75,    76,    61,    84,   120,     4,     6,     8,    22,     4,
       4,    10,     3,     4,    14,    16,    26,    27,    31,    32,
      33,    34,    73,   115,   116,   117,   118,     3,    31,   115,
      99,   115,    25,    73,    21,    21,    76,     3,    83,    85,
      86,    45,    52,    87,    88,    89,    90,    91,   120,   115,
     119,   115,     3,   115,   114,   115,   118,   101,     4,     6,
       8,   115,   118,   118,     4,    13,    17,    18,    19,    20,
      21,    49,    15,    16,    50,    11,    12,    23,    35,    22,
      57,    60,    40,    25,    73,     3,     4,    16,    29,    36,
      54,    73,    77,    78,    79,    80,     9,    10,    86,     3,
       3,    88,    90,    25,    25,     5,     9,     7,    22,     5,
       9,     5,   119,   115,     3,     5,   119,   116,   116,   116,
     116,   116,   116,     3,    73,   111,   112,   117,   117,   117,
     118,   118,   118,   118,   115,   100,   115,   100,    25,    24,
      83,    73,     6,    81,    82,    83,    24,    25,     3,    77,
       4,    92,   120,    92,    68,    69,    68,   115,    22,   115,
     115,     5,     7,     5,    10,    10,    43,   112,    41,    58,
     109,    42,   105,   120,     3,     5,    24,    78,    43,    82,
      10,    73,    25,    61,    83,    93,    94,    95,    96,    10,
      25,    97,    25,   115,   100,   100,   115,   100,    16,    73,
       7,    77,    83,     5,    25,    10,    10,    78,    25,    25,
      40,    73,    49,    25,    94,    78,    78,   100,    77
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 141 "parser.y"
    {astRoot = new Program((yyvsp[(1) - (3)].programHead), (yyvsp[(2) - (3)].routine));}
    break;

  case 3:
#line 144 "parser.y"
    {(yyval.programHead) = new ProgramHead(*(yyvsp[(2) - (3)].content));}
    break;

  case 4:
#line 147 "parser.y"
    {(yyval.routine) = new Routine((yyvsp[(1) - (2)].routineHead), (yyvsp[(2) - (2)].routineBody));}
    break;

  case 5:
#line 150 "parser.y"
    {(yyval.subRoutine) = new SubRoutine((yyvsp[(1) - (2)].routineHead), (yyvsp[(2) - (2)].routineBody));}
    break;

  case 6:
#line 153 "parser.y"
    {(yyval.routineHead) = new RoutineHead((yyvsp[(1) - (5)].labelPart), (yyvsp[(2) - (5)].constPart), (yyvsp[(3) - (5)].typePart), (yyvsp[(4) - (5)].varPart), (yyvsp[(5) - (5)].routinePart));}
    break;

  case 7:
#line 156 "parser.y"
    {(yyval.labelPart) = new LabelPart();}
    break;

  case 8:
#line 159 "parser.y"
    {(yyval.constPart) = new ConstPart((yyvsp[(2) - (2)].constExprList));}
    break;

  case 9:
#line 160 "parser.y"
    {(yyval.constPart) = new ConstPart();}
    break;

  case 10:
#line 163 "parser.y"
    {(yyval.constExprList) = new ConstExprList(*(yyvsp[(2) - (5)].content), (yyvsp[(1) - (5)].constExprList), (yyvsp[(4) - (5)].constValue));}
    break;

  case 11:
#line 164 "parser.y"
    {(yyval.constExprList) = new ConstExprList(*(yyvsp[(1) - (4)].content), (yyvsp[(3) - (4)].constValue));}
    break;

  case 12:
#line 167 "parser.y"
    {(yyval.constValue) = new ConstValue((yyvsp[(1) - (1)].type), *(yyvsp[(1) - (1)].content));}
    break;

  case 13:
#line 168 "parser.y"
    {(yyval.constValue) = new ConstValue((yyvsp[(1) - (1)].type), *(yyvsp[(1) - (1)].content));}
    break;

  case 14:
#line 169 "parser.y"
    {(yyval.constValue) = new ConstValue((yyvsp[(1) - (1)].type), *(yyvsp[(1) - (1)].content));}
    break;

  case 15:
#line 170 "parser.y"
    {(yyval.constValue) = new ConstValue((yyvsp[(1) - (1)].type), *(yyvsp[(1) - (1)].content));}
    break;

  case 16:
#line 171 "parser.y"
    {(yyval.constValue) = new ConstValue((yyvsp[(1) - (1)].type), *(yyvsp[(1) - (1)].content));}
    break;

  case 17:
#line 174 "parser.y"
    {(yyval.typePart) = new TypePart((yyvsp[(2) - (2)].typeDeclList));}
    break;

  case 18:
#line 175 "parser.y"
    {(yyval.typePart) = new TypePart();}
    break;

  case 19:
#line 178 "parser.y"
    {(yyval.typeDeclList) = new TypeDeclList((yyvsp[(1) - (2)].typeDeclList), (yyvsp[(2) - (2)].typeDefinition));}
    break;

  case 20:
#line 179 "parser.y"
    {(yyval.typeDeclList) = new TypeDeclList((yyvsp[(1) - (1)].typeDefinition));}
    break;

  case 21:
#line 182 "parser.y"
    {(yyval.typeDefinition) = new TypeDefinition(*(yyvsp[(1) - (4)].content), (yyvsp[(3) - (4)].typeDecl));}
    break;

  case 22:
#line 185 "parser.y"
    {(yyval.typeDecl) = new TypeDecl((yyvsp[(1) - (1)].simpleTypeDecl));}
    break;

  case 23:
#line 186 "parser.y"
    {(yyval.typeDecl) = new TypeDecl((yyvsp[(1) - (1)].arrayTypeDecl));}
    break;

  case 24:
#line 187 "parser.y"
    {(yyval.typeDecl) = new TypeDecl((yyvsp[(1) - (1)].recordTypeDecl));}
    break;

  case 25:
#line 190 "parser.y"
    {(yyval.simpleTypeDecl) = new SimpleTypeDecl((yyvsp[(1) - (1)].type), *(yyvsp[(1) - (1)].content));}
    break;

  case 26:
#line 191 "parser.y"
    {(yyval.simpleTypeDecl) = new SimpleTypeDecl((yyvsp[(1) - (1)].type), *(yyvsp[(1) - (1)].content));}
    break;

  case 27:
#line 192 "parser.y"
    {(yyval.simpleTypeDecl) = new SimpleTypeDecl((yyvsp[(2) - (3)].nameList));}
    break;

  case 28:
#line 193 "parser.y"
    {(yyval.simpleTypeDecl) = new SimpleTypeDecl((yyvsp[(1) - (3)].constValue), (yyvsp[(3) - (3)].constValue));}
    break;

  case 29:
#line 194 "parser.y"
    {(yyval.simpleTypeDecl) = new SimpleTypeDecl((yyvsp[(2) - (4)].constValue)->neg(), (yyvsp[(4) - (4)].constValue));}
    break;

  case 30:
#line 195 "parser.y"
    {(yyval.simpleTypeDecl) = new SimpleTypeDecl((yyvsp[(2) - (5)].constValue)->neg(), (yyvsp[(5) - (5)].constValue)->neg());}
    break;

  case 31:
#line 196 "parser.y"
    {(yyval.simpleTypeDecl) = new SimpleTypeDecl(*(yyvsp[(1) - (3)].content), *(yyvsp[(3) - (3)].content));}
    break;

  case 32:
#line 199 "parser.y"
    {(yyval.arrayTypeDecl) = new ArrayTypeDecl((yyvsp[(3) - (6)].simpleTypeDecl), (yyvsp[(6) - (6)].typeDecl));}
    break;

  case 33:
#line 202 "parser.y"
    {(yyval.recordTypeDecl) = new RecordTypeDecl((yyvsp[(2) - (3)].fieldDeclList));}
    break;

  case 34:
#line 205 "parser.y"
    {(yyval.fieldDeclList) = new FieldDeclList((yyvsp[(1) - (2)].fieldDeclList), (yyvsp[(2) - (2)].fieldDecl));}
    break;

  case 35:
#line 206 "parser.y"
    {(yyval.fieldDeclList) = new FieldDeclList((yyvsp[(1) - (1)].fieldDecl));}
    break;

  case 36:
#line 209 "parser.y"
    {(yyval.fieldDecl) = new FieldDecl((yyvsp[(1) - (4)].nameList), (yyvsp[(3) - (4)].typeDecl));}
    break;

  case 37:
#line 212 "parser.y"
    {(yyval.nameList) = new NameList(*(yyvsp[(3) - (3)].content), (yyvsp[(1) - (3)].nameList));}
    break;

  case 38:
#line 213 "parser.y"
    {(yyval.nameList) = new NameList(*(yyvsp[(1) - (1)].content));}
    break;

  case 39:
#line 216 "parser.y"
    {(yyval.varPart) = new VarPart((yyvsp[(2) - (2)].varDeclList));}
    break;

  case 40:
#line 217 "parser.y"
    {(yyval.varPart) = new VarPart();}
    break;

  case 41:
#line 220 "parser.y"
    {(yyval.varDeclList) = new VarDeclList((yyvsp[(1) - (2)].varDeclList), (yyvsp[(2) - (2)].varDecl));}
    break;

  case 42:
#line 221 "parser.y"
    {(yyval.varDeclList) = new VarDeclList((yyvsp[(1) - (1)].varDecl));}
    break;

  case 43:
#line 224 "parser.y"
    {(yyval.varDecl) = new VarDecl((yyvsp[(1) - (4)].nameList), (yyvsp[(3) - (4)].typeDecl));}
    break;

  case 44:
#line 227 "parser.y"
    {(yyval.routinePart) = new RoutinePart((yyvsp[(1) - (2)].routinePart), (yyvsp[(2) - (2)].functionDecl));}
    break;

  case 45:
#line 228 "parser.y"
    {(yyval.routinePart) = new RoutinePart((yyvsp[(1) - (2)].routinePart), (yyvsp[(2) - (2)].procedureDecl));}
    break;

  case 46:
#line 229 "parser.y"
    {(yyval.routinePart) = new RoutinePart((yyvsp[(1) - (1)].functionDecl));}
    break;

  case 47:
#line 230 "parser.y"
    {(yyval.routinePart) = new RoutinePart((yyvsp[(1) - (1)].procedureDecl));}
    break;

  case 48:
#line 231 "parser.y"
    {(yyval.routinePart) = new RoutinePart();}
    break;

  case 49:
#line 234 "parser.y"
    {(yyval.functionDecl) = new FunctionDecl((yyvsp[(1) - (4)].functionHead), (yyvsp[(3) - (4)].subRoutine));}
    break;

  case 50:
#line 237 "parser.y"
    {(yyval.functionHead) = new FunctionHead(*(yyvsp[(2) - (5)].content), (yyvsp[(3) - (5)].parameters), (yyvsp[(5) - (5)].simpleTypeDecl));}
    break;

  case 51:
#line 240 "parser.y"
    {(yyval.procedureDecl) = new ProcedureDecl((yyvsp[(1) - (4)].procedureHead), (yyvsp[(3) - (4)].subRoutine));}
    break;

  case 52:
#line 243 "parser.y"
    {(yyval.procedureHead) = new ProcedureHead(*(yyvsp[(2) - (3)].content), (yyvsp[(3) - (3)].parameters));}
    break;

  case 53:
#line 246 "parser.y"
    {(yyval.parameters) = new Parameters((yyvsp[(2) - (3)].paraDeclList));}
    break;

  case 54:
#line 247 "parser.y"
    {(yyval.parameters) = new Parameters( );}
    break;

  case 55:
#line 250 "parser.y"
    {(yyval.paraDeclList) = new ParaDeclList((yyvsp[(1) - (3)].paraDeclList), (yyvsp[(3) - (3)].paraTypeList));}
    break;

  case 56:
#line 251 "parser.y"
    {(yyval.paraDeclList) = new ParaDeclList((yyvsp[(1) - (1)].paraTypeList));}
    break;

  case 57:
#line 254 "parser.y"
    {(yyval.paraTypeList) = new ParaTypeList((yyvsp[(1) - (3)].varParaList), (yyvsp[(3) - (3)].simpleTypeDecl));}
    break;

  case 58:
#line 255 "parser.y"
    {(yyval.paraTypeList) = new ParaTypeList((yyvsp[(1) - (3)].valParaList), (yyvsp[(3) - (3)].simpleTypeDecl));}
    break;

  case 59:
#line 258 "parser.y"
    {(yyval.varParaList) = new VarParaList((yyvsp[(2) - (2)].nameList));}
    break;

  case 60:
#line 261 "parser.y"
    {(yyval.valParaList) = new ValParaList((yyvsp[(1) - (1)].nameList));}
    break;

  case 61:
#line 264 "parser.y"
    {(yyval.routineBody) = new RoutineBody((yyvsp[(1) - (1)].compoundStmt));}
    break;

  case 62:
#line 267 "parser.y"
    {(yyval.compoundStmt) = new CompoundStmt((yyvsp[(2) - (3)].stmtList));}
    break;

  case 63:
#line 270 "parser.y"
    {(yyval.stmtList) = new StmtList((yyvsp[(1) - (3)].stmtList), (yyvsp[(2) - (3)].stmt));}
    break;

  case 64:
#line 271 "parser.y"
    {(yyval.stmtList) = new StmtList();}
    break;

  case 65:
#line 274 "parser.y"
    {(yyval.stmt) = new Stmt((yyvsp[(3) - (3)].nonLabelStmt));}
    break;

  case 66:
#line 275 "parser.y"
    {(yyval.stmt) = new Stmt((yyvsp[(1) - (1)].nonLabelStmt));}
    break;

  case 67:
#line 278 "parser.y"
    {(yyval.nonLabelStmt) = new NonLabelStmt((yyvsp[(1) - (1)].assignStmt));}
    break;

  case 68:
#line 279 "parser.y"
    {(yyval.nonLabelStmt) = new NonLabelStmt((yyvsp[(1) - (1)].procStmt));}
    break;

  case 69:
#line 280 "parser.y"
    {(yyval.nonLabelStmt) = new NonLabelStmt((yyvsp[(1) - (1)].compoundStmt));}
    break;

  case 70:
#line 281 "parser.y"
    {(yyval.nonLabelStmt) = new NonLabelStmt((yyvsp[(1) - (1)].ifStmt));}
    break;

  case 71:
#line 282 "parser.y"
    {(yyval.nonLabelStmt) = new NonLabelStmt((yyvsp[(1) - (1)].repeatStmt));}
    break;

  case 72:
#line 283 "parser.y"
    {(yyval.nonLabelStmt) = new NonLabelStmt((yyvsp[(1) - (1)].whileStmt));}
    break;

  case 73:
#line 284 "parser.y"
    {(yyval.nonLabelStmt) = new NonLabelStmt((yyvsp[(1) - (1)].forStmt));}
    break;

  case 74:
#line 285 "parser.y"
    {(yyval.nonLabelStmt) = new NonLabelStmt((yyvsp[(1) - (1)].caseStmt));}
    break;

  case 75:
#line 286 "parser.y"
    {(yyval.nonLabelStmt) = new NonLabelStmt((yyvsp[(1) - (1)].gotoStmt));}
    break;

  case 76:
#line 289 "parser.y"
    {(yyval.assignStmt) = new AssignStmt(*(yyvsp[(1) - (3)].content), (yyvsp[(3) - (3)].expression));}
    break;

  case 77:
#line 290 "parser.y"
    {(yyval.assignStmt) = new AssignStmt(*(yyvsp[(1) - (6)].content), (yyvsp[(3) - (6)].expression), (yyvsp[(6) - (6)].expression));}
    break;

  case 78:
#line 291 "parser.y"
    {(yyval.assignStmt) = new AssignStmt(*(yyvsp[(1) - (5)].content), *(yyvsp[(3) - (5)].content), (yyvsp[(5) - (5)].expression));}
    break;

  case 79:
#line 294 "parser.y"
    {(yyval.procStmt) = new ProcStmt((yyvsp[(1) - (1)].type), *(yyvsp[(1) - (1)].content));}
    break;

  case 80:
#line 295 "parser.y"
    {(yyval.procStmt) = new ProcStmt(*(yyvsp[(1) - (4)].content), (yyvsp[(3) - (4)].argsList));}
    break;

  case 81:
#line 296 "parser.y"
    {(yyval.procStmt) = new ProcStmt((yyvsp[(1) - (1)].type), *(yyvsp[(1) - (1)].content));}
    break;

  case 82:
#line 297 "parser.y"
    {(yyval.procStmt) = new ProcStmt(*(yyvsp[(1) - (4)].content), (yyvsp[(3) - (4)].expressionList));}
    break;

  case 83:
#line 298 "parser.y"
    {(yyval.procStmt) = new ProcStmt((yyvsp[(3) - (4)].factor));}
    break;

  case 84:
#line 301 "parser.y"
    {(yyval.ifStmt) = new IfStmt((yyvsp[(2) - (5)].expression), (yyvsp[(4) - (5)].stmt), (yyvsp[(5) - (5)].elseClause));}
    break;

  case 85:
#line 304 "parser.y"
    {(yyval.elseClause) = new ElseClause((yyvsp[(2) - (2)].stmt));}
    break;

  case 86:
#line 305 "parser.y"
    {(yyval.elseClause) = new ElseClause();}
    break;

  case 87:
#line 308 "parser.y"
    {(yyval.repeatStmt) = new RepeatStmt((yyvsp[(2) - (4)].stmtList), (yyvsp[(4) - (4)].expression));}
    break;

  case 88:
#line 311 "parser.y"
    {(yyval.whileStmt) = new WhileStmt((yyvsp[(2) - (4)].expression), (yyvsp[(4) - (4)].stmt));}
    break;

  case 89:
#line 314 "parser.y"
    {(yyval.forStmt) = new ForStmt(*(yyvsp[(2) - (8)].content), (yyvsp[(4) - (8)].expression), (yyvsp[(5) - (8)].direction), (yyvsp[(6) - (8)].expression), (yyvsp[(8) - (8)].stmt));}
    break;

  case 90:
#line 317 "parser.y"
    {(yyval.direction) = new Direction(*(yyvsp[(1) - (1)].content));}
    break;

  case 91:
#line 318 "parser.y"
    {(yyval.direction) = new Direction(*(yyvsp[(1) - (1)].content));}
    break;

  case 92:
#line 321 "parser.y"
    {(yyval.caseStmt) = new CaseStmt((yyvsp[(2) - (5)].expression), (yyvsp[(4) - (5)].caseExprList));}
    break;

  case 93:
#line 324 "parser.y"
    {(yyval.caseExprList) = new CaseExprList((yyvsp[(1) - (2)].caseExprList), (yyvsp[(2) - (2)].caseExpr));}
    break;

  case 94:
#line 325 "parser.y"
    {(yyval.caseExprList) = new CaseExprList((yyvsp[(1) - (1)].caseExpr));}
    break;

  case 95:
#line 328 "parser.y"
    {(yyval.caseExpr) = new CaseExpr((yyvsp[(1) - (4)].constValue), (yyvsp[(3) - (4)].stmt));}
    break;

  case 96:
#line 329 "parser.y"
    {(yyval.caseExpr) = new CaseExpr(*(yyvsp[(1) - (4)].content), (yyvsp[(3) - (4)].stmt));}
    break;

  case 97:
#line 332 "parser.y"
    {(yyval.gotoStmt) = new GotoStmt(*(yyvsp[(2) - (2)].content));}
    break;

  case 98:
#line 335 "parser.y"
    {(yyval.expressionList) = new ExpressionList((yyvsp[(1) - (3)].expressionList), (yyvsp[(3) - (3)].expression));}
    break;

  case 99:
#line 336 "parser.y"
    {(yyval.expressionList) = new ExpressionList((yyvsp[(1) - (1)].expression));}
    break;

  case 100:
#line 339 "parser.y"
    {(yyval.expression) = new Expression((yyvsp[(1) - (3)].expression), *(yyvsp[(2) - (3)].content), (yyvsp[(3) - (3)].expr));}
    break;

  case 101:
#line 340 "parser.y"
    {(yyval.expression) = new Expression((yyvsp[(1) - (3)].expression), *(yyvsp[(2) - (3)].content), (yyvsp[(3) - (3)].expr));}
    break;

  case 102:
#line 341 "parser.y"
    {(yyval.expression) = new Expression((yyvsp[(1) - (3)].expression), *(yyvsp[(2) - (3)].content), (yyvsp[(3) - (3)].expr));}
    break;

  case 103:
#line 342 "parser.y"
    {(yyval.expression) = new Expression((yyvsp[(1) - (3)].expression), *(yyvsp[(2) - (3)].content), (yyvsp[(3) - (3)].expr));}
    break;

  case 104:
#line 343 "parser.y"
    {(yyval.expression) = new Expression((yyvsp[(1) - (3)].expression), *(yyvsp[(2) - (3)].content), (yyvsp[(3) - (3)].expr));}
    break;

  case 105:
#line 344 "parser.y"
    {(yyval.expression) = new Expression((yyvsp[(1) - (3)].expression), *(yyvsp[(2) - (3)].content), (yyvsp[(3) - (3)].expr));}
    break;

  case 106:
#line 345 "parser.y"
    {(yyval.expression) = new Expression((yyvsp[(1) - (1)].expr));}
    break;

  case 107:
#line 348 "parser.y"
    {(yyval.expr) = new Expr((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].content), (yyvsp[(3) - (3)].term));}
    break;

  case 108:
#line 349 "parser.y"
    {(yyval.expr) = new Expr((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].content), (yyvsp[(3) - (3)].term));}
    break;

  case 109:
#line 350 "parser.y"
    {(yyval.expr) = new Expr((yyvsp[(1) - (3)].expr), *(yyvsp[(2) - (3)].content), (yyvsp[(3) - (3)].term));}
    break;

  case 110:
#line 351 "parser.y"
    {(yyval.expr) = new Expr((yyvsp[(1) - (1)].term));}
    break;

  case 111:
#line 354 "parser.y"
    {(yyval.term) = new Term((yyvsp[(1) - (3)].term), *(yyvsp[(2) - (3)].content), (yyvsp[(3) - (3)].factor));}
    break;

  case 112:
#line 355 "parser.y"
    {(yyval.term) = new Term((yyvsp[(1) - (3)].term), *(yyvsp[(2) - (3)].content), (yyvsp[(3) - (3)].factor));}
    break;

  case 113:
#line 356 "parser.y"
    {(yyval.term) = new Term((yyvsp[(1) - (3)].term), *(yyvsp[(2) - (3)].content), (yyvsp[(3) - (3)].factor));}
    break;

  case 114:
#line 357 "parser.y"
    {(yyval.term) = new Term((yyvsp[(1) - (3)].term), *(yyvsp[(2) - (3)].content), (yyvsp[(3) - (3)].factor));}
    break;

  case 115:
#line 358 "parser.y"
    {(yyval.term) = new Term((yyvsp[(1) - (1)].factor));}
    break;

  case 116:
#line 361 "parser.y"
    {(yyval.factor) = new Factor((yyvsp[(1) - (1)].type), *(yyvsp[(1) - (1)].content));}
    break;

  case 117:
#line 362 "parser.y"
    {(yyval.factor) = new Factor((yyvsp[(1) - (4)].type), *(yyvsp[(1) - (4)].content), (yyvsp[(3) - (4)].argsList));}
    break;

  case 118:
#line 363 "parser.y"
    {(yyval.factor) = new Factor((yyvsp[(1) - (1)].type), *(yyvsp[(1) - (1)].content));}
    break;

  case 119:
#line 364 "parser.y"
    {(yyval.factor) = new Factor((yyvsp[(1) - (4)].type), *(yyvsp[(1) - (4)].content), (yyvsp[(3) - (4)].argsList));}
    break;

  case 120:
#line 365 "parser.y"
    {(yyval.factor) = new Factor((yyvsp[(1) - (1)].constValue));}
    break;

  case 121:
#line 366 "parser.y"
    {(yyval.factor) = new Factor((yyvsp[(2) - (3)].expression));}
    break;

  case 122:
#line 367 "parser.y"
    {(yyval.factor) = new Factor((yyvsp[(1) - (2)].type), (yyvsp[(2) - (2)].factor));}
    break;

  case 123:
#line 368 "parser.y"
    {(yyval.factor) = new Factor((yyvsp[(1) - (2)].type), (yyvsp[(2) - (2)].factor));}
    break;

  case 124:
#line 369 "parser.y"
    {(yyval.factor) = new Factor(*(yyvsp[(1) - (4)].content), (yyvsp[(3) - (4)].expression));}
    break;

  case 125:
#line 370 "parser.y"
    {(yyval.factor) = new Factor(*(yyvsp[(1) - (3)].content), *(yyvsp[(3) - (3)].content));}
    break;

  case 126:
#line 373 "parser.y"
    {(yyval.argsList) = new ArgsList((yyvsp[(1) - (3)].argsList), (yyvsp[(3) - (3)].expression));}
    break;

  case 127:
#line 374 "parser.y"
    {(yyval.argsList) = new ArgsList((yyvsp[(1) - (1)].expression));}
    break;

  case 128:
#line 376 "parser.y"
    { }
    break;


/* Line 1267 of yacc.c.  */
#line 2410 "yac.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 378 "parser.y"





