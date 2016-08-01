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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 48 "decafcomp.y"
{
    class decafAST *ast;
    std::string *sval;
 }
/* Line 1529 of yacc.c.  */
#line 154 "decafcomp.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

