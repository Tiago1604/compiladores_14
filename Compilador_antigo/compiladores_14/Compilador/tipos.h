#ifndef TIPOS_H
#define TIPOS_H

// Enumeração ampliada dos tipos de nós AST
typedef enum {
    // Tipos existentes
    AST_NUM, AST_ID, AST_OP,
    
    // Novos tipos para comandos
    AST_ATRIB,     // Comando de atribuição
    AST_DECL,      // Declaração de variável
    AST_PRINT,     // Comando de impressão
    
    // Estruturas de controle
    AST_IF,        // Comando if
    AST_IF_ELSE,   // Comando if-else
    AST_BLOCO,     // Bloco de código
    AST_WHILE,     // Laço while
    AST_FOR,       // Laço for
    
    // Expressões
    AST_COMP,      // Operação de comparação
    
    // Estruturais
    AST_LISTA_CMD, // Lista de comandos
    AST_PROGRAMA   // Programa completo
} ASTTipo;

// Tipos de operadores de comparação
typedef enum {
    COMP_IGUAL,     // ==
    COMP_DIFERENTE, // !=
    COMP_MAIOR,     // >
    COMP_MENOR,     // <
    COMP_MAIOR_IGUAL, // >=
    COMP_MENOR_IGUAL  // <=
} TipoComparacao;

// Estrutura para nó da AST com campos adicionais
typedef struct noAST {
    ASTTipo tipo;      // Tipo do nó
    
    // Para AST_NUM
    int valor;         // Valor para nós numéricos
    
    // Para AST_ID
    char nome[32];     // Nome da variável para nós identificadores
    
    // Para AST_OP
    char operador;     // Operador (+, -, *, /)
    
    // Para AST_COMP
    TipoComparacao op_comp;  // Tipo de operador de comparação
    
    // Para AST_DECL
    char tipo_var[16]; // Tipo da variável (int, float, etc.)
    
    // Nós filhos
    struct noAST *esquerda;  // Filho esquerdo
    struct noAST *direita;   // Filho direito
    
    // Para listas de comandos e blocos
    struct noAST *proximo;   // Próximo comando em uma lista
} NoAST;

#endif