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
     IN = 264,
     RANGE = 265,
     PRINT = 266,
     DEF = 267,
     SOMA = 268,
     SUBTRACAO = 269,
     MULTIPLICACAO = 270,
     DIVISAO = 271,
     ATRIBUICAO = 272,
     IGUAL = 273,
     DIFERENTE = 274,
     MENOR = 275,
     MAIOR = 276,
     MENOR_IGUAL = 277,
     MAIOR_IGUAL = 278,
     ABRE_PAR = 279,
     FECHA_PAR = 280,
     DOIS_PONTOS = 281,
     NEWLINE = 282
   };
#endif
/* Tokens.  */
#define INTEIRO 258
#define FLUTUANTE 259
#define IDENTIFICADOR 260
#define IF 261
#define ELSE 262
#define FOR 263
#define IN 264
#define RANGE 265
#define PRINT 266
#define DEF 267
#define SOMA 268
#define SUBTRACAO 269
#define MULTIPLICACAO 270
#define DIVISAO 271
#define ATRIBUICAO 272
#define IGUAL 273
#define DIFERENTE 274
#define MENOR 275
#define MAIOR 276
#define MENOR_IGUAL 277
#define MAIOR_IGUAL 278
#define ABRE_PAR 279
#define FECHA_PAR 280
#define DOIS_PONTOS 281
#define NEWLINE 282




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 15 "parser.y"
{
    int inteiro;
    float flutuante;
    char *str;
    ASTNode *arvore;
}
/* Line 1529 of yacc.c.  */
#line 110 "build/parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

