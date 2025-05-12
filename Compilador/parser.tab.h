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
     DIVIDE = 278
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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 10 "parser.y"
{
    int intValue;
    char* id;
    char* str;
}
/* Line 1529 of yacc.c.  */
#line 101 "parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

