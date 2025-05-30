#ifndef AST_H
#define AST_H

#include "tipos.h"

// Funções existentes
NoAST *criarNoNum(int valor);                       // Cria um nó para números
NoAST *criarNoId(const char *nome);                 // Cria um nó para identificadores
NoAST *criarNoOp(char operador, NoAST *esq, NoAST *dir);  // Cria um nó para operadores

// Novas funções para AST aprimorada
NoAST *criarNoDecl(const char *tipo, const char *nome);   // Cria um nó de declaração
NoAST *criarNoAtrib(NoAST *id, NoAST *expr);              // Cria um nó de atribuição
NoAST *criarNoPrint(NoAST *expr);                         // Cria um nó de impressão
NoAST *criarNoIf(NoAST *condicao, NoAST *bloco);          // Cria um nó if
NoAST *criarNoIfElse(NoAST *condicao, NoAST *bloco_if, NoAST *bloco_else); // Cria nó if-else
NoAST *criarNoWhile(NoAST *condicao, NoAST *bloco);       // Cria um nó de laço while
NoAST *criarNoFor(NoAST *init, NoAST *cond, NoAST *incr, NoAST *bloco); // Cria um nó de laço for
NoAST *criarNoComp(TipoComparacao op, NoAST *esq, NoAST *dir);  // Cria um nó de comparação
NoAST *criarNoBloco(NoAST *lista_cmd);                   // Cria um nó de bloco de código
NoAST *criarNoListaCmd(NoAST *cmd, NoAST *proximo);      // Cria um nó de lista de comandos
NoAST *criarNoPrograma(NoAST *lista_cmd);                // Cria um nó de programa

// Funções para impressão e gerenciamento de memória
void imprimirAST(const NoAST *raiz);                // Imprime AST em notação de expressão
void imprimirASTEmOrdem(const NoAST *raiz);         // Imprime AST em travessia em ordem
void imprimirASTDetalhada(const NoAST *raiz, int nivel); // Imprime AST detalhada com indentação
void liberarAST(NoAST *raiz);                       // Libera memória da AST

#endif