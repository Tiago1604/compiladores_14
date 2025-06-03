/* exemplo.y */

%{
#include <stdio.h>
#include <stdlib.h>

/* 
   Declarações explícitas para evitar warnings de 
   “implicit declaration of function yylex/yyerror”
*/
int yylex(void);
void yyerror(const char *s);

%}

%token NUM
%token IDENT
%token ESPA

%union {
    int inteiro;
    char * texto;
}

%type <inteiro> NUM
%type <texto> IDENT

%%

programa:
    lista_elementos
    ;

lista_elementos:
    lista_elementos NUM {printf("numero lido: %d\n", $2);}
    | lista_elementos IDENT {printf("identificador lido: %s\n", $2);}
    | lista_elementos ESPA {printf("espaco encontradp\n");}
    | NUM {printf("numero lido: %d\n", $1);}
    | IDENT {printf("identificador lido: %s\n", $1);}
    | ESPA {printf("espaco encontradp\n");}
    ;
%%

/* Definição de yyerror */
void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático: %s\n", s);
}

