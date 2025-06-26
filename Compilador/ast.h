#ifndef AST_H
#define AST_H

struct ListaVar;

/*
 * Tipos de nós da árvore sintática
 */
enum TipoNo {
    NO_LISTA_COMANDOS,
    NO_DEF_FUNCAO,
    NO_IF,
    NO_FOR,
    NO_WHILE,
    NO_PRINT,
    NO_ATRIBUICAO,
    NO_COMPARACAO,
    NO_ARITMETICO,
    NO_NUMERO,
    NO_FLUTUANTE,
    NO_IDENTIFICADOR,
    NO_CHAMADA_FUNCAO,
};

/*
 * Tipos de operações
 */
enum TipoOp {
    OP_MAIS,
    OP_MENOS,
    OP_VEZES,
    OP_DIVIDE,
    OP_IGUAL,
    OP_DIFERENTE,
    OP_MENOR,
    OP_MAIOR,
    OP_MENOR_IGUAL,
    OP_MAIOR_IGUAL
};

// Estrutura de um nó da árvore sintática
typedef struct No {
    enum TipoNo tipo;
    enum TipoOp op;
    union {
        int ival;
        float fval;
        char *sval;
    } valor;
    struct No *esquerda;
    struct No *meio;  // Para if-else e para loops
    struct No *direita;
} No;

// Nó global da raiz
extern No *raiz;

// Funções de criação de nós
No *criar_no(enum TipoNo tipo, No *esquerda, No *direita);
No *criar_funcao(char *nome, No *params, No *corpo);
No *criar_if(No *condicao, No *corpo_if, No *corpo_else);
No *criar_for(char *var, No *alcance, No *corpo);
No *criar_while(No *condicao, No *corpo);
No *criar_print(No *expr);
No *criar_atribuicao(char *var, No *expr);
No *criar_comparacao(enum TipoOp op, No *esquerda, No *direita);
No *criar_aritmetico(enum TipoOp op, No *esquerda, No *direita);
No *criar_numero(int valor);
No *criar_flutuante(float valor);
No *criar_identificador(char *nome);
No *criar_chamada_funcao(char *nome, No *args);

// Função de geração de código
void gerar_codigo_c(No *no, FILE *saida);
void gerar_codigo_c_interno(No *no, FILE *saida, int identacao);
void coletar_vars(No *no, struct ListaVar **vars);
void extrair_comandos_globais(No *no, No **comandos_globais, No **definicoes_funcoes);
void extrair_corpo_funcao(No *no, No **corpo);
void extrair_comandos_globais_do_corpo(No *no, No **comandos_globais);
void extrair_funcoes_aninhadas(No *no, No **comandos_globais, No **definicoes_funcoes);

// Função para imprimir a AST
void imprimirAST(No *no, int nivel);

#endif 