%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void);
void yyerror(const char *s);
%}

%union {
    int intValue;
    char* id;
    char* str;
}

%token <str> operador_mais
%token <str> operador_menos
%token <str> operador_multiplicacao
%token <str> operador_divisao

%token <str> atribuicao_igual

%token comando_print
%token comando_if
%token comando_else

%token <str> comparador_igual
%token <str> comparador_diferente
%token <str> comparador_maior_que
%token <str> comparador_menor_que
%token <str> comparador_maior_igual
%token <str> comparador_menor_igual

%token <intValue> NUM
%token <id> ID
%token caracter_abreParentese
%token caracter_fechaParentese
%token caracter_doispontos
%token <str> FRASE


%type <str> expressao
%type <str> comparador
%type <str> comparacao
%type <str> stmt statement print condicional


%%
program:
    program stmt
    |
    ;

stmt:
    statement { $$ = $1; }
    | print    { $$ = $1; }
    | condicional { $$ = $1; }
    ;



statement:
    ID atribuicao_igual expressao {
        char buffer[256];
        // Formata a string para gerar a declaração no estilo C
        sprintf(buffer, "int %s = %s;", $1, $3);
        $$ = strdup(buffer); // Retorna a string formatada
    }
    ;

expressao:
    NUM { 
        char buffer[20];
        sprintf(buffer, "%d", yylval.intValue);
        $$ = strdup(buffer);
    }
    | ID {
        $$ = strdup($1);
    }
    | expressao operador_mais expressao 
    {
        char buffer[256];
        sprintf(buffer, "%s + %s", $1, $3);
        $$ = strdup(buffer);
    }
    | expressao operador_menos expressao 
    {
        char buffer[256];
        sprintf(buffer, "%s - %s", $1, $3);
        $$ = strdup(buffer);
    }
    | expressao operador_multiplicacao expressao 
    {
        char buffer[256];
        sprintf(buffer, "%s * %s", $1, $3);
        $$ = strdup(buffer);
    }
    | expressao operador_divisao expressao 
    {
        char buffer[256];
        sprintf(buffer, "%s / %s", $1, $3);
        $$ = strdup(buffer);
    }
    ;



print:
    comando_print caracter_abreParentese ID caracter_fechaParentese { printf("printf(\"%%d\\n\", %s);\n", $3); }
    | comando_print caracter_abreParentese NUM caracter_fechaParentese { printf("printf(\"%%d\\n\", %d);\n", $3); }
    | comando_print caracter_abreParentese FRASE caracter_fechaParentese { printf("printf(%s);\n", $3); }
    ;

condicional:
    // if x > x: instrucao
    comando_if comparacao caracter_doispontos stmt{ printf("if (%s) {\n%s\n}\n", $2, $4); }
    // if x > x: intrucao else: instrucao
    | comando_if comparacao caracter_doispontos stmt comando_else caracter_doispontos stmt { printf("if (%s) {\n%s\n} else {\n%s\n}\n", $2, $4, $7); }
    | comando_if ID caracter_doispontos stmt{ printf("if (%s) {\n%s\n}\n", $2, $4); }
    | comando_if ID caracter_doispontos stmt comando_else caracter_doispontos stmt { printf("if (%s) {\n%s\n} else {\n%s\n}\n", $2, $4, $7); }


comparacao:
    expressao comparador expressao 
    {
        char buffer[256];
        sprintf(buffer, "%s %s %s", $1, $2, $3); //"5 > 3"
        $$ = strdup(buffer);
        free($2);
    }
    ;

comparador:
    comparador_igual            { $$ = $1; }
    | comparador_diferente      { $$ = $1; }
    | comparador_maior_que      { $$ = $1; }
    | comparador_menor_que      { $$ = $1; }
    | comparador_maior_igual    { $$ = $1; }
    | comparador_menor_igual    { $$ = $1; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático: %s\n", s);
}