#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "tipos.h"

// Cria um nó de constante inteira
AST* criar_no_constante_int(int valor) {
    AST *novo_no = (AST*) malloc(sizeof(AST));
    if (!novo_no) return NULL;
    novo_no->tipo = TIPO_INT;
    novo_no->categoria = CONSTANTE;
    novo_no->dado.valor_int = valor;
    return novo_no;
}

// Cria um nó de constante float
AST* criar_no_constante_float(float valor) {
    AST *novo_no = (AST*) malloc(sizeof(AST));
    if (!novo_no) return NULL;
    novo_no->tipo = TIPO_FLOAT;
    novo_no->categoria = CONSTANTE;
    novo_no->dado.valor_float = valor;
    return novo_no;
}

// Cria um nó de variável
AST* criar_no_variavel(char *nome) {
    AST *novo_no = (AST*) malloc(sizeof(AST));
    if (!novo_no) return NULL;
    novo_no->tipo = TIPO_NAO_DEFINIDO;  // Tipo será determinado pela tabela de símbolos
    novo_no->categoria = VARIAVEL;
    novo_no->dado.nome = strdup(nome);
    return novo_no;
}

// Cria um nó de operação binária
AST* criar_no_operacao(int operador, AST *esq, AST *dir) {
    AST *novo_no = (AST*) malloc(sizeof(AST));
    if (!novo_no) return NULL;
    novo_no->tipo = TIPO_NAO_DEFINIDO;  // Tipo será determinado após a análise semântica
    novo_no->categoria = OPERACAO;
    novo_no->dado.op.operador = operador;
    novo_no->dado.op.esq = esq;
    novo_no->dado.op.dir = dir;
    return novo_no;
}

// Função para liberar a memória da AST
void liberar_ast(AST *no) {
    if (no == NULL) return;
    
    if (no->categoria == OPERACAO) {
        liberar_ast(no->dado.op.esq);
        liberar_ast(no->dado.op.dir);
    } else if (no->categoria == VARIAVEL) {
        free(no->dado.nome);
    }
    
    free(no);
}