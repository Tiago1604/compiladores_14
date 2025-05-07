#ifndef AST_H
#define AST_H

#include "tipos.h"

typedef struct AST {
    int tipo;               // Tipo do nó (e.g., TIPO_INT, TIPO_FLOAT, TIPO_STRING)
    int categoria;          // Categoria do nó (e.g., VARIAVEL, CONSTANTE, OPERACAO)
    union {
        int valor_int;      // Valor se for uma constante inteira
        float valor_float;  // Valor se for uma constante float
        char *nome;         // Nome da variável ou função
        struct {
            struct AST *esq; // Subárvore esquerda
            struct AST *dir; // Subárvore direita
        } op;               // Operandos se for uma operação
    } dado;
} AST;

// Funções para criação de nós da AST
AST* criar_no_constante_int(int valor);
AST* criar_no_constante_float(float valor);
AST* criar_no_variavel(char *nome);
AST* criar_no_operacao(int operador, AST *esq, AST *dir);

#endif // AST_H
