#ifndef TIPOS_H
#define TIPOS_H

typedef enum { AST_NUM, AST_ID, AST_OP } ASTTipo;

typedef struct noAST {
    ASTTipo tipo;
    int valor;
    char nome[32];
    char operador;
    struct noAST *esquerda;
    struct noAST *direita;
} NoAST;

#endif