%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "tabela.h"

extern int yylex();
extern int num_linha;
void yyerror(const char *s);

int escopo_atual = 0;
ASTNode *root;
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
%token IF ELSE FOR IN RANGE PRINT DEF
%token SOMA SUBTRACAO MULTIPLICACAO DIVISAO
%token ATRIBUICAO IGUAL DIFERENTE MENOR MAIOR MENOR_IGUAL MAIOR_IGUAL
%token ABRE_PAR FECHA_PAR DOIS_PONTOS NEWLINE

%type <arvore> programa lista_comandos comando bloco
%type <arvore> comando_se comando_para comando_def
%type <arvore> atribuicao comando_imprimir expressao

%left IGUAL DIFERENTE MENOR MAIOR MENOR_IGUAL MAIOR_IGUAL
%left SOMA SUBTRACAO
%left MULTIPLICACAO DIVISAO

%%

programa
    : lista_comandos { root = $1; printf("Tabela de Simbolos:\n"); imprimirTabela(); printf("\nAST:\n"); imprimirAST(root, 0); }
    ;

lista_comandos
    : comando NEWLINE { $$ = criar_no(NODE_STMT_LIST, $1, NULL); }
    | lista_comandos comando NEWLINE { $$ = criar_no(NODE_STMT_LIST, $1, $2); }
    ;

bloco : lista_comandos{ $$ = $1; };



comando
    : comando_se
    | comando_para
    | comando_imprimir
    | atribuicao
    | comando_def
    ;

comando_se
    : IF expressao DOIS_PONTOS NEWLINE bloco {
        $$ = criar_if($2, $5, NULL);
    }
    | IF expressao DOIS_PONTOS NEWLINE bloco ELSE DOIS_PONTOS NEWLINE bloco {
        $$ = criar_if($2, $5, $9);
    }
    ;


comando_para
    : FOR IDENTIFICADOR IN RANGE ABRE_PAR expressao FECHA_PAR DOIS_PONTOS bloco {
        inserirSimbolo($2, TIPO_INT, escopo_atual);
        $$ = criar_for($2, $6, $9);
    }
    ;

comando_def
    : DEF IDENTIFICADOR ABRE_PAR FECHA_PAR DOIS_PONTOS bloco {
        inserirSimbolo($2, TIPO_FUNC, escopo_atual);
        $$ = criar_function_def($2, NULL, $6);
    }
    ;

comando_imprimir
    : PRINT ABRE_PAR expressao FECHA_PAR { $$ = criar_print($3); }
    ;

atribuicao
    : IDENTIFICADOR ATRIBUICAO expressao {
        Tipo tipo = TIPO_INT;
        if ($3 && $3->type == NODE_FLOAT) tipo = TIPO_FLOAT;
        if (!buscarSimbolo($1, escopo_atual)) {
            inserirSimbolo($1, tipo, escopo_atual);
        }
        $$ = criar_assignment($1, $3);
    }
    ;

expressao
    : expressao SOMA expressao           { $$ = criar_arithmetic(OP_PLUS, $1, $3); }
    | expressao SUBTRACAO expressao      { $$ = criar_arithmetic(OP_MINUS, $1, $3); }
    | expressao MULTIPLICACAO expressao  { $$ = criar_arithmetic(OP_TIMES, $1, $3); }
    | expressao DIVISAO expressao        { $$ = criar_arithmetic(OP_DIVIDE, $1, $3); }
    | expressao IGUAL expressao          { $$ = criar_comparison(OP_EQ, $1, $3); }
    | expressao DIFERENTE expressao      { $$ = criar_comparison(OP_NEQ, $1, $3); }
    | expressao MENOR expressao          { $$ = criar_comparison(OP_LT, $1, $3); }
    | expressao MAIOR expressao          { $$ = criar_comparison(OP_GT, $1, $3); }
    | expressao MENOR_IGUAL expressao    { $$ = criar_comparison(OP_LTE, $1, $3); }
    | expressao MAIOR_IGUAL expressao    { $$ = criar_comparison(OP_GTE, $1, $3); }
    | INTEIRO                            { $$ = criar_number($1); }
    | FLUTUANTE                          { $$ = criar_float($1); }
    | IDENTIFICADOR {
        if (!buscarSimbolo($1, escopo_atual)) {
            fprintf(stderr, "Erro: Variável '%s' não declarada (linha %d)\n", $1, num_linha);
            exit(1);
        }
        $$ = criar_identifier($1);
    }
    | ABRE_PAR expressao FECHA_PAR       { $$ = $2; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro na linha %d: %s\n", num_linha, s);
    exit(1);
}
