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

// Função para avaliar expressões constantes
int avaliarExpressaoConstante(NoAST *raiz) {
    if (!raiz) return 0;
    
    switch (raiz->tipo) {
        case AST_NUM:
            return raiz->valor;
        case AST_ID:
            return 0; // Não podemos avaliar variáveis em tempo de compilação
        case AST_OP: {
            int esq = avaliarExpressaoConstante(raiz->esquerda);
            int dir = avaliarExpressaoConstante(raiz->direita);
            
            switch (raiz->operador) {
                case '+': return esq + dir;
                case '-': return esq - dir;
                case '*': return esq * dir;
                case '/': return dir != 0 ? esq / dir : 0;
                default: return 0;
            }
        }
        default:
            return 0;
    }
}

// Função para otimizar a AST usando constant folding
NoAST *otimizarAST(NoAST *raiz) {
    if (!raiz) return NULL;
    
    // Otimiza os filhos primeiro
    raiz->esquerda = otimizarAST(raiz->esquerda);
    raiz->direita = otimizarAST(raiz->direita);
    
    // Se for um operador e ambos os filhos forem constantes
    if (raiz->tipo == AST_OP && 
        raiz->esquerda && raiz->esquerda->tipo == AST_NUM &&
        raiz->direita && raiz->direita->tipo == AST_NUM) {
        
        int resultado = avaliarExpressaoConstante(raiz);
        NoAST *novo = criarNoNum(resultado);
        liberarAST(raiz);
        return novo;
    }
    
    // Otimização: x + 0 = x
    if (raiz->tipo == AST_OP && raiz->operador == '+' &&
        raiz->direita && raiz->direita->tipo == AST_NUM && raiz->direita->valor == 0) {
        NoAST *novo = raiz->esquerda;
        raiz->esquerda = NULL;
        liberarAST(raiz);
        return novo;
    }
    
    // Otimização: x * 1 = x
    if (raiz->tipo == AST_OP && raiz->operador == '*' &&
        raiz->direita && raiz->direita->tipo == AST_NUM && raiz->direita->valor == 1) {
        NoAST *novo = raiz->esquerda;
        raiz->esquerda = NULL;
        liberarAST(raiz);
        return novo;
    }
    
    // Otimização: x * 0 = 0
    if (raiz->tipo == AST_OP && raiz->operador == '*' &&
        ((raiz->esquerda && raiz->esquerda->tipo == AST_NUM && raiz->esquerda->valor == 0) ||
         (raiz->direita && raiz->direita->tipo == AST_NUM && raiz->direita->valor == 0))) {
        NoAST *novo = criarNoNum(0);
        liberarAST(raiz);
        return novo;
    }
    
    return raiz;
}

// Função para gerar código intermediário (bitcode)
void gerarBitcode(NoAST *raiz) {
    if (!raiz) return;
    
    switch (raiz->tipo) {
        case AST_NUM:
            printf("LOAD_CONST %d\n", raiz->valor);
            break;
        case AST_ID:
            printf("LOAD_NAME %s\n", raiz->nome);
            break;
        case AST_OP:
            // Otimização: se for uma operação com constantes, carrega o resultado direto
            if (raiz->esquerda && raiz->esquerda->tipo == AST_NUM &&
                raiz->direita && raiz->direita->tipo == AST_NUM) {
                int resultado = avaliarExpressaoConstante(raiz);
                printf("LOAD_CONST %d\n", resultado);
            } else {
                gerarBitcode(raiz->esquerda);
                gerarBitcode(raiz->direita);
                switch (raiz->operador) {
                    case '+': printf("ADD\n"); break;
                    case '-': printf("SUB\n"); break;
                    case '*': printf("MUL\n"); break;
                    case '/': printf("DIV\n"); break;
                }
            }
            break;
    }
}

// Função para gerar código C a partir da AST
void gerarCodigoC(NoAST *raiz) {
    if (!raiz) return;
    
    switch (raiz->tipo) {
        case AST_NUM:
            printf("%d", raiz->valor);
            break;
        case AST_ID:
            printf("%s", raiz->nome);
            break;
        case AST_OP:
            // Otimização: se for uma operação com constantes, imprime o resultado direto
            if (raiz->esquerda && raiz->esquerda->tipo == AST_NUM &&
                raiz->direita && raiz->direita->tipo == AST_NUM) {
                int resultado = avaliarExpressaoConstante(raiz);
                printf("%d", resultado);
            } else {
                printf("(");
                gerarCodigoC(raiz->esquerda);
                printf(" %c ", raiz->operador);
                gerarCodigoC(raiz->direita);
                printf(")");
            }
            break;
    }
}