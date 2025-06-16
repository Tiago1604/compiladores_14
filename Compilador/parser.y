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
    ASTNode *arvore;
}

%token <inteiro> INTEIRO
%token <flutuante> FLUTUANTE
%token <str> IDENTIFICADOR
%token IF ELSE FOR IN RANGE PRINT
%token SOMA SUBTRACAO MULTIPLICACAO DIVISAO
%token ATRIBUICAO IGUAL DIFERENTE MENOR MAIOR MENOR_IGUAL MAIOR_IGUAL
%token ABRE_PAR FECHA_PAR DOIS_PONTOS

%type <arvore> programa lista_comandos comando
%type <arvore> comando_se comando_para
%type <arvore> expressao comando_imprimir atribuicao

%left IGUAL DIFERENTE MENOR MAIOR MENOR_IGUAL MAIOR_IGUAL
%left SOMA SUBTRACAO
%left MULTIPLICACAO DIVISAO

%%

/*
 * Regras de produção da gramática
 */
programa
    : lista_comandos { root = $1; printf("Tabela de Simbolos:\n"); imprimirTabela(); printf("\nAST:\n"); imprimirAST(root, 0); }
    ;

lista_comandos
    : comando { $$ = criar_no(NODE_STMT_LIST, $1, NULL); }
    | lista_comandos comando { $$ = criar_no(NODE_STMT_LIST, $1, $2); }
    ;

comando
    : comando_se
    | comando_para
    | comando_imprimir
    | atribuicao
    ;

comando_se
    : IF expressao DOIS_PONTOS lista_comandos
        { $$ = criar_if($2, $4, NULL); }
    | IF expressao DOIS_PONTOS lista_comandos ELSE DOIS_PONTOS lista_comandos
        { $$ = criar_if($2, $4, $7); }
    ;

comando_para
    : FOR IDENTIFICADOR IN RANGE ABRE_PAR expressao FECHA_PAR DOIS_PONTOS lista_comandos
        {
            // Inserir variável de controle do for como int
            inserirSimbolo($2, TIPO_INT, escopo_atual);
            $$ = criar_for($2, $6, $9);
        }
    ;

comando_imprimir
    : PRINT ABRE_PAR expressao FECHA_PAR { $$ = criar_print($3); }
    ;

atribuicao
    : IDENTIFICADOR ATRIBUICAO expressao {
        // Inferir tipo da expressão
        Tipo tipo = TIPO_INT;
        if ($3 && $3->type == NODE_FLOAT) tipo = TIPO_FLOAT;
        // Inserir na tabela se não existir
        if (!buscarSimbolo($1, escopo_atual)) {
            inserirSimbolo($1, tipo, escopo_atual);
        }
        $$ = criar_assignment($1, $3);
    }
    ;

expressao
    : expressao SOMA expressao      { $$ = criar_arithmetic(OP_PLUS, $1, $3); }
    | expressao SUBTRACAO expressao { $$ = criar_arithmetic(OP_MINUS, $1, $3); }
    | expressao MULTIPLICACAO expressao { $$ = criar_arithmetic(OP_TIMES, $1, $3); }
    | expressao DIVISAO expressao   { $$ = criar_arithmetic(OP_DIVIDE, $1, $3); }
    | expressao IGUAL expressao     { $$ = criar_comparison(OP_EQ, $1, $3); }
    | expressao DIFERENTE expressao { $$ = criar_comparison(OP_NEQ, $1, $3); }
    | expressao MENOR expressao     { $$ = criar_comparison(OP_LT, $1, $3); }
    | expressao MAIOR expressao     { $$ = criar_comparison(OP_GT, $1, $3); }
    | expressao MENOR_IGUAL expressao { $$ = criar_comparison(OP_LTE, $1, $3); }
    | expressao MAIOR_IGUAL expressao { $$ = criar_comparison(OP_GTE, $1, $3); }
    | INTEIRO                      { $$ = criar_number($1); }
    | FLUTUANTE                    { $$ = criar_float($1); }
    | IDENTIFICADOR                {
        // Verifica se a variável foi declarada
        if (!buscarSimbolo($1, escopo_atual)) {
            fprintf(stderr, "Erro: Variável '%s' não declarada (linha %d)\n", $1, num_linha);
            exit(1);
        }
        $$ = criar_identifier($1);
    }
    | ABRE_PAR expressao FECHA_PAR { $$ = $2; }
    ;

%%
void yyerror(const char *s) {
    fprintf(stderr, "Erro na linha %d: %s\n", num_linha, s);
    exit(1);
}