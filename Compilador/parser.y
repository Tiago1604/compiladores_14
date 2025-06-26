%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "tabela.h"

extern int yylex();
extern int num_linha;
void yyerror(const char *s);
// Variável global para escopo (pode ser expandida depois)
int escopo_atual = 0;

// Estrutura para gerenciar erros
typedef struct {
    int tem_erro;
    int num_erros;
    char mensagens[100][256];  // Array para armazenar até 100 mensagens de erro
} GerenciadorErros;

GerenciadorErros gerenciador_erros = {0, 0};

// Função para verificar se houve erros
int tem_erro() {
    return gerenciador_erros.tem_erro;
}

// Função para adicionar erro
void adicionar_erro(const char *mensagem) {
    if (gerenciador_erros.num_erros < 100) {
        snprintf(gerenciador_erros.mensagens[gerenciador_erros.num_erros], 
                256, "Linha %d: %s", num_linha, mensagem);
        gerenciador_erros.num_erros++;
        gerenciador_erros.tem_erro = 1;
    }
}

// Função auxiliar para verificar operandos de função em comparações
void verificar_operandos_funcao(No *op1, No *op2) {
    Simbolo *s1 = NULL;
    Simbolo *s2 = NULL;
    if (op1->tipo == NO_IDENTIFICADOR) {
        s1 = buscarSimbolo(op1->valor.sval, escopo_atual);
    }
    if (op2->tipo == NO_IDENTIFICADOR) {
        s2 = buscarSimbolo(op2->valor.sval, escopo_atual);
    }
    
    if ((s1 && s1->tipo == TIPO_FUNC) || (s2 && s2->tipo == TIPO_FUNC)) {
        char erro[256];
        const char *func_name = s1 && s1->tipo == TIPO_FUNC ? op1->valor.sval : op2->valor.sval;
        snprintf(erro, sizeof(erro), "Erro de tipo: tentativa de comparar a função '%s' com um valor", func_name);
        adicionar_erro(erro);
    }
}
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
%token IF ELSE FOR WHILE IN RANGE PRINT DEF
%token SOMA SUBTRACAO MULTIPLICACAO DIVISAO
%token ATRIBUICAO IGUAL DIFERENTE MENOR MAIOR MENOR_IGUAL MAIOR_IGUAL
%token ABRE_PAR FECHA_PAR DOIS_PONTOS


/* não usar "\" aqui: */
%type <arvore> programa
%type <arvore> lista_comandos
%type <arvore> chamada_funcao
%type <arvore> comando
%type <arvore> comando_if
%type <arvore> comando_for
%type <arvore> comando_print
%type <arvore> atribuicao
%type <arvore> comando_def
%type <arvore> expressao
%type <arvore> comando_while


%define parse.error verbose

// Definição de precedência e associatividade
%left IGUAL DIFERENTE MENOR MAIOR MENOR_IGUAL MAIOR_IGUAL
%left SOMA SUBTRACAO
%left MULTIPLICACAO DIVISAO
%nonassoc THEN
%nonassoc ELSE

%%

programa
    : lista_comandos { 
        if ($1 == NULL) { adicionar_erro("Erro de sintaxe no programa"); raiz = NULL;
        } else {
            raiz = $1;
        }
        
        // Imprime erros se houver
        if (gerenciador_erros.tem_erro) {
            printf("\nErros encontrados:\n");
            for (int i = 0; i < gerenciador_erros.num_erros; i++) {
                printf("%s\n", gerenciador_erros.mensagens[i]);
            }
            printf("\n");
        }
        
        printf("Tabela de Simbolos:\n"); 
        imprimirTabela(); 
        if (raiz != NULL) {
            printf("\nAST:\n"); 
            imprimirAST(raiz, 0);
        }
    }
    | error { 
        adicionar_erro("Erro de sintaxe no programa");
        raiz = NULL;
        yyerrok; 
    }
    ;

lista_comandos
    : comando { 
        if ($1 == NULL) {
            $$ = NULL;
        } else {
            $$ = criar_no(NO_LISTA_COMANDOS, $1, NULL);
        }
    }
    | lista_comandos comando { 
        if ($1 == NULL || $2 == NULL) {
            $$ = NULL;
        } else {
            // Criar uma lista linear, não aninhada
            No *ultimo = $1;
            while (ultimo->direita != NULL) {
                ultimo = ultimo->direita;
            }
            ultimo->direita = criar_no(NO_LISTA_COMANDOS, $2, NULL);
            $$ = $1;
        }
    }
    ;

comando
    : comando_if
    | comando_for
    | comando_while
    | comando_print
    | atribuicao
    | comando_def
    | chamada_funcao
    | error { 
        adicionar_erro("Erro de sintaxe no comando");
        $$ = NULL;
        yyerrok;
    }
    ;

comando_if
    : IF expressao DOIS_PONTOS lista_comandos %prec THEN
        { 
            if ($2 == NULL || $4 == NULL) {
                $$ = NULL;
            } else {
                $$ = criar_if($2, $4, NULL);
            }
        }
    | IF expressao DOIS_PONTOS lista_comandos ELSE DOIS_PONTOS lista_comandos
        { 
            if ($2 == NULL || $4 == NULL || $7 == NULL) {
                $$ = NULL;
            } else {
                $$ = criar_if($2, $4, $7);
            }
        }
    | IF expressao DOIS_PONTOS lista_comandos ELSE error {
            adicionar_erro("Erro de sintaxe: faltando ':' após 'else'");
            $$ = NULL;
            yyerrok;
        }
    | IF error {
            adicionar_erro("Erro na expressão de condição do if");
            $$ = NULL;
            yyerrok;
        }
    ;

comando_for
    : FOR IDENTIFICADOR IN RANGE ABRE_PAR expressao FECHA_PAR DOIS_PONTOS
      {
        // Inserir a variável 'i' no escopo atual antes de processar o corpo
        inserirSimbolo($2, TIPO_INT, escopo_atual);
        // Não abrir novo escopo aqui, pois isto isolaria a variável
      }
      lista_comandos
      {
        $$ = criar_for($2, $6, $10); // Ajuste o número de $10 para refletir a posição correta
      }
    ;
  
comando_while
    : WHILE expressao DOIS_PONTOS lista_comandos
      {
        abrir_escopo();
        $$ = criar_while($2, $4);
        fechar_escopo();
      }
    ;


comando_print
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
    : expressao SOMA expressao      { $$ = criar_aritmetico(OP_MAIS, $1, $3); }
    | expressao SUBTRACAO expressao { $$ = criar_aritmetico(OP_MENOS, $1, $3); }
    | expressao MULTIPLICACAO expressao { $$ = criar_aritmetico(OP_VEZES, $1, $3); }
    | expressao DIVISAO expressao   { $$ = criar_aritmetico(OP_DIVIDE, $1, $3); }
    | expressao IGUAL expressao     { 
        verificar_operandos_funcao($1, $3);
        $$ = criar_comparacao(OP_IGUAL, $1, $3); 
    }
    | expressao DIFERENTE expressao { 
        verificar_operandos_funcao($1, $3);
        $$ = criar_comparacao(OP_DIFERENTE, $1, $3); 
    }
    | expressao MENOR expressao     { 
        verificar_operandos_funcao($1, $3);
        $$ = criar_comparacao(OP_MENOR, $1, $3); 
    }
    | expressao MAIOR expressao     { 
        verificar_operandos_funcao($1, $3);
        $$ = criar_comparacao(OP_MAIOR, $1, $3); 
    }
    | expressao MENOR_IGUAL expressao { 
        verificar_operandos_funcao($1, $3);
        $$ = criar_comparacao(OP_MENOR_IGUAL, $1, $3); 
    }
    | expressao MAIOR_IGUAL expressao { 
        verificar_operandos_funcao($1, $3);
        $$ = criar_comparacao(OP_MAIOR_IGUAL, $1, $3); 
    }
    | INTEIRO                      { $$ = criar_numero($1); }
    | FLUTUANTE                    { $$ = criar_flutuante($1); }
    | IDENTIFICADOR                {
        // Verifica se a variável foi declarada
        if (!buscarSimbolo($1, escopo_atual)) {
            char erro[256];
            snprintf(erro, sizeof(erro), "Variável '%s' não declarada", $1);
            adicionar_erro(erro);
        }
        $$ = criar_identificador($1);
      }
    | ABRE_PAR expressao FECHA_PAR
      { $$ = $2; }
    ;

%%

void yyerror(const char *s) {
    char erro[256];
    // Mensagens de erro específicas
    if (strstr(s, "expecting DOIS_PONTOS")) {
        snprintf(erro, sizeof(erro), "Erro de sintaxe: faltando ':' após a palavra-chave");
    } else {
        snprintf(erro, sizeof(erro), "Erro de sintaxe: %s", s);
    }
    adicionar_erro(erro);
}
