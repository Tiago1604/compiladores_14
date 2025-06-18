#ifndef AST_H
#define AST_H

/*
 * Tipos de nós da árvore sintática
 */
enum NodeType {
    NODE_STMT_LIST,
    NODE_FUNCTION_DEF,
    NODE_IF,
    NODE_FOR,
    NODE_PRINT,
    NODE_ASSIGNMENT,
    NODE_COMPARISON,
    NODE_ARITHMETIC,
    NODE_NUMBER,
    NODE_FLOAT,
    NODE_IDENTIFIER
};

/*
 * Tipos de operações
 */
enum OpType {
    OP_PLUS,
    OP_MINUS,
    OP_TIMES,
    OP_DIVIDE,
    OP_EQ,
    OP_NEQ,
    OP_LT,
    OP_GT,
    OP_LTE,
    OP_GTE
};

/*
 * Estrutura de um nó da árvore sintática
 */
typedef struct ASTNode {
    enum NodeType type;
    enum OpType op;
    union {
        int ival;
        float fval;
        char *sval;
    } value;
    struct ASTNode *left;
    struct ASTNode *middle;  // Para if-else e para loops
    struct ASTNode *right;
} ASTNode;

// Nó global da raiz
extern ASTNode *root;

// Funções de criação de nós
ASTNode *criar_no(enum NodeType type, ASTNode *left, ASTNode *right);
ASTNode *criar_function_def(char *name, ASTNode *params, ASTNode *body);
ASTNode *criar_if(ASTNode *condition, ASTNode *if_body, ASTNode *else_body);
ASTNode *criar_for(char *var, ASTNode *range, ASTNode *body);
ASTNode *criar_print(ASTNode *expr);
ASTNode *criar_assignment(char *var, ASTNode *expr);
ASTNode *criar_comparison(enum OpType op, ASTNode *left, ASTNode *right);
ASTNode *criar_arithmetic(enum OpType op, ASTNode *left, ASTNode *right);
ASTNode *criar_number(int value);
ASTNode *criar_float(float value);
ASTNode *criar_identifier(char *name);

// Função de geração de código
void gerar_codigo_c(ASTNode *no, FILE *saida);
void gerar_codigo_c_interno(ASTNode *no, FILE *saida, int identacao);


// Função para imprimir a AST
void imprimirAST(ASTNode *no, int nivel);

#endif 