%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "tabela.h"

extern int yylex();
extern int num_linha;
void yyerror(const char *s);
int escopo_atual = 0;   /* escopo global */
%}

%union {
    int inteiro;
    float flutuante;
    char *str;
    No *arvore;          /* AST em "velha" API */
}

/* tokens */
%token <inteiro> INTEIRO
%token <flutuante> FLUTUANTE
%token <str> IDENTIFICADOR
%token IF ELSE FOR IN RANGE PRINT DEF
%token SOMA SUBTRACAO MULTIPLICACAO DIVISAO
%token ATRIBUICAO IGUAL DIFERENTE MENOR MAIOR MENOR_IGUAL MAIOR_IGUAL
%token ABRE_PAR FECHA_PAR DOIS_PONTOS

/* não usar "\" aqui: */
%type <arvore> programa
%type <arvore> lista_comandos
%type <arvore> chamada_funcao
%type <arvore> comando
%type <arvore> comando_se
%type <arvore> comando_para
%type <arvore> comando_imprimir
%type <arvore> atribuicao
%type <arvore> comando_def
%type <arvore> expressao

/* precedências */
%left IGUAL DIFERENTE MENOR MAIOR MENOR_IGUAL MAIOR_IGUAL
%left SOMA SUBTRACAO
%left MULTIPLICACAO DIVISAO

%%

programa
    : lista_comandos 
      { raiz = $1;
        printf("Tabela de Simbolos:\n"); imprimirTabela();
        printf("\nAST:\n"); imprimirAST(raiz, 0);
      }
    ;

lista_comandos
    : comando
      { $$ = criar_no(NO_LISTA_COMANDOS, $1, NULL); }
    | lista_comandos comando
      { $$ = criar_no(NO_LISTA_COMANDOS, $1, $2); }
    ;

comando
    : comando_if
    | comando_for
    | comando_print
    | atribuicao
    | comando_def
    | chamada_funcao
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
        abrir_escopo();
        inserirSimbolo($2, TIPO_INT, escopo_atual);
        $$ = criar_for($2, $6, $9);
        fechar_escopo();
      }
    ;

comando_imprimir
    : PRINT ABRE_PAR expressao FECHA_PAR
      { $$ = criar_print($3); }
    ;

atribuicao
    : IDENTIFICADOR ATRIBUICAO expressao
      {
        Tipo tipo = TIPO_INT;
        if ($3 && $3->tipo == NO_FLUTUANTE) tipo = TIPO_FLOAT;
        if (!buscarSimbolo($1, escopo_atual))
            inserirSimbolo($1, tipo, escopo_atual);
        $$ = criar_atribuicao($1, $3);
      }
    ;

comando_def
    : DEF IDENTIFICADOR ABRE_PAR FECHA_PAR DOIS_PONTOS 
      { 
        // Verificar se a função já foi declarada no escopo global
        if (buscarSimbolo($2, 0)) {
          fprintf(stderr, "Erro: função '%s' já foi declarada (linha %d)\n", $2, num_linha);
          exit(1);
        }
        // Inserir função no escopo global
        inserirSimbolo($2, TIPO_FUNC, 0); 
        // Abrir novo escopo para variáveis locais da função
        abrir_escopo();
      } 
      lista_comandos
      {
        $$ = criar_funcao($2, NULL, $7);
        // Fechar escopo da função
        fechar_escopo();
      }
    ;

chamada_funcao
    : IDENTIFICADOR ABRE_PAR FECHA_PAR
      {
        if (!buscarSimbolo($1, 0)) {
          fprintf(stderr, "Erro: função '%s' não declarada (linha %d)\n", $1, num_linha);
          exit(1);
        }
        $$ = criar_chamada_funcao($1, NULL); // NULL para argumentos, se não houver
      }
    ;
    
expressao
    : expressao SOMA expressao
      { $$ = criar_aritmetico(OP_MAIS, $1, $3); }
    | expressao SUBTRACAO expressao
      { $$ = criar_aritmetico(OP_MENOS, $1, $3); }
    | expressao MULTIPLICACAO expressao
      { $$ = criar_aritmetico(OP_VEZES, $1, $3); }
    | expressao DIVISAO expressao
      { $$ = criar_aritmetico(OP_DIVIDE, $1, $3); }
    | expressao IGUAL expressao
      { $$ = criar_comparacao(OP_IGUAL, $1, $3); }
    | expressao DIFERENTE expressao
      { $$ = criar_comparacao(OP_DIFERENTE, $1, $3); }
    | expressao MENOR expressao
      { $$ = criar_comparacao(OP_MENOR, $1, $3); }
    | expressao MAIOR expressao
      { $$ = criar_comparacao(OP_MAIOR, $1, $3); }
    | expressao MENOR_IGUAL expressao
      { $$ = criar_comparacao(OP_MENOR_IGUAL, $1, $3); }
    | expressao MAIOR_IGUAL expressao
      { $$ = criar_comparacao(OP_MAIOR_IGUAL, $1, $3); }
    | INTEIRO
      { $$ = criar_numero($1); }
    | FLUTUANTE
      { $$ = criar_flutuante($1); }
    | IDENTIFICADOR
      {
        if (!buscarSimbolo($1, escopo_atual)) {
          fprintf(stderr, "Erro: '%s' não declarada (linha %d)\n", $1, num_linha);
          exit(1);
        }
        $$ = criar_identificador($1);
      }
    | ABRE_PAR expressao FECHA_PAR
      { $$ = $2; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro na linha %d: %s\n", num_linha, s);
    exit(1);
}
