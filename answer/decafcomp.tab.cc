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
     T_AND = 258,
     T_ASSIGN = 259,
     T_BOOLTYPE = 260,
     T_BREAK = 261,
     T_COMMA = 262,
     T_CONTINUE = 263,
     T_DIV = 264,
     T_DOT = 265,
     T_ELSE = 266,
     T_EQ = 267,
     T_EXTERN = 268,
     T_FALSE = 269,
     T_FOR = 270,
     T_FUNC = 271,
     T_GEQ = 272,
     T_GT = 273,
     T_IF = 274,
     T_INTTYPE = 275,
     T_LCB = 276,
     T_LEFTSHIFT = 277,
     T_LEQ = 278,
     T_LPAREN = 279,
     T_LSB = 280,
     T_LT = 281,
     T_MINUS = 282,
     T_MOD = 283,
     T_MULT = 284,
     T_NEQ = 285,
     T_NOT = 286,
     T_NULL = 287,
     T_OR = 288,
     T_PACKAGE = 289,
     T_PLUS = 290,
     T_RCB = 291,
     T_RETURN = 292,
     T_RIGHTSHIFT = 293,
     T_RPAREN = 294,
     T_RSB = 295,
     T_SEMICOLON = 296,
     T_STRINGTYPE = 297,
     T_TRUE = 298,
     T_VAR = 299,
     T_VOID = 300,
     T_WHILE = 301,
     T_ID = 302,
     T_CHARCONSTANT = 303,
     T_INTCONSTANT = 304,
     T_STRINGCONSTANT = 305
   };
#endif
/* Tokens.  */
#define T_AND 258
#define T_ASSIGN 259
#define T_BOOLTYPE 260
#define T_BREAK 261
#define T_COMMA 262
#define T_CONTINUE 263
#define T_DIV 264
#define T_DOT 265
#define T_ELSE 266
#define T_EQ 267
#define T_EXTERN 268
#define T_FALSE 269
#define T_FOR 270
#define T_FUNC 271
#define T_GEQ 272
#define T_GT 273
#define T_IF 274
#define T_INTTYPE 275
#define T_LCB 276
#define T_LEFTSHIFT 277
#define T_LEQ 278
#define T_LPAREN 279
#define T_LSB 280
#define T_LT 281
#define T_MINUS 282
#define T_MOD 283
#define T_MULT 284
#define T_NEQ 285
#define T_NOT 286
#define T_NULL 287
#define T_OR 288
#define T_PACKAGE 289
#define T_PLUS 290
#define T_RCB 291
#define T_RETURN 292
#define T_RIGHTSHIFT 293
#define T_RPAREN 294
#define T_RSB 295
#define T_SEMICOLON 296
#define T_STRINGTYPE 297
#define T_TRUE 298
#define T_VAR 299
#define T_VOID 300
#define T_WHILE 301
#define T_ID 302
#define T_CHARCONSTANT 303
#define T_INTCONSTANT 304
#define T_STRINGCONSTANT 305




/* Copy the first part of user declarations.  */
#line 1 "decafcomp.y"

#include <iostream>
#include <ostream>
#include <string>
#include <cstdlib>
#include "decafcomp-defs.h"

int yylex(void);
int yyerror(char *);

using namespace std;

// this global variable contains all the generated code
static llvm::LLVMContext &Context = llvm::getGlobalContext();
static llvm::Module *TheModule;

// this is the method used to construct the LLVM intermediate code (IR)
static llvm::IRBuilder<> Builder(llvm::getGlobalContext());

// the calls to getGlobalContext() in the init above and in the
// following code ensures that we are incrementally generating
// instructions in the right order

// dummy main function
// should be replaced with actual codegen for the main method 
// using the full Decaf grammar
static llvm::Function *TheFunction = 0;

// we have to create a main function 
llvm::Function *gen_main_def() {
  // create the top-level definition for main
  llvm::FunctionType *FT = llvm::FunctionType::get(llvm::IntegerType::get(llvm::getGlobalContext(), 32), false);
  llvm::Function *TheFunction = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, "main", TheModule);
  if (TheFunction == 0) {
    throw runtime_error("empty function block"); 
  }
  // Create a new basic block which contains a sequence of LLVM instructions
  llvm::BasicBlock *BB = llvm::BasicBlock::Create(llvm::getGlobalContext(), "entry", TheFunction);
  // All subsequent calls to IRBuilder will place instructions in this location
  Builder.SetInsertPoint(BB);
  return TheFunction;
}

#include "decafcomp.cc"



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
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
#line 48 "decafcomp.y"
{
    class decafAST *ast;
    std::string *sval;
 }
/* Line 193 of yacc.c.  */
#line 248 "decafcomp.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 261 "decafcomp.tab.c"

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
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   221

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  90
/* YYNRULES -- Number of states.  */
#define YYNSTATES  183

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   305

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
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    18,    28,    32,    34,
      36,    38,    40,    42,    44,    46,    53,    54,    60,    63,
      72,    80,    81,    84,    89,    91,    95,    97,    99,   101,
     103,   104,   112,   121,   124,   129,   134,   135,   138,   140,
     143,   146,   152,   160,   166,   176,   179,   184,   190,   193,
     196,   198,   202,   209,   213,   217,   222,   224,   228,   230,
     232,   234,   238,   240,   244,   246,   250,   252,   256,   258,
     262,   264,   267,   269,   274,   276,   278,   282,   285,   287,
     289,   291,   293,   295,   297,   299,   301,   303,   305,   307,
     309
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      52,     0,    -1,    53,    -1,    54,    59,    -1,    -1,    13,
      16,    47,    24,    39,    57,    41,    54,    -1,    13,    16,
      47,    24,    55,    39,    57,    41,    54,    -1,    56,     7,
      55,    -1,    56,    -1,    42,    -1,    58,    -1,    45,    -1,
      58,    -1,    20,    -1,     5,    -1,    34,    47,    21,    60,
      65,    36,    -1,    -1,    60,    44,    47,    58,    41,    -1,
      60,    62,    -1,    60,    44,    63,    25,    49,    40,    58,
      41,    -1,    60,    44,    47,    58,     4,    64,    41,    -1,
      -1,    61,    62,    -1,    44,    63,    58,    41,    -1,    47,
      -1,    63,     7,    47,    -1,    49,    -1,    48,    -1,    43,
      -1,    14,    -1,    -1,    16,    47,    24,    39,    57,    67,
      65,    -1,    16,    47,    24,    66,    39,    57,    67,    65,
      -1,    47,    58,    -1,    47,    58,     7,    66,    -1,    21,
      61,    68,    36,    -1,    -1,    69,    68,    -1,    67,    -1,
      71,    41,    -1,    72,    41,    -1,    19,    24,    75,    39,
      67,    -1,    19,    24,    75,    39,    67,    11,    67,    -1,
      46,    24,    75,    39,    67,    -1,    15,    24,    70,    41,
      75,    41,    70,    39,    67,    -1,    37,    41,    -1,    37,
      24,    39,    41,    -1,    37,    24,    75,    39,    41,    -1,
       6,    41,    -1,     8,    41,    -1,    71,    -1,    71,     7,
      70,    -1,    47,    25,    75,    40,     4,    75,    -1,    47,
       4,    75,    -1,    47,    24,    39,    -1,    47,    24,    73,
      39,    -1,    74,    -1,    74,     7,    73,    -1,    75,    -1,
      50,    -1,    76,    -1,    75,    33,    76,    -1,    77,    -1,
      76,     3,    77,    -1,    78,    -1,    77,    82,    78,    -1,
      79,    -1,    78,    83,    79,    -1,    80,    -1,    79,    84,
      80,    -1,    81,    -1,    31,    80,    -1,    47,    -1,    47,
      25,    75,    40,    -1,    72,    -1,    64,    -1,    24,    75,
      39,    -1,    27,    81,    -1,    12,    -1,    30,    -1,    26,
      -1,    23,    -1,    18,    -1,    17,    -1,    35,    -1,    27,
      -1,    29,    -1,     9,    -1,    22,    -1,    38,    -1,    28,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   116,   116,   118,   130,   131,   139,   150,   156,   163,
     164,   167,   168,   171,   172,   175,   183,   184,   191,   202,
     218,   226,   227,   234,   248,   254,   262,   263,   274,   275,
     278,   279,   285,   294,   299,   306,   313,   314,   321,   322,
     323,   324,   328,   332,   336,   342,   343,   344,   345,   346,
     349,   354,   361,   362,   365,   366,   372,   377,   384,   385,
     395,   396,   401,   402,   407,   408,   411,   412,   415,   416,
     419,   420,   423,   424,   425,   426,   427,   428,   431,   432,
     433,   434,   435,   436,   438,   439,   442,   443,   444,   445,
     446
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_AND", "T_ASSIGN", "T_BOOLTYPE",
  "T_BREAK", "T_COMMA", "T_CONTINUE", "T_DIV", "T_DOT", "T_ELSE", "T_EQ",
  "T_EXTERN", "T_FALSE", "T_FOR", "T_FUNC", "T_GEQ", "T_GT", "T_IF",
  "T_INTTYPE", "T_LCB", "T_LEFTSHIFT", "T_LEQ", "T_LPAREN", "T_LSB",
  "T_LT", "T_MINUS", "T_MOD", "T_MULT", "T_NEQ", "T_NOT", "T_NULL", "T_OR",
  "T_PACKAGE", "T_PLUS", "T_RCB", "T_RETURN", "T_RIGHTSHIFT", "T_RPAREN",
  "T_RSB", "T_SEMICOLON", "T_STRINGTYPE", "T_TRUE", "T_VAR", "T_VOID",
  "T_WHILE", "T_ID", "T_CHARCONSTANT", "T_INTCONSTANT", "T_STRINGCONSTANT",
  "$accept", "start", "program", "extern_list", "extern_param",
  "extern_type", "method_type", "decaf_type", "decafpackage", "field_list",
  "var_list", "multivar", "id_list", "constant", "method_list",
  "param_list", "block", "statement_list", "statement", "assign_list",
  "assign", "method_call", "method_arg_list", "method_arg", "expr",
  "and_level", "comp_level", "plus_level", "mult_level", "not_level",
  "to_endpoint", "comp_op", "plus_op", "mult_op", 0
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
     305
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    51,    52,    53,    54,    54,    54,    55,    55,    56,
      56,    57,    57,    58,    58,    59,    60,    60,    60,    60,
      60,    61,    61,    62,    63,    63,    64,    64,    64,    64,
      65,    65,    65,    66,    66,    67,    68,    68,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      70,    70,    71,    71,    72,    72,    73,    73,    74,    74,
      75,    75,    76,    76,    77,    77,    78,    78,    79,    79,
      80,    80,    81,    81,    81,    81,    81,    81,    82,    82,
      82,    82,    82,    82,    83,    83,    84,    84,    84,    84,
      84
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     8,     9,     3,     1,     1,
       1,     1,     1,     1,     1,     6,     0,     5,     2,     8,
       7,     0,     2,     4,     1,     3,     1,     1,     1,     1,
       0,     7,     8,     2,     4,     4,     0,     2,     1,     2,
       2,     5,     7,     5,     9,     2,     4,     5,     2,     2,
       1,     3,     6,     3,     3,     4,     1,     3,     1,     1,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     2,     1,     4,     1,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     0,     2,     0,     0,     1,     0,     3,     0,
       0,     0,    16,    14,    13,     0,     9,     0,     8,    10,
      30,    11,     0,    12,     0,     0,     0,     0,    18,     0,
       4,     0,     7,     0,    24,     0,    15,     5,     4,     0,
       0,     0,     0,     0,     6,     0,     0,     0,     0,    17,
      25,     0,    23,     0,    33,     0,    29,    28,    27,    26,
       0,     0,    21,    30,     0,     0,    20,     0,    36,    31,
      34,    30,    19,     0,     0,     0,     0,     0,     0,     0,
       0,    22,    38,     0,    36,     0,     0,    32,    48,    49,
       0,     0,     0,    45,    24,     0,     0,     0,     0,     0,
      35,    37,    39,    40,     0,     0,    50,     0,     0,     0,
      72,    75,    74,     0,    60,    62,    64,    66,    68,    70,
       0,     0,     0,    53,    54,    59,     0,    56,    58,     0,
       0,     0,     0,    77,    71,     0,     0,     0,     0,    78,
      83,    82,    81,    80,    79,     0,    85,    84,     0,    87,
      88,    90,    86,    89,     0,    46,     0,     0,    55,     0,
       0,     0,    51,    76,     0,    61,    41,    63,    65,    67,
      69,    47,    43,    57,     0,     0,    73,     0,    52,     0,
      42,     0,    44
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,    17,    18,    22,    23,     8,    20,
      68,    28,    35,   111,    29,    47,    82,    83,    84,   105,
     106,   112,   126,   127,   128,   114,   115,   116,   117,   118,
     119,   145,   148,   154
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -130
static const yytype_int16 yypact[] =
{
      -3,    47,    32,  -130,    54,    36,  -130,    45,  -130,    78,
      88,     1,  -130,  -130,  -130,    13,  -130,    67,   114,  -130,
      33,  -130,   101,  -130,    13,     2,   103,   107,  -130,   121,
      -3,   134,  -130,   141,    51,    94,  -130,  -130,    -3,    31,
      27,   119,   129,   138,  -130,    13,    51,   143,    16,  -130,
    -130,   140,  -130,   162,   177,    13,  -130,  -130,  -130,  -130,
     144,    51,  -130,   170,   142,   162,  -130,   146,     8,  -130,
    -130,   170,  -130,   147,   149,   167,   168,    -4,   148,   169,
      69,  -130,  -130,   158,    20,   155,   156,  -130,  -130,  -130,
     152,   124,   113,  -130,  -130,   100,   124,   124,    48,   124,
    -130,  -130,  -130,  -130,     9,   157,   193,   124,    98,   124,
     106,  -130,  -130,   110,   198,   151,    76,    52,  -130,  -130,
     161,   120,   125,   171,  -130,  -130,   164,   199,   171,    49,
     124,   152,   137,  -130,  -130,   124,   124,   162,   124,  -130,
    -130,  -130,  -130,  -130,  -130,   124,  -130,  -130,   124,  -130,
    -130,  -130,  -130,  -130,   124,  -130,   166,   162,  -130,    86,
     201,    75,  -130,  -130,    99,   198,   197,   151,    76,    52,
    -130,  -130,  -130,  -130,   124,   152,  -130,   162,   171,   172,
    -130,   162,  -130
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -130,  -130,  -130,    85,   184,  -130,    -7,   -10,  -130,  -130,
    -130,   145,   132,   173,    55,   150,   -53,   128,  -130,  -129,
     -15,    -8,    56,  -130,   -88,    80,    79,    73,    71,  -104,
     112,  -130,  -130,  -130
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      63,    19,   162,   113,   121,   134,    13,    13,   122,   123,
       1,   129,    71,    97,    73,    19,    74,    31,    13,   132,
      92,    14,    14,    75,    40,    43,    73,    76,    74,    62,
      56,    48,     6,    14,    99,    75,    54,    93,    53,    76,
      15,    62,   161,    16,    16,    77,   179,   164,    65,    26,
     170,    67,    78,    85,    79,    80,    13,    77,    21,    57,
      86,   149,    56,     5,    58,    59,    79,    80,    49,    85,
      45,    14,   107,    97,   150,   108,    86,    27,    46,   109,
     151,   152,   136,     9,   166,    43,   178,   124,     7,   160,
     153,    57,    10,    98,    99,   110,    58,    59,   125,    13,
      56,    41,    11,   146,   172,    13,    24,    41,   136,    12,
     107,   147,    56,   108,    14,    37,   175,   109,    69,    42,
      14,    25,   107,    44,   180,   108,    87,    56,   182,    57,
      98,   135,   136,   110,    58,    59,   125,   107,    56,   176,
     108,    57,    30,   136,   109,   110,    58,    59,   107,   137,
      33,   108,   120,   136,    34,   109,    57,    36,   136,   156,
     110,    58,    59,   139,   157,    39,    50,    57,   140,   141,
     136,   110,    58,    59,   142,    38,   163,   143,    51,    52,
      61,   144,    55,    62,    64,    66,    26,    72,    88,    46,
      89,    90,    91,    96,   100,    94,   102,   103,   130,   104,
     131,   138,   155,   158,   136,   174,   159,   171,   177,    32,
      95,   181,   101,    81,    70,   173,   165,   167,   168,   169,
     133,    60
};

static const yytype_uint8 yycheck[] =
{
      53,    11,   131,    91,    92,   109,     5,     5,    96,    97,
      13,    99,    65,     4,     6,    25,     8,    24,     5,   107,
      24,    20,    20,    15,    34,    35,     6,    19,     8,    21,
      14,     4,     0,    20,    25,    15,    46,    41,    45,    19,
      39,    21,   130,    42,    42,    37,   175,   135,    55,    16,
     154,    61,    44,    68,    46,    47,     5,    37,    45,    43,
      68,     9,    14,    16,    48,    49,    46,    47,    41,    84,
      39,    20,    24,     4,    22,    27,    84,    44,    47,    31,
      28,    29,    33,    47,   137,    95,   174,    39,    34,    40,
      38,    43,    47,    24,    25,    47,    48,    49,    50,     5,
      14,     7,    24,    27,   157,     5,    39,     7,    33,    21,
      24,    35,    14,    27,    20,    30,    41,    31,    63,    25,
      20,     7,    24,    38,   177,    27,    71,    14,   181,    43,
      24,    25,    33,    47,    48,    49,    50,    24,    14,    40,
      27,    43,    41,    33,    31,    47,    48,    49,    24,    39,
      47,    27,    39,    33,    47,    31,    43,    36,    33,    39,
      47,    48,    49,    12,    39,    24,    47,    43,    17,    18,
      33,    47,    48,    49,    23,    41,    39,    26,    49,    41,
      40,    30,    39,    21,     7,    41,    16,    41,    41,    47,
      41,    24,    24,    24,    36,    47,    41,    41,    41,    47,
       7,     3,    41,    39,    33,     4,     7,    41,    11,    25,
      78,    39,    84,    68,    64,   159,   136,   138,   145,   148,
     108,    48
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    13,    52,    53,    54,    16,     0,    34,    59,    47,
      47,    24,    21,     5,    20,    39,    42,    55,    56,    58,
      60,    45,    57,    58,    39,     7,    16,    44,    62,    65,
      41,    57,    55,    47,    47,    63,    36,    54,    41,    24,
      58,     7,    25,    58,    54,    39,    47,    66,     4,    41,
      47,    49,    41,    57,    58,    39,    14,    43,    48,    49,
      64,    40,    21,    67,     7,    57,    41,    58,    61,    65,
      66,    67,    41,     6,     8,    15,    19,    37,    44,    46,
      47,    62,    67,    68,    69,    71,    72,    65,    41,    41,
      24,    24,    24,    41,    47,    63,    24,     4,    24,    25,
      36,    68,    41,    41,    47,    70,    71,    24,    27,    31,
      47,    64,    72,    75,    76,    77,    78,    79,    80,    81,
      39,    75,    75,    75,    39,    50,    73,    74,    75,    75,
      41,     7,    75,    81,    80,    25,    33,    39,     3,    12,
      17,    18,    23,    26,    30,    82,    27,    35,    83,     9,
      22,    28,    29,    38,    84,    41,    39,    39,    39,     7,
      40,    75,    70,    39,    75,    76,    67,    77,    78,    79,
      80,    41,    67,    73,     4,    41,    40,    11,    75,    70,
      67,    39,    67
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
        case 3:
#line 118 "decafcomp.y"
    {
        ProgramAST *prog = new ProgramAST((decafStmtList *)(yyvsp[(1) - (2)].ast), (PackageAST *)(yyvsp[(2) - (2)].ast));
        try {
            prog->Codegen();
        }
        catch (std::runtime_error &e) {
            cout << "semantic error: " << e.what() << endl;
            exit(EXIT_FAILURE);
        }
        delete prog;
    ;}
    break;

  case 4:
#line 130 "decafcomp.y"
    { (yyval.ast) = new decafStmtList(); ;}
    break;

  case 5:
#line 131 "decafcomp.y"
    {
        string* id = (yyvsp[(3) - (8)].sval);
        ExternAST* ext = new ExternAST(*id, (TypeSym*) (yyvsp[(6) - (8)].ast), NULL);
        delete id;
        decafStmtList* l = (decafStmtList*) (yyvsp[(8) - (8)].ast);
        l->push_front(ext);
        (yyval.ast) = l;
    ;}
    break;

  case 6:
#line 139 "decafcomp.y"
    {
        string* id = (yyvsp[(3) - (9)].sval);
        decafStmtList* ex_list = (decafStmtList*) (yyvsp[(5) - (9)].ast);
        ExternAST* ext = new ExternAST(*id, (TypeSym*) (yyvsp[(7) - (9)].ast), ex_list);
        delete id;
        decafStmtList* l = (decafStmtList*) (yyvsp[(9) - (9)].ast);
        l->push_front(ext);
        (yyval.ast) = l;
    ;}
    break;

  case 7:
#line 150 "decafcomp.y"
    { // one to many
        decafStmtList* ex_list = (decafStmtList*) (yyvsp[(3) - (3)].ast);
        // assert that ex_list != NULL
        ex_list->push_front((yyvsp[(1) - (3)].ast));
        (yyval.ast) = ex_list;
    ;}
    break;

  case 8:
#line 156 "decafcomp.y"
    {
        decafStmtList* ex_list = new decafStmtList();
        ex_list->push_back((yyvsp[(1) - (1)].ast));
        (yyval.ast) = ex_list;
    ;}
    break;

  case 9:
#line 163 "decafcomp.y"
    { (yyval.ast) = new VarDecl(V_STRING); ;}
    break;

  case 10:
#line 164 "decafcomp.y"
    { (yyval.ast) = new VarDecl((TypeSym*) (yyvsp[(1) - (1)].ast)); ;}
    break;

  case 11:
#line 167 "decafcomp.y"
    { (yyval.ast) = new TypeSym(V_VOID); ;}
    break;

  case 12:
#line 168 "decafcomp.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 13:
#line 171 "decafcomp.y"
    { (yyval.ast) = new TypeSym(V_INT); ;}
    break;

  case 14:
#line 172 "decafcomp.y"
    { (yyval.ast) = new TypeSym(V_BOOL); ;}
    break;

  case 15:
#line 175 "decafcomp.y"
    {
        decafStmtList* fields = (decafStmtList*) (yyvsp[(4) - (6)].ast);
        decafStmtList* stmts = (decafStmtList*) (yyvsp[(5) - (6)].ast);
        (yyval.ast) = new PackageAST(*(yyvsp[(2) - (6)].sval), fields, stmts); 
        delete (yyvsp[(2) - (6)].sval); 
    ;}
    break;

  case 16:
#line 183 "decafcomp.y"
    { (yyval.ast) = new decafStmtList(); ;}
    break;

  case 17:
#line 184 "decafcomp.y"
    {
        decafStmtList* var_list = (decafStmtList*) (yyvsp[(1) - (5)].ast);
        VarDecl* var = new VarDecl(*(yyvsp[(3) - (5)].sval));
        var->Type = (TypeSym*) (yyvsp[(4) - (5)].ast);
        var_list->push_back(new GlobalVar(var));
        (yyval.ast) = var_list;
    ;}
    break;

  case 18:
#line 191 "decafcomp.y"
    {
        decafStmtList* globals = (decafStmtList*) (yyvsp[(1) - (2)].ast);
        decafStmtList* mlist = (decafStmtList*) (yyvsp[(2) - (2)].ast);

        for (list<decafAST*>::iterator vit = mlist->begin(); 
            vit != mlist->end(); vit++) {
            VarDecl* var = (VarDecl*) *vit;
            globals->push_back(new GlobalVar(var));
        }
        (yyval.ast) = globals;
    ;}
    break;

  case 19:
#line 202 "decafcomp.y"
    { 
        decafStmtList* globals = (decafStmtList*) (yyvsp[(1) - (8)].ast);
        decafStmtList* mlist = (decafStmtList*) (yyvsp[(3) - (8)].ast);
        TypeSym* var_type = (TypeSym*) (yyvsp[(7) - (8)].ast);

        for (list<decafAST*>::iterator vit = mlist->begin(); 
            vit != mlist->end(); vit++) {
            VarDecl* var = (VarDecl*) *vit;
            var->Type = new TypeSym(*var_type);
            NumLit* arrsize = new NumLit(*(yyvsp[(5) - (8)].sval));
            globals->push_back(new GlobalVar(var, arrsize));
        }
        delete var_type;
        delete (yyvsp[(5) - (8)].sval);
        (yyval.ast) = globals;
    ;}
    break;

  case 20:
#line 218 "decafcomp.y"
    {
        decafStmtList* globals = (decafStmtList*) (yyvsp[(1) - (7)].ast);
        globals->push_back(new GlobalVar(*(yyvsp[(3) - (7)].sval), (TypeSym*) (yyvsp[(4) - (7)].ast), (yyvsp[(6) - (7)].ast)));
        delete (yyvsp[(3) - (7)].sval);
        (yyval.ast) = globals;
    ;}
    break;

  case 21:
#line 226 "decafcomp.y"
    { (yyval.ast) = new decafStmtList(); ;}
    break;

  case 22:
#line 227 "decafcomp.y"
    {
        decafStmtList* vars = (decafStmtList*) (yyvsp[(1) - (2)].ast);
        vars->push_back((yyvsp[(2) - (2)].ast));
        (yyval.ast) = vars;
    ;}
    break;

  case 23:
#line 234 "decafcomp.y"
    {
        decafStmtList* var_list = (decafStmtList*) (yyvsp[(2) - (4)].ast);
        TypeSym* var_type = (TypeSym*) (yyvsp[(3) - (4)].ast);

        for (list<decafAST*>::iterator vit = var_list->begin(); 
            vit != var_list->end(); vit++) {
            VarDecl* var = (VarDecl*) *vit;
            var->Type = new TypeSym(*var_type);
        }
        delete var_type;
        (yyval.ast) = var_list;
    ;}
    break;

  case 24:
#line 248 "decafcomp.y"
    { // one or more
        decafStmtList* v_list = new decafStmtList();
        VarDecl* var = new VarDecl(*(yyvsp[(1) - (1)].sval));
        v_list->push_back(var);
        (yyval.ast) = v_list;
    ;}
    break;

  case 25:
#line 254 "decafcomp.y"
    {
        decafStmtList* v_list = (decafStmtList*) (yyvsp[(1) - (3)].ast);
        VarDecl* var = new VarDecl(*(yyvsp[(3) - (3)].sval));
        v_list->push_back(var);
        (yyval.ast) = v_list;
    ;}
    break;

  case 26:
#line 262 "decafcomp.y"
    { (yyval.ast) = new NumLit(*(yyvsp[(1) - (1)].sval)); delete (yyvsp[(1) - (1)].sval); ;}
    break;

  case 27:
#line 263 "decafcomp.y"
    {
        try {
            string strrep = ConvertEsc(*(yyvsp[(1) - (1)].sval));
            int val = strrep[1];
            (yyval.ast) = new NumLit(val); 
            delete (yyvsp[(1) - (1)].sval);
        } catch (string e) {
            yyerror(e.c_str());
            return -1;
        }
    ;}
    break;

  case 28:
#line 274 "decafcomp.y"
    { (yyval.ast) = new BoolLit(true); ;}
    break;

  case 29:
#line 275 "decafcomp.y"
    { (yyval.ast) = new BoolLit(false); ;}
    break;

  case 30:
#line 278 "decafcomp.y"
    { (yyval.ast) = new decafStmtList(); ;}
    break;

  case 31:
#line 279 "decafcomp.y"
    {
        decafStmtList* l = (decafStmtList*) (yyvsp[(7) - (7)].ast);
        BlockAST* bloc = (BlockAST*) (yyvsp[(6) - (7)].ast);
        l->push_front(new MethodDecl(*(yyvsp[(2) - (7)].sval), (TypeSym*) (yyvsp[(5) - (7)].ast), NULL, bloc));
        (yyval.ast) = l;
    ;}
    break;

  case 32:
#line 285 "decafcomp.y"
    {
        decafStmtList* l = (decafStmtList*) (yyvsp[(8) - (8)].ast);
        BlockAST* bloc = (BlockAST*) (yyvsp[(7) - (8)].ast);
        decafStmtList* params = (decafStmtList*) (yyvsp[(4) - (8)].ast);
        l->push_front(new MethodDecl(*(yyvsp[(2) - (8)].sval), (TypeSym*) (yyvsp[(6) - (8)].ast), params, bloc));
        (yyval.ast) = l;
    ;}
    break;

  case 33:
#line 294 "decafcomp.y"
    { // one or more
        decafStmtList* res = new decafStmtList();
        res->push_back(new VarDecl(*(yyvsp[(1) - (2)].sval), (TypeSym*) (yyvsp[(2) - (2)].ast)));
        (yyval.ast) = res;
    ;}
    break;

  case 34:
#line 299 "decafcomp.y"
    {
        decafStmtList* res = (decafStmtList*) (yyvsp[(4) - (4)].ast);
        res->push_front(new VarDecl(*(yyvsp[(1) - (4)].sval), (TypeSym*) (yyvsp[(2) - (4)].ast)));
        (yyval.ast) = res;
    ;}
    break;

  case 35:
#line 306 "decafcomp.y"
    {
        decafStmtList* vars = (decafStmtList*) (yyvsp[(2) - (4)].ast);
        decafStmtList* stats = (decafStmtList*) (yyvsp[(3) - (4)].ast);
        (yyval.ast) = new BlockAST(vars, stats);
    ;}
    break;

  case 36:
#line 313 "decafcomp.y"
    { (yyval.ast) = new decafStmtList(); ;}
    break;

  case 37:
#line 314 "decafcomp.y"
    {
        decafStmtList* res = (decafStmtList*) (yyvsp[(2) - (2)].ast);
        res->push_front((yyvsp[(1) - (2)].ast));
        (yyval.ast) = res;
    ;}
    break;

  case 38:
#line 321 "decafcomp.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 39:
#line 322 "decafcomp.y"
    { (yyval.ast) = (yyvsp[(1) - (2)].ast);;}
    break;

  case 40:
#line 323 "decafcomp.y"
    { (yyval.ast) = (yyvsp[(1) - (2)].ast); ;}
    break;

  case 41:
#line 324 "decafcomp.y"
    { 
        BlockAST* ifBloc = (BlockAST*) (yyvsp[(5) - (5)].ast);
        (yyval.ast) = new IfElseAST((yyvsp[(3) - (5)].ast), ifBloc, NULL);
    ;}
    break;

  case 42:
#line 328 "decafcomp.y"
    {
        BlockAST* ifBloc = (BlockAST*) (yyvsp[(5) - (7)].ast);
        BlockAST* elseBloc = (BlockAST*) (yyvsp[(7) - (7)].ast);
        (yyval.ast) = new IfElseAST((yyvsp[(3) - (7)].ast), ifBloc, elseBloc);;}
    break;

  case 43:
#line 332 "decafcomp.y"
    {
        BlockAST* bloc = (BlockAST*) (yyvsp[(5) - (5)].ast);
        (yyval.ast) = new WhileStmtAST((yyvsp[(3) - (5)].ast), bloc);
    ;}
    break;

  case 44:
#line 336 "decafcomp.y"
    {
        decafStmtList* init = (decafStmtList*) (yyvsp[(3) - (9)].ast);
        decafStmtList* iter = (decafStmtList*) (yyvsp[(7) - (9)].ast);
        BlockAST* bloc = (BlockAST*) (yyvsp[(9) - (9)].ast);
        (yyval.ast) = new ForStmtAST(init, (yyvsp[(5) - (9)].ast), iter, bloc);
    ;}
    break;

  case 45:
#line 342 "decafcomp.y"
    { (yyval.ast) = new ReturnAST(NULL); ;}
    break;

  case 46:
#line 343 "decafcomp.y"
    { (yyval.ast) = new ReturnAST(NULL); ;}
    break;

  case 47:
#line 344 "decafcomp.y"
    { (yyval.ast) = new ReturnAST((yyvsp[(3) - (5)].ast)); ;}
    break;

  case 48:
#line 345 "decafcomp.y"
    { (yyval.ast) = new BreakAST(); ;}
    break;

  case 49:
#line 346 "decafcomp.y"
    { (yyval.ast) = new ContAST(); ;}
    break;

  case 50:
#line 349 "decafcomp.y"
    { // one or more
        decafStmtList* res = new decafStmtList(); 
        res->push_back((yyvsp[(1) - (1)].ast));
        (yyval.ast) = res;
    ;}
    break;

  case 51:
#line 354 "decafcomp.y"
    {
        decafStmtList* res = (decafStmtList*) (yyvsp[(3) - (3)].ast); 
        res->push_front((yyvsp[(1) - (3)].ast));
        (yyval.ast) = res;
    ;}
    break;

  case 52:
#line 361 "decafcomp.y"
    { (yyval.ast) = new AssignAST(*(yyvsp[(1) - (6)].sval), (yyvsp[(3) - (6)].ast), (yyvsp[(6) - (6)].ast)); ;}
    break;

  case 53:
#line 362 "decafcomp.y"
    { (yyval.ast) = new AssignAST(*(yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].ast)); ;}
    break;

  case 54:
#line 365 "decafcomp.y"
    { (yyval.ast) = new MethodCall(*(yyvsp[(1) - (3)].sval), NULL); ;}
    break;

  case 55:
#line 366 "decafcomp.y"
    {
        decafStmtList* args = (decafStmtList*) (yyvsp[(3) - (4)].ast); 
        (yyval.ast) = new MethodCall(*(yyvsp[(1) - (4)].sval), args);
    ;}
    break;

  case 56:
#line 372 "decafcomp.y"
    { // one or more
        decafStmtList* res = new decafStmtList(); 
        res->push_back((yyvsp[(1) - (1)].ast));
        (yyval.ast) = res;
    ;}
    break;

  case 57:
#line 377 "decafcomp.y"
    {
        decafStmtList* res = (decafStmtList*) (yyvsp[(3) - (3)].ast); 
        res->push_front((yyvsp[(1) - (3)].ast));
        (yyval.ast) = res;
    ;}
    break;

  case 58:
#line 384 "decafcomp.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 59:
#line 385 "decafcomp.y"
    { 
        try {
            (yyval.ast) = new StringLit(*(yyvsp[(1) - (1)].sval));
        } catch (string e) {
            yyerror(e.c_str());
            return -1;
        }
    ;}
    break;

  case 60:
#line 395 "decafcomp.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 61:
#line 396 "decafcomp.y"
    {
        (yyval.ast) = new Operation((yyvsp[(1) - (3)].ast), new OpSym(OR), (yyvsp[(3) - (3)].ast)); 
    ;}
    break;

  case 62:
#line 401 "decafcomp.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 63:
#line 402 "decafcomp.y"
    {
        (yyval.ast) = new Operation((yyvsp[(1) - (3)].ast), new OpSym(AND), (yyvsp[(3) - (3)].ast)); 
    ;}
    break;

  case 64:
#line 407 "decafcomp.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 65:
#line 408 "decafcomp.y"
    { (yyval.ast) = new Operation((yyvsp[(1) - (3)].ast), (OpSym*) (yyvsp[(2) - (3)].ast), (yyvsp[(3) - (3)].ast)); ;}
    break;

  case 66:
#line 411 "decafcomp.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 67:
#line 412 "decafcomp.y"
    { (yyval.ast) = new Operation((yyvsp[(1) - (3)].ast), (OpSym*) (yyvsp[(2) - (3)].ast), (yyvsp[(3) - (3)].ast)); ;}
    break;

  case 68:
#line 415 "decafcomp.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 69:
#line 416 "decafcomp.y"
    { (yyval.ast) = new Operation((yyvsp[(1) - (3)].ast), (OpSym*) (yyvsp[(2) - (3)].ast), (yyvsp[(3) - (3)].ast)); ;}
    break;

  case 70:
#line 419 "decafcomp.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 71:
#line 420 "decafcomp.y"
    { (yyval.ast) = new Operation((yyvsp[(2) - (2)].ast), new OpSym(NOT)); ;}
    break;

  case 72:
#line 423 "decafcomp.y"
    { (yyval.ast) = new VarCall(*(yyvsp[(1) - (1)].sval)); delete (yyvsp[(1) - (1)].sval); ;}
    break;

  case 73:
#line 424 "decafcomp.y"
    { (yyval.ast) = new VarCall(*(yyvsp[(1) - (4)].sval), (yyvsp[(3) - (4)].ast)); delete (yyvsp[(1) - (4)].sval); ;}
    break;

  case 74:
#line 425 "decafcomp.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 75:
#line 426 "decafcomp.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 76:
#line 427 "decafcomp.y"
    { (yyval.ast) = (yyvsp[(2) - (3)].ast); ;}
    break;

  case 77:
#line 428 "decafcomp.y"
    { (yyval.ast) = new Operation((yyvsp[(2) - (2)].ast), new OpSym(NEG)); ;}
    break;

  case 78:
#line 431 "decafcomp.y"
    { (yyval.ast) = new OpSym(EQ); ;}
    break;

  case 79:
#line 432 "decafcomp.y"
    { (yyval.ast) = new OpSym(NEQ); ;}
    break;

  case 80:
#line 433 "decafcomp.y"
    { (yyval.ast) = new OpSym(LT); ;}
    break;

  case 81:
#line 434 "decafcomp.y"
    { (yyval.ast) = new OpSym(LE); ;}
    break;

  case 82:
#line 435 "decafcomp.y"
    { (yyval.ast) = new OpSym(GT); ;}
    break;

  case 83:
#line 436 "decafcomp.y"
    { (yyval.ast) = new OpSym(GE); ;}
    break;

  case 84:
#line 438 "decafcomp.y"
    { (yyval.ast) = new OpSym(ADD); ;}
    break;

  case 85:
#line 439 "decafcomp.y"
    { (yyval.ast) = new OpSym(MINUS); ;}
    break;

  case 86:
#line 442 "decafcomp.y"
    { (yyval.ast) = new OpSym(MULT); ;}
    break;

  case 87:
#line 443 "decafcomp.y"
    { (yyval.ast) = new OpSym(DIV); ;}
    break;

  case 88:
#line 444 "decafcomp.y"
    { (yyval.ast) = new OpSym(LSHI); ;}
    break;

  case 89:
#line 445 "decafcomp.y"
    { (yyval.ast) = new OpSym(RSHI); ;}
    break;

  case 90:
#line 446 "decafcomp.y"
    { (yyval.ast) = new OpSym(MOD); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2255 "decafcomp.tab.c"
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


#line 449 "decafcomp.y"


int main() {
    // initialize LLVM
    // Make the module, which holds all the code.
    TheModule = new llvm::Module("Test", Context);
    // set up symbol table
    // set up dummy main function

    // parse the input and create the abstract syntax tree
    int retval = yyparse();
    TheFunction = TheModule->getFunction("main");

    // remove symbol table
    // Finish off the main function.
    // return 0 from main, which is EXIT_SUCCESS
    // Validate the generated code, checking for consistency.
    //verifyFunction(*TheFunction);
    // Print out all of the generated code to stderr
    TheModule->dump();

    return(retval >= 1 ? EXIT_FAILURE : EXIT_SUCCESS);
}


