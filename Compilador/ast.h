#ifndef AST_H
#define AST_H

#include "tipos.h"

NoAST *criarNoNum(int valor);                       // Cria um nó para números
NoAST *criarNoId(const char *nome);                 // Cria um nó para identificadores
NoAST *criarNoOp(char operador, NoAST *esq, NoAST *dir);  // Cria um nó para operadores
void imprimirAST(const NoAST *raiz);                // Imprime AST em notação de expressão
void imprimirASTEmOrdem(const NoAST *raiz);         // Imprime AST em travessia em ordem
void liberarAST(NoAST *raiz);                       // Libera memória da AST

// Novas funções para otimização
NoAST *otimizarAST(NoAST *raiz);                    // Otimiza a AST usando constant folding
int avaliarExpressaoConstante(NoAST *raiz);         // Avalia expressões constantes

// Novas funções para geração de código
void gerarBitcode(NoAST *raiz);                     // Gera código intermediário (bitcode)
void gerarCodigoC(NoAST *raiz);                     // Gera código C a partir da AST

#endif