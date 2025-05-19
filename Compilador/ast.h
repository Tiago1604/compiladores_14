#ifndef AST_H
#define AST_H

#include "tipos.h"

NoAST *criarNoNum(int valor);
NoAST *criarNoId(const char *nome);
NoAST *criarNoOp(char operador, NoAST *esq, NoAST *dir);
void imprimirAST(const NoAST *raiz);
void liberarAST(NoAST *raiz);

#endif