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
%token <str> operador_modulo

%token <str> atribuicao_igual

%token <str> comparador_igual
%token <str> comparador_diferente
%token <str> comparador_maior_que
%token <str> comparador_menor_que
%token <str> comparador_maior_igual
%token <str> comparador_menor_igual

%token <str> COMENT_LINHA
%token <str> COMENT_BLOCO

%token <intValue> NUM
%token <id> ID

%type <str> comparador
%type <str> operador
%type <str> comentarios
%type <str> atribuicao



%%

// id = a algo
input:
      atribuicao
    | expressao
    | comparacao
;

//COMENTARIOS
comentarios:
    COMENT_BLOCO {("Comentario: %s\n", $1);}
    | COMENT_LINHA {("Comentario: %s\n", $1);}

//ATRIBUICA0
// alguma coisa = alguma coisa
// alguma coisa = expressao(7+9)
atribuicao:
    ID atribuicao_igual expressao { printf("Atribuição: %s %s %s\n", $1, $2, $3); }
    | ID atribuicao_igual NUM { printf("Atribuição: %s %s %d\n", $1, $2, $3); }
    | ID atribuicao_igual ID { printf("Atribuição: %s %s %s\n", $1, $2, $3); }
    ;


// EXPRESSOES
// alguma coisa + alguma coisa
expressao:
    ID operador ID {printf("Expressão: %s %s %s\n", $1, $2, $3);}
    ID operador NUM {printf("Expressão: %s %s %d\n", $1, $2, $3);}
    NUM operador NUM {printf("Expressão: %d %s %d\n", $1, $2, $3);}
    NUM operador ID {printf("Expressão: %d %s %s\n", $1, $2, $3);}
    ;

// + - / %
operador:
    operador_mais { $$ = $1; }
    | operador_menos { $$ = $1; }
    | operador_multiplicacao { $$ = $1; }
    | operador_divisao { $$ = $1; }
    | operador_modulo { $$ = $1; }
    ;


// COMPARACOES
// alguma coisa > alguma coisa
comparacao:
    ID comparador ID { printf("Comparação: %s %s %s\n", $1, $2, $3); }
    | ID comparador NUM { printf("Comparação: %s %s %d\n", $1, $2, $3); }
    | NUM comparador ID { printf("Comparação: %d %s %s\n", $1, $2, $3); }
    | NUM comparador NUM { printf("Comparação: %d %s %d\n", $1, $2, $3); }
    ;

// > < == <=
comparador:
    comparador_igual       { $$ = $1; }
    | comparador_diferente { $$ = $1; }
    | comparador_maior_que { $$ = $1; }
    | comparador_menor_que { $$ = $1; }
    | comparador_maior_igual { $$ = $1; }
    | comparador_menor_igual { $$ = $1; }
    ;


%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático: %s\n", s);
}
