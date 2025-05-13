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


%type <intValue> expressao
%type <str> comparador
%type <str> comparacao

%%
program:
    program stmt
    |
    ;

stmt:
    statement
    | print
    | condicional


statement:
    ID atribuicao_igual expressao { printf("declaracao:\n    int %s = %d;\n", $1, $3); }

expressao:
    NUM { $$ = $1; }
    | ID { $$ = 0; }  // Para variáveis não inicializadas, o valor será 0
    | expressao operador_mais expressao { $$ = $1 + $3; }
    | expressao operador_menos expressao { $$ = $1 - $3; }
    | expressao operador_multiplicacao expressao { $$ = $1 * $3; }
    | expressao operador_divisao expressao { $$ = $1 / $3; }
    ;

print:
    comando_print caracter_abreParentese ID caracter_fechaParentese { printf("printf(\"%%d\\n\", %s);\n", $3); }
    | comando_print caracter_abreParentese NUM caracter_fechaParentese { printf("printf(\"%%d\\n\", %d);\n", $3); }
    | comando_print caracter_abreParentese FRASE caracter_fechaParentese { printf("é o print:\nprintf(%s);\n", $3); }
    ;

condicional:
    comando_if comparacao caracter_doispontos { printf("if(%s){ }\n", $2); }

comparacao:
    expressao comparador expressao 
    {
        char buffer[256];
        sprintf(buffer, "%d %s %d", $1, $2, $3); //"5 > 3"
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
