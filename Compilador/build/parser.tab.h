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
     INTEIRO = 258,
     FLUTUANTE = 259,
     IDENTIFICADOR = 260,
     IF = 261,
     ELSE = 262,
     FOR = 263,
     WHILE = 264,
     IN = 265,
     RANGE = 266,
     PRINT = 267,
     DEF = 268,
     SOMA = 269,
     SUBTRACAO = 270,
     MULTIPLICACAO = 271,
     DIVISAO = 272,
     ATRIBUICAO = 273,
     IGUAL = 274,
     DIFERENTE = 275,
     MENOR = 276,
     MAIOR = 277,
     MENOR_IGUAL = 278,
     MAIOR_IGUAL = 279,
     ABRE_PAR = 280,
     FECHA_PAR = 281,
     DOIS_PONTOS = 282
   };
#endif
/* Tokens.  */
#define INTEIRO 258
#define FLUTUANTE 259
#define IDENTIFICADOR 260
#define IF 261
#define ELSE 262
#define FOR 263
#define WHILE 264
#define IN 265
#define RANGE 266
#define PRINT 267
#define DEF 268
#define SOMA 269
#define SUBTRACAO 270
#define MULTIPLICACAO 271
#define DIVISAO 272
#define ATRIBUICAO 273
#define IGUAL 274
#define DIFERENTE 275
#define MENOR 276
#define MAIOR 277
#define MENOR_IGUAL 278
#define MAIOR_IGUAL 279
#define ABRE_PAR 280
#define FECHA_PAR 281
#define DOIS_PONTOS 282




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 14 "parser.y"
{
    int inteiro;
    float flutuante;
    char *str;
    No *arvore;          /* AST em "velha" API */
}
/* Line 1529 of yacc.c.  */
#line 110 "build/parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

