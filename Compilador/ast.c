#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

NoAST *criarNoNum(int valor) {
    NoAST *novo = malloc(sizeof(NoAST));
    novo->tipo = AST_NUM;
    novo->valor = valor;
    novo->esquerda = novo->direita = NULL;
    return novo;
}

NoAST *criarNoId(const char *nome) {
    NoAST *novo = malloc(sizeof(NoAST));
    novo->tipo = AST_ID;
    strncpy(novo->nome, nome, 31);
    novo->nome[31] = '\0';
    novo->esquerda = novo->direita = NULL;
    return novo;
}

NoAST *criarNoOp(char operador, NoAST *esq, NoAST *dir) {
    NoAST *novo = malloc(sizeof(NoAST));
    novo->tipo = AST_OP;
    novo->operador = operador;
    novo->esquerda = esq;
    novo->direita = dir;
    return novo;
}

void imprimirAST(const NoAST *raiz) {
    if (!raiz) return;
    switch (raiz->tipo) {
        case AST_NUM:
            printf("%d", raiz->valor);
            break;
        case AST_ID:
            printf("%s", raiz->nome);
            break;
        case AST_OP:
            printf("(");
            imprimirAST(raiz->esquerda);
            printf(" %c ", raiz->operador);
            imprimirAST(raiz->direita);
            printf(")");
            break;
    }
}

void liberarAST(NoAST *raiz) {
    if (!raiz) return;
    liberarAST(raiz->esquerda);
    liberarAST(raiz->direita);
    free(raiz);
}