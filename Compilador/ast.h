#ifndef AST_H
#define AST_H

// Tipos de operacoes
#define OP_SOMA        1
#define OP_SUBTRACAO   2
#define OP_MULTIPLICACAO 3
#define OP_DIVISAO     4
#define OP_MAIOR       5
#define OP_MENOR       6
#define OP_MAIOR_IGUAL 7
#define OP_MENOR_IGUAL 8
#define OP_IGUAL       9
#define OP_DIFERENTE   10

typedef struct AST {
    int tipo;               // Tipo do nó 
    int categoria;          // Categoria do nó 
    union {
        int valor_int;      // Valor se for uma constante inteira
        float valor_float;  // Valor se for uma constante float
        char *nome;         // Nome da variável ou função
        struct {
            struct AST *esq; // Subárvore esquerda
            struct AST *dir; // Subárvore direita
            int operador;    // Tipo de operação
        } op;               // Operandos se for uma operação
    } dado;
} AST;


AST* criar_no_constante_int(int valor);
AST* criar_no_constante_float(float valor);
AST* criar_no_variavel(char *nome);
AST* criar_no_operacao(int operador, AST *esq, AST *dir);


void liberar_ast(AST *no);

#endif 