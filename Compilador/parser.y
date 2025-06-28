%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "tabela.h"

// Declarações de funções externas e variáveis de controle
extern int yylex();    // Função do analisador léxico gerada pelo Flex
extern int num_linha;  // Controla o número da linha atual para mensagens de erro
void yyerror(const char *s);  // Função para tratamento de erros sintáticos

// Variável global para controlar o escopo atual das variáveis e funções
int escopo_atual = 0;  // 0 representa o escopo global

// Estrutura para gerenciar erros encontrados durante a análise
typedef struct {
    int tem_erro;           // Flag indicando se há algum erro
    int num_erros;          // Contador de erros encontrados
    char mensagens[100][256];  // Array para armazenar até 100 mensagens de erro
} GerenciadorErros;

// Inicializa o gerenciador de erros
GerenciadorErros gerenciador_erros = {0, 0};

// Função para verificar se houve erros durante a análise
int tem_erro() {
    return gerenciador_erros.tem_erro;
}

// Função para adicionar uma mensagem de erro ao gerenciador
void adicionar_erro(const char *mensagem) {
    if (gerenciador_erros.num_erros < 100) {
        // Formata a mensagem incluindo o número da linha
        snprintf(gerenciador_erros.mensagens[gerenciador_erros.num_erros], 
                256, "Linha %d: %s", num_linha, mensagem);
        gerenciador_erros.num_erros++;
        gerenciador_erros.tem_erro = 1;
    }
}

// Função que verifica se operandos de comparação são funções (o que seria inválido)
void verificar_operandos_funcao(No *op1, No *op2) {
    Simbolo *s1 = NULL;
    Simbolo *s2 = NULL;
    // Busca os símbolos na tabela se forem identificadores
    if (op1->tipo == NO_IDENTIFICADOR) {
        s1 = buscarSimbolo(op1->valor.sval, escopo_atual);
    }
    if (op2->tipo == NO_IDENTIFICADOR) {
        s2 = buscarSimbolo(op2->valor.sval, escopo_atual);
    }
    
    // Se algum dos operandos for uma função, reporta erro
    if ((s1 && s1->tipo == TIPO_FUNC) || (s2 && s2->tipo == TIPO_FUNC)) {
        char erro[256];
        const char *func_name = s1 && s1->tipo == TIPO_FUNC ? op1->valor.sval : op2->valor.sval;
        snprintf(erro, sizeof(erro), "Erro de tipo: tentativa de comparar a função '%s' com um valor", func_name);
        adicionar_erro(erro);
    }
}
%}

// Define os tipos de dados dos tokens e não-terminais (união semântica)
%union {
    int inteiro;         // Para tokens de número inteiro
    float flutuante;     // Para tokens de número de ponto flutuante
    char *str;           // Para tokens de strings e identificadores
    No *arvore;          // Para nós da árvore sintática abstrata (AST)
}

/* Definição dos tokens reconhecidos pelo analisador léxico */
%token <inteiro> INTEIRO       // Token para números inteiros
%token <flutuante> FLUTUANTE   // Token para números de ponto flutuante
%token <str> IDENTIFICADOR     // Token para identificadores (nomes de variáveis/funções)
%token <str> STRING            // Token para literais string
%token IF ELSE FOR WHILE IN RANGE PRINT DEF  // Tokens para palavras-chave
%token SOMA SUBTRACAO MULTIPLICACAO DIVISAO  // Tokens para operadores aritméticos
%token ATRIBUICAO IGUAL DIFERENTE MENOR MAIOR MENOR_IGUAL MAIOR_IGUAL  // Tokens para operadores de atribuição e comparação
%token ABRE_PAR FECHA_PAR DOIS_PONTOS  // Tokens para símbolos de pontuação


/* Tipos para os não-terminais da gramática */
%type <arvore> programa         // Representa o programa completo
%type <arvore> lista_comandos   // Lista de comandos do programa
%type <arvore> chamada_funcao   // Chamada de função
%type <arvore> comando          // Comando individual
%type <arvore> comando_if       // Estrutura de condição if/else
%type <arvore> comando_for      // Loop for
%type <arvore> comando_print    // Comando de impressão
%type <arvore> atribuicao       // Atribuição de variável
%type <arvore> comando_def      // Definição de função
%type <arvore> expressao        // Expressões gerais
%type <arvore> comando_while    // Loop while

// Define a precedência e associatividade dos operadores (ordem crescente de precedência)
%left IGUAL DIFERENTE MENOR MAIOR MENOR_IGUAL MAIOR_IGUAL  // Operadores de comparação com menor precedência
%left SOMA SUBTRACAO                                       // Operadores aditivos
%left MULTIPLICACAO DIVISAO                                // Operadores multiplicativos com maior precedência
%nonassoc THEN                                             // Marcador para resolução do conflito do if-dangling
%nonassoc ELSE                                             // Marcador para associar else com o if mais próximo

// Configura o Bison para gerar mensagens de erro mais detalhadas
%define parse.error verbose

%%

// Regra inicial da gramática - representa o programa completo
programa
    : lista_comandos { 
        if ($1 == NULL) { 
            adicionar_erro("Erro de sintaxe no programa"); 
            raiz = NULL;  // Raiz da AST é NULL se houver erro
        } else {
            raiz = $1;    // Define a raiz da AST como a lista de comandos
        }
        
        // Imprime todos os erros encontrados durante a análise
        if (gerenciador_erros.tem_erro) {
            printf("\nErros encontrados:\n");
            for (int i = 0; i < gerenciador_erros.num_erros; i++) {
                printf("%s\n", gerenciador_erros.mensagens[i]);
            }
            printf("\n");
        }
        
        // Imprime a tabela de símbolos e a AST para depuração
        printf("Tabela de Simbolos:\n"); 
        imprimirTabela(); 
        if (raiz != NULL) {
            printf("\nAST:\n"); 
            imprimirAST(raiz, 0);
        }
    }
    | error { 
        // Tratamento de erro em nível de programa
        adicionar_erro("Erro de sintaxe no programa");
        raiz = NULL;
        yyerrok;  // Permite que o parser se recupere do erro
    }
    ;

// Define uma lista de comandos sequenciais
lista_comandos
    : comando { 
        // Caso base: um único comando
        if ($1 == NULL) {
            $$ = NULL;
        } else {
            $$ = criar_no(NO_LISTA_COMANDOS, $1, NULL);  // Cria nó para um comando
        }
    }
    | lista_comandos comando { 
        // Caso recursivo: adiciona um novo comando à lista existente
        if ($1 == NULL || $2 == NULL) {
            $$ = NULL;
        } else {
            // Cria uma estrutura linear de comandos, não aninhada
            No *ultimo = $1;
            while (ultimo->direita != NULL) {
                ultimo = ultimo->direita;
            }
            ultimo->direita = criar_no(NO_LISTA_COMANDOS, $2, NULL);
            $$ = $1;  // Retorna o início da lista
        }
    }
    ;

// Define os tipos de comandos aceitos pelo compilador
comando
    : comando_if       // Estruturas condicionais if/else
    | comando_for      // Loops for
    | comando_while    // Loops while 
    | comando_print    // Comandos de impressão
    | atribuicao       // Atribuições de variáveis
    | comando_def      // Definições de funções
    | chamada_funcao   // Chamadas de função
    | error { 
        // Tratamento de erro para comandos inválidos
        adicionar_erro("Erro de sintaxe no comando");
        $$ = NULL;
        yyerrok;  // Permite que o parser continue após o erro
    }
    ;

// Define a estrutura condicional if-else
comando_if
    : IF expressao DOIS_PONTOS lista_comandos %prec THEN
        { 
            // If simples sem else
            if ($2 == NULL || $4 == NULL) {
                $$ = NULL;
            } else {
                $$ = criar_if($2, $4, NULL);  // Cria nó if sem bloco else
            }
        }
    | IF expressao DOIS_PONTOS lista_comandos ELSE DOIS_PONTOS lista_comandos
        { 
            // If com else
            if ($2 == NULL || $4 == NULL || $7 == NULL) {
                $$ = NULL;
            } else {
                $$ = criar_if($2, $4, $7);  // Cria nó if-else completo
            }
        }
    | IF expressao DOIS_PONTOS lista_comandos ELSE error {
            // Erro específico: falta ":" após else
            adicionar_erro("Erro de sintaxe: faltando ':' após 'else'");
            $$ = NULL;
            yyerrok;
        }
    | IF error {
            // Erro na expressão de condição
            adicionar_erro("Erro na expressão de condição do if");
            $$ = NULL;
            yyerrok;
        }
    ;

// Define a estrutura de loop for (estilo Python)
comando_for
    : FOR IDENTIFICADOR IN RANGE ABRE_PAR expressao FECHA_PAR DOIS_PONTOS
      {
        // Registra a variável de iteração na tabela de símbolos
        inserirSimbolo($2, TIPO_INT, escopo_atual);
        // Não abre novo escopo para não isolar a variável de iteração
      }
      lista_comandos
      {
        // Cria o nó for com variável de iteração, limite e corpo
        $$ = criar_for($2, $6, $10);
      }
    ;
  
// Define a estrutura de loop while
comando_while
    : WHILE expressao DOIS_PONTOS lista_comandos
      {
        // Abre um novo escopo para variáveis locais ao loop
        abrir_escopo();
        // Cria o nó while com condição e corpo
        $$ = criar_while($2, $4);
        // Fecha o escopo ao sair do loop
        fechar_escopo();
      }
    ;

// Define o comando de impressão (print)
comando_print
    : PRINT ABRE_PAR expressao FECHA_PAR
      { $$ = criar_print($3); }  // Cria nó para imprimir a expressão
    ;

// Define atribuição de valores a variáveis
atribuicao
    : IDENTIFICADOR ATRIBUICAO expressao
      {
        // Determina o tipo da variável com base na expressão
        Tipo tipo = TIPO_INT;  // Tipo padrão é inteiro
        if ($3 && $3->tipo == NO_FLUTUANTE) tipo = TIPO_FLOAT;  // Promove para float se necessário
        
        // Se a variável não existe, insere na tabela de símbolos
        if (!buscarSimbolo($1, escopo_atual))
            inserirSimbolo($1, tipo, escopo_atual);
            
        // Cria o nó de atribuição
        $$ = criar_atribuicao($1, $3);
      }
    ;

// Define a declaração de funções
comando_def
    : DEF IDENTIFICADOR ABRE_PAR FECHA_PAR DOIS_PONTOS 
      { 
        // Verifica se a função já foi declarada no escopo global
        if (buscarSimbolo($2, 0)) {
          fprintf(stderr, "Erro: função '%s' já foi declarada (linha %d)\n", $2, num_linha);
          exit(1);
        }
        
        // Registra a função na tabela de símbolos global
        inserirSimbolo($2, TIPO_FUNC, 0); 
        
        // Cria novo escopo para variáveis locais da função
        abrir_escopo();
      } 
      lista_comandos
      {
        // Cria o nó de definição de função
        $$ = criar_funcao($2, NULL, $7);
        
        // Fecha o escopo da função
        fechar_escopo();
      }
    ;

// Define chamada de função
chamada_funcao
    : IDENTIFICADOR ABRE_PAR FECHA_PAR
      {
        // Verifica se a função foi declarada antes de ser chamada
        if (!buscarSimbolo($1, 0)) {
          fprintf(stderr, "Erro: função '%s' não declarada (linha %d)\n", $1, num_linha);
          exit(1);
        }
        
        // Cria o nó de chamada de função (sem argumentos)
        $$ = criar_chamada_funcao($1, NULL);
      }
    ;
    
// Define os tipos de expressões suportados
expressao
    : expressao SOMA expressao      { $$ = criar_aritmetico(OP_MAIS, $1, $3); }    // Adição
    | expressao SUBTRACAO expressao { $$ = criar_aritmetico(OP_MENOS, $1, $3); }   // Subtração
    | expressao MULTIPLICACAO expressao { $$ = criar_aritmetico(OP_VEZES, $1, $3); } // Multiplicação
    | expressao DIVISAO expressao   { $$ = criar_aritmetico(OP_DIVIDE, $1, $3); }  // Divisão
    | expressao IGUAL expressao     { 
        // Comparação de igualdade
        verificar_operandos_funcao($1, $3);  // Verifica se não há funções sendo comparadas
        $$ = criar_comparacao(OP_IGUAL, $1, $3); 
    }
    | expressao DIFERENTE expressao { 
        // Comparação de diferença
        verificar_operandos_funcao($1, $3);
        $$ = criar_comparacao(OP_DIFERENTE, $1, $3); 
    }
    | expressao MENOR expressao     { 
        // Comparação "menor que"
        verificar_operandos_funcao($1, $3);
        $$ = criar_comparacao(OP_MENOR, $1, $3); 
    }
    | expressao MAIOR expressao     { 
        // Comparação "maior que"
        verificar_operandos_funcao($1, $3);
        $$ = criar_comparacao(OP_MAIOR, $1, $3); 
    }
    | expressao MENOR_IGUAL expressao { 
        // Comparação "menor ou igual"
        verificar_operandos_funcao($1, $3);
        $$ = criar_comparacao(OP_MENOR_IGUAL, $1, $3); 
    }
    | expressao MAIOR_IGUAL expressao { 
        // Comparação "maior ou igual"
        verificar_operandos_funcao($1, $3);
        $$ = criar_comparacao(OP_MAIOR_IGUAL, $1, $3); 
    }
    | INTEIRO                      { $$ = criar_numero($1); }           // Literal inteiro
    | FLUTUANTE                    { $$ = criar_flutuante($1); }        // Literal float
    | STRING                       { $$ = criar_string($1); }           // Literal string
    | IDENTIFICADOR                {
        // Uso de variável
        // Verifica se a variável foi declarada antes de ser usada
        if (!buscarSimbolo($1, escopo_atual)) {
            char erro[256];
            snprintf(erro, sizeof(erro), "Variável '%s' não declarada", $1);
            adicionar_erro(erro);
        }
        $$ = criar_identificador($1);
      }
    | ABRE_PAR expressao FECHA_PAR { $$ = $2; }  // Expressão entre parênteses
    ;

%%

// Função chamada pelo Bison quando ocorre um erro sintático
void yyerror(const char *s) {
    char erro[256];
    
    // Fornece mensagens de erro específicas para problemas comuns
    if (strstr(s, "expecting DOIS_PONTOS")) {
        snprintf(erro, sizeof(erro), "Erro de sintaxe: faltando ':' após a palavra-chave");
    } else {
        snprintf(erro, sizeof(erro), "Erro de sintaxe: %s", s);
    }
    
    // Registra o erro no gerenciador
    adicionar_erro(erro);
}
