%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "tabela.h"

extern int yylex();
extern int num_linha;
void yyerror(const char *s);
// Variável global para escopo (pode ser expandida depois)
int escopo_atual = 0;
%}

%union {
    int inteiro;
    float flutuante;
    char *str;
    No *arvore;
}

%token <inteiro> INTEIRO
%token <flutuante> FLUTUANTE
%token <str> IDENTIFICADOR
%token IF ELSE FOR IN RANGE PRINT
%token SOMA SUBTRACAO MULTIPLICACAO DIVISAO
%token ATRIBUICAO IGUAL DIFERENTE MENOR MAIOR MENOR_IGUAL MAIOR_IGUAL
%token ABRE_PAR FECHA_PAR DOIS_PONTOS

%type <arvore> programa lista_comandos comando
%type <arvore> comando_if comando_for
%type <arvore> expressao comando_print atribuicao

%left IGUAL DIFERENTE MENOR MAIOR MENOR_IGUAL MAIOR_IGUAL
%left SOMA SUBTRACAO
%left MULTIPLICACAO DIVISAO

%%

/*
 * Regras de produção da gramática
 */
programa
    : lista_comandos { raiz = $1; printf("Tabela de Simbolos:\n"); imprimirTabela(); printf("\nAST:\n"); imprimirAST(raiz, 0); }
    ;

lista_comandos
    : comando { $$ = criar_no(NO_LISTA_COMANDOS, $1, NULL); }
    | lista_comandos comando { $$ = criar_no(NO_LISTA_COMANDOS, $1, $2); }
    ;

comando
    : comando_if
    | comando_for
    | comando_print
    | atribuicao
    ;

comando_if
    : IF expressao DOIS_PONTOS lista_comandos
        { $$ = criar_if($2, $4, NULL); }
    | IF expressao DOIS_PONTOS lista_comandos ELSE DOIS_PONTOS lista_comandos
        { $$ = criar_if($2, $4, $7); }
    ;

comando_for
    : FOR IDENTIFICADOR IN RANGE ABRE_PAR expressao FECHA_PAR DOIS_PONTOS lista_comandos
        {
            // Inserir variável de controle do for como int
            inserirSimbolo($2, TIPO_INT, escopo_atual);
            $$ = criar_for($2, $6, $9);
        }
    ;

comando_print
    : PRINT ABRE_PAR expressao FECHA_PAR { $$ = criar_print($3); }
    ;

atribuicao
    : IDENTIFICADOR ATRIBUICAO expressao {
        // Inferir tipo da expressão
        Tipo tipo = TIPO_INT;
        if ($3 && $3->tipo == NO_FLUTUANTE) tipo = TIPO_FLOAT;
        // Inserir na tabela se não existir
        if (!buscarSimbolo($1, escopo_atual)) {
            inserirSimbolo($1, tipo, escopo_atual);
        }
        $$ = criar_atribuicao($1, $3);
    }
    ;

expressao
    : expressao SOMA expressao      { $$ = criar_aritmetico(OP_MAIS, $1, $3); }
    | expressao SUBTRACAO expressao { $$ = criar_aritmetico(OP_MENOS, $1, $3); }
    | expressao MULTIPLICACAO expressao { $$ = criar_aritmetico(OP_VEZES, $1, $3); }
    | expressao DIVISAO expressao   { $$ = criar_aritmetico(OP_DIVIDE, $1, $3); }
    | expressao IGUAL expressao     { $$ = criar_comparacao(OP_IGUAL, $1, $3); }
    | expressao DIFERENTE expressao { $$ = criar_comparacao(OP_DIFERENTE, $1, $3); }
    | expressao MENOR expressao     { $$ = criar_comparacao(OP_MENOR, $1, $3); }
    | expressao MAIOR expressao     { $$ = criar_comparacao(OP_MAIOR, $1, $3); }
    | expressao MENOR_IGUAL expressao { $$ = criar_comparacao(OP_MENOR_IGUAL, $1, $3); }
    | expressao MAIOR_IGUAL expressao { $$ = criar_comparacao(OP_MAIOR_IGUAL, $1, $3); }
    | INTEIRO                      { $$ = criar_numero($1); }
    | FLUTUANTE                    { $$ = criar_flutuante($1); }
    | IDENTIFICADOR                {
        // Verifica se a variável foi declarada
        if (!buscarSimbolo($1, escopo_atual)) {
            fprintf(stderr, "Erro: Variável '%s' não declarada (linha %d)\n", $1, num_linha);
            exit(1);
        }
        $$ = criar_identificador($1);
    }
    | ABRE_PAR expressao FECHA_PAR { $$ = $2; }
    ;

%%
void yyerror(const char *s) {
    fprintf(stderr, "Erro na linha %d: %s\n", num_linha, s);
    exit(1);
}