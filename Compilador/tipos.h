#ifndef TIPOS_H
#define TIPOS_H

typedef enum { AST_NUM, AST_ID, AST_OP } ASTTipo;  // Enumeração dos tipos de nós da AST

typedef struct noAST {
    ASTTipo tipo;      // Tipo do nó (número, identificador ou operador)
    int valor;         // Valor armazenado para nós tipo AST_NUM
    char nome[32];     // Nome da variável para nós tipo AST_ID
    char operador;     // Operador (+, -, *, /) para nós tipo AST_OP
    struct noAST *esquerda;  // Filho esquerdo na árvore
    struct noAST *direita;   // Filho direito na árvore
} NoAST;

#endif