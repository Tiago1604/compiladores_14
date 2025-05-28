#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para criar um nó de número na AST
NoAST *criarNoNum(int valor) {
    NoAST *novo = malloc(sizeof(NoAST));  // Aloca memória para o nó
    novo->tipo = AST_NUM;                 // Define tipo como número
    novo->valor = valor;                  // Armazena o valor
    novo->esquerda = novo->direita = NULL;  // Inicializa filhos como nulos
    return novo;
}

// Função para criar um nó de identificador (variável) na AST
NoAST *criarNoId(const char *nome) {
    NoAST *novo = malloc(sizeof(NoAST));  // Aloca memória para o nó
    novo->tipo = AST_ID;                  // Define tipo como identificador
    strncpy(novo->nome, nome, 31);        // Copia o nome da variável (limitado a 31 caracteres)
    novo->nome[31] = '\0';                // Garante terminação nula da string
    novo->esquerda = novo->direita = NULL;  // Inicializa filhos como nulos
    return novo;
}

// Função para criar um nó de operador na AST
NoAST *criarNoOp(char operador, NoAST *esq, NoAST *dir) {
    NoAST *novo = malloc(sizeof(NoAST));  // Aloca memória para o nó
    novo->tipo = AST_OP;                  // Define tipo como operador
    novo->operador = operador;            // Armazena o tipo de operador (+, -, *, /)
    novo->esquerda = esq;                 // Conecta ao filho esquerdo
    novo->direita = dir;                  // Conecta ao filho direito
    return novo;
}

// Função para imprimir AST em formato de expressão (pré-ordem)
void imprimirAST(const NoAST *raiz) {
    if (!raiz) return;  // Caso base: nó nulo
    switch (raiz->tipo) {
        case AST_NUM:
            printf("%d", raiz->valor);  // Imprime valor para nós numéricos
            break;
        case AST_ID:
            printf("%s", raiz->nome);   // Imprime nome para nós de identificador
            break;
        case AST_OP:
            printf("(");                // Abre parêntese para operação
            imprimirAST(raiz->esquerda);  // Imprime operando esquerdo
            printf(" %c ", raiz->operador);  // Imprime operador
            imprimirAST(raiz->direita);   // Imprime operando direito
            printf(")");                // Fecha parêntese
            break;
    }
}

// Função para impressão em ordem (in-order traversal) da AST
void imprimirASTEmOrdem(const NoAST *raiz) {
    if (!raiz) return;  // Caso base: nó nulo
    
    // Primeiro visita o filho esquerdo (recursão)
    if (raiz->esquerda) {
        imprimirASTEmOrdem(raiz->esquerda);
    }
    
    // Depois visita o nó atual (raiz)
    switch (raiz->tipo) {
        case AST_NUM:
            printf("%d ", raiz->valor);  // Imprime valor para nós numéricos
            break;
        case AST_ID:
            printf("%s ", raiz->nome);   // Imprime nome para nós de identificador
            break;
        case AST_OP:
            printf("%c ", raiz->operador);  // Imprime operador
            break;
    }
    
    // Por último visita o filho direito (recursão)
    if (raiz->direita) {
        imprimirASTEmOrdem(raiz->direita);
    }
}

// Função para liberar memória utilizada pela AST
void liberarAST(NoAST *raiz) {
    if (!raiz) return;  // Caso base: nó nulo
    liberarAST(raiz->esquerda);  // Libera filho esquerdo (pós-ordem)
    liberarAST(raiz->direita);   // Libera filho direito (pós-ordem)
    free(raiz);                  // Libera o nó atual
}