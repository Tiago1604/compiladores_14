%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);

%}

/* Declaração de tokens */
%token NUM
%token ESPACO

%union {
    int intValue; /* Para armazenar números */
}

%type <intValue> NUM 

%%
/* A gramática */
programa:
    lista_numeros
    ;

lista_numeros:
      lista_numeros NUM    { printf("Número lido: %d\n", $2); }
    | NUM                 { printf("Número lido: %d\n", $1); }
    | lista_numeros ESPACO { printf("Espaço detectado\n"); }
    | ESPACO              { printf("Espaço detectado\n"); }
    ;
%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático: %s\n", s);
}
