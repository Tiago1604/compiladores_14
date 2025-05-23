/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 23 "parser.y"

    #include "tipos.h"

#line 53 "parser.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    EQ = 258,                      /* EQ  */
    NEQ = 259,                     /* NEQ  */
    GE = 260,                      /* GE  */
    LE = 261,                      /* LE  */
    GT = 262,                      /* GT  */
    LT = 263,                      /* LT  */
    IF = 264,                      /* IF  */
    ELSE = 265,                    /* ELSE  */
    COLON = 266,                   /* COLON  */
    ID = 267,                      /* ID  */
    NUM = 268,                     /* NUM  */
    PRINT = 269,                   /* PRINT  */
    INT = 270,                     /* INT  */
    ASSIGN = 271,                  /* ASSIGN  */
    SEMICOLON = 272,               /* SEMICOLON  */
    LPAREN = 273,                  /* LPAREN  */
    RPAREN = 274,                  /* RPAREN  */
    PLUS = 275,                    /* PLUS  */
    MINUS = 276,                   /* MINUS  */
    TIMES = 277,                   /* TIMES  */
    DIVIDE = 278,                  /* DIVIDE  */
    FLOAT = 279,                   /* FLOAT  */
    CHAR = 280,                    /* CHAR  */
    RETURN = 281,                  /* RETURN  */
    WHILE = 282,                   /* WHILE  */
    FOR = 283,                     /* FOR  */
    BREAK = 284,                   /* BREAK  */
    CONTINUE = 285,                /* CONTINUE  */
    TRUE = 286,                    /* TRUE  */
    FALSE = 287,                   /* FALSE  */
    NONE = 288,                    /* NONE  */
    NOT = 289,                     /* NOT  */
    AND = 290,                     /* AND  */
    OR = 291,                      /* OR  */
    IS = 292,                      /* IS  */
    LAMBDA = 293,                  /* LAMBDA  */
    DEL = 294,                     /* DEL  */
    GLOBAL = 295,                  /* GLOBAL  */
    NONLOCAL = 296,                /* NONLOCAL  */
    ASSERT = 297,                  /* ASSERT  */
    RAISE = 298,                   /* RAISE  */
    TRY = 299,                     /* TRY  */
    EXCEPT = 300,                  /* EXCEPT  */
    FINALLY = 301,                 /* FINALLY  */
    WITH = 302,                    /* WITH  */
    YIELD = 303,                   /* YIELD  */
    DEF = 304,                     /* DEF  */
    CLASS = 305,                   /* CLASS  */
    ASYNC = 306,                   /* ASYNC  */
    AWAIT = 307,                   /* AWAIT  */
    MATCH = 308,                   /* MATCH  */
    CASE = 309,                    /* CASE  */
    TYPE = 310                     /* TYPE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 14 "parser.y"

    int intValue;
    char* id;
    char* str;
    float floatValue;
    char charValue;
    NoAST* ast;

#line 134 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
