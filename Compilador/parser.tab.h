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
     EQ = 258,
     NEQ = 259,
     GE = 260,
     LE = 261,
     GT = 262,
     LT = 263,
     IF = 264,
     ELSE = 265,
     COLON = 266,
     ID = 267,
     NUM = 268,
     PRINT = 269,
     INT = 270,
     ASSIGN = 271,
     SEMICOLON = 272,
     LPAREN = 273,
     RPAREN = 274,
     PLUS = 275,
     MINUS = 276,
     TIMES = 277,
     DIVIDE = 278,
     FLOAT = 279,
     CHAR = 280,
     RETURN = 281,
     WHILE = 282,
     FOR = 283,
     BREAK = 284,
     CONTINUE = 285,
     TRUE = 286,
     FALSE = 287,
     NONE = 288,
     NOT = 289,
     AND = 290,
     OR = 291,
     IS = 292,
     LAMBDA = 293,
     DEL = 294,
     GLOBAL = 295,
     NONLOCAL = 296,
     ASSERT = 297,
     RAISE = 298,
     TRY = 299,
     EXCEPT = 300,
     FINALLY = 301,
     WITH = 302,
     YIELD = 303,
     DEF = 304,
     CLASS = 305,
     ASYNC = 306,
     AWAIT = 307,
     MATCH = 308,
     CASE = 309,
     TYPE = 310,
     LBRACE = 311,
     RBRACE = 312,
     LOWER_THAN_ELSE = 313
   };
#endif
/* Tokens.  */
#define EQ 258
#define NEQ 259
#define GE 260
#define LE 261
#define GT 262
#define LT 263
#define IF 264
#define ELSE 265
#define COLON 266
#define ID 267
#define NUM 268
#define PRINT 269
#define INT 270
#define ASSIGN 271
#define SEMICOLON 272
#define LPAREN 273
#define RPAREN 274
#define PLUS 275
#define MINUS 276
#define TIMES 277
#define DIVIDE 278
#define FLOAT 279
#define CHAR 280
#define RETURN 281
#define WHILE 282
#define FOR 283
#define BREAK 284
#define CONTINUE 285
#define TRUE 286
#define FALSE 287
#define NONE 288
#define NOT 289
#define AND 290
#define OR 291
#define IS 292
#define LAMBDA 293
#define DEL 294
#define GLOBAL 295
#define NONLOCAL 296
#define ASSERT 297
#define RAISE 298
#define TRY 299
#define EXCEPT 300
#define FINALLY 301
#define WITH 302
#define YIELD 303
#define DEF 304
#define CLASS 305
#define ASYNC 306
#define AWAIT 307
#define MATCH 308
#define CASE 309
#define TYPE 310
#define LBRACE 311
#define RBRACE 312
#define LOWER_THAN_ELSE 313




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 21 "parser.y"
{
    int intValue;    // Para números inteiros
    char* id;        // Para identificadores
    char* str;       // Para strings
    float floatValue; // Para números de ponto flutuante
    char charValue;   // Para caracteres
    NoAST* ast;       // Para nós da AST
}
/* Line 1529 of yacc.c.  */
#line 174 "parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;
