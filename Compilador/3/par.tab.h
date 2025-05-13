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
     operador_mais = 258,
     operador_menos = 259,
     operador_multiplicacao = 260,
     operador_divisao = 261,
     atribuicao_igual = 262,
     comando_print = 263,
     comando_if = 264,
     comparador_igual = 265,
     comparador_diferente = 266,
     comparador_maior_que = 267,
     comparador_menor_que = 268,
     comparador_maior_igual = 269,
     comparador_menor_igual = 270,
     NUM = 271,
     ID = 272,
     caracter_abreParentese = 273,
     caracter_fechaParentese = 274,
     caracter_doispontos = 275,
     FRASE = 276
   };
#endif
/* Tokens.  */
#define operador_mais 258
#define operador_menos 259
#define operador_multiplicacao 260
#define operador_divisao 261
#define atribuicao_igual 262
#define comando_print 263
#define comando_if 264
#define comparador_igual 265
#define comparador_diferente 266
#define comparador_maior_que 267
#define comparador_menor_que 268
#define comparador_maior_igual 269
#define comparador_menor_igual 270
#define NUM 271
#define ID 272
#define caracter_abreParentese 273
#define caracter_fechaParentese 274
#define caracter_doispontos 275
#define FRASE 276




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 10 "par.y"
{
    int intValue;
    char* id;
    char* str;
}
/* Line 1529 of yacc.c.  */
#line 97 "par.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

