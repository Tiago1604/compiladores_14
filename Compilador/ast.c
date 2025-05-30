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
    novo->proximo = NULL;                 // Inicializa próximo como nulo
    return novo;
}

// Função para criar um nó de identificador (variável) na AST
NoAST *criarNoId(const char *nome) {
    NoAST *novo = malloc(sizeof(NoAST));  // Aloca memória para o nó
    novo->tipo = AST_ID;                  // Define tipo como identificador
    strncpy(novo->nome, nome, 31);        // Copia o nome da variável (limitado a 31 caracteres)
    novo->nome[31] = '\0';                // Garante terminação nula da string
    novo->esquerda = novo->direita = NULL;  // Inicializa filhos como nulos
    novo->proximo = NULL;                 // Inicializa próximo como nulo
    return novo;
}

// Função para criar um nó de operador na AST
NoAST *criarNoOp(char operador, NoAST *esq, NoAST *dir) {
    NoAST *novo = malloc(sizeof(NoAST));  // Aloca memória para o nó
    novo->tipo = AST_OP;                  // Define tipo como operador
    novo->operador = operador;            // Armazena o tipo de operador (+, -, *, /)
    novo->esquerda = esq;                 // Conecta ao filho esquerdo
    novo->direita = dir;                  // Conecta ao filho direito
    novo->proximo = NULL;                 // Inicializa próximo como nulo
    return novo;
}

// Função para criar um nó de declaração de variável
NoAST *criarNoDecl(const char *tipo, const char *nome) {
    NoAST *novo = malloc(sizeof(NoAST));  // Aloca memória para o nó
    novo->tipo = AST_DECL;                // Define tipo como declaração
    strncpy(novo->nome, nome, 31);        // Copia o nome da variável
    novo->nome[31] = '\0';                // Garante terminação nula da string
    strncpy(novo->tipo_var, tipo, 15);    // Copia o tipo da variável
    novo->tipo_var[15] = '\0';            // Garante terminação nula da string
    novo->esquerda = novo->direita = NULL;  // Inicializa filhos como nulos
    novo->proximo = NULL;                 // Inicializa próximo como nulo
    return novo;
}

// Função para criar um nó de atribuição
NoAST *criarNoAtrib(NoAST *id, NoAST *expr) {
    NoAST *novo = malloc(sizeof(NoAST));  // Aloca memória para o nó
    novo->tipo = AST_ATRIB;               // Define tipo como atribuição
    novo->esquerda = id;                  // Variável sendo atribuída (lado esquerdo)
    novo->direita = expr;                 // Expressão sendo atribuída (lado direito)
    novo->proximo = NULL;                 // Inicializa próximo como nulo
    return novo;
}

// Função para criar um nó de impressão
NoAST *criarNoPrint(NoAST *expr) {
    NoAST *novo = malloc(sizeof(NoAST));  // Aloca memória para o nó
    novo->tipo = AST_PRINT;               // Define tipo como impressão
    novo->esquerda = expr;                // Expressão a ser impressa
    novo->direita = NULL;                 // Não tem filho direito
    novo->proximo = NULL;                 // Inicializa próximo como nulo
    return novo;
}

// Função para criar um nó if
NoAST *criarNoIf(NoAST *condicao, NoAST *bloco) {
    NoAST *novo = malloc(sizeof(NoAST));  // Aloca memória para o nó
    novo->tipo = AST_IF;                  // Define tipo como if
    novo->esquerda = condicao;            // Condição do if
    novo->direita = bloco;                // Bloco a ser executado se verdadeiro
    novo->proximo = NULL;                 // Inicializa próximo como nulo
    return novo;
}

// Função para criar um nó if-else
NoAST *criarNoIfElse(NoAST *condicao, NoAST *bloco_if, NoAST *bloco_else) {
    NoAST *novo = malloc(sizeof(NoAST));  // Aloca memória para o nó
    novo->tipo = AST_IF_ELSE;             // Define tipo como if-else
    novo->esquerda = condicao;            // Condição do if
    
    // Cria uma estrutura para armazenar os dois blocos
    NoAST *blocos = malloc(sizeof(NoAST));
    blocos->esquerda = bloco_if;          // Bloco a ser executado se verdadeiro
    blocos->direita = bloco_else;         // Bloco a ser executado se falso
    
    novo->direita = blocos;               // Conecta os blocos ao nó if-else
    novo->proximo = NULL;                 // Inicializa próximo como nulo
    return novo;
}

// Função para criar um nó while
NoAST *criarNoWhile(NoAST *condicao, NoAST *bloco) {
    NoAST *novo = malloc(sizeof(NoAST));  // Aloca memória para o nó
    novo->tipo = AST_WHILE;               // Define tipo como while
    novo->esquerda = condicao;            // Condição do laço
    novo->direita = bloco;                // Bloco a ser executado enquanto condição for verdadeira
    novo->proximo = NULL;                 // Inicializa próximo como nulo
    return novo;
}

// Função para criar um nó for
NoAST *criarNoFor(NoAST *init, NoAST *cond, NoAST *incr, NoAST *bloco) {
    NoAST *novo = malloc(sizeof(NoAST));  // Aloca memória para o nó
    novo->tipo = AST_FOR;                 // Define tipo como for
    
    // Cria uma estrutura para armazenar os componentes do for
    NoAST *componentes = malloc(sizeof(NoAST));
    componentes->esquerda = init;         // Inicialização
    
    NoAST *cond_incr = malloc(sizeof(NoAST));
    cond_incr->esquerda = cond;          // Condição
    cond_incr->direita = incr;           // Incremento
    
    componentes->direita = cond_incr;    // Conecta condição e incremento à inicialização
    
    novo->esquerda = componentes;        // Conecta componentes ao nó for
    novo->direita = bloco;               // Bloco a ser executado
    novo->proximo = NULL;                // Inicializa próximo como nulo
    return novo;
}

// Função para criar um nó de comparação
NoAST *criarNoComp(TipoComparacao op, NoAST *esq, NoAST *dir) {
    NoAST *novo = malloc(sizeof(NoAST));  // Aloca memória para o nó
    novo->tipo = AST_COMP;                // Define tipo como comparação
    novo->op_comp = op;                   // Armazena o operador de comparação
    novo->esquerda = esq;                 // Operando esquerdo
    novo->direita = dir;                  // Operando direito
    novo->proximo = NULL;                 // Inicializa próximo como nulo
    return novo;
}

// Função para criar um nó de bloco de código
NoAST *criarNoBloco(NoAST *lista_cmd) {
    NoAST *novo = malloc(sizeof(NoAST));  // Aloca memória para o nó
    novo->tipo = AST_BLOCO;               // Define tipo como bloco
    novo->esquerda = lista_cmd;           // Lista de comandos no bloco
    novo->direita = NULL;                 // Não tem filho direito
    novo->proximo = NULL;                 // Inicializa próximo como nulo
    return novo;
}

// Função para criar um nó de lista de comandos
NoAST *criarNoListaCmd(NoAST *cmd, NoAST *proximo) {
    NoAST *novo = malloc(sizeof(NoAST));  // Aloca memória para o nó
    novo->tipo = AST_LISTA_CMD;           // Define tipo como lista de comandos
    novo->esquerda = cmd;                 // Comando atual
    novo->direita = NULL;                 // Não tem filho direito
    novo->proximo = proximo;              // Próximo comando na lista
    return novo;
}

// Função para criar um nó de programa
NoAST *criarNoPrograma(NoAST *lista_cmd) {
    NoAST *novo = malloc(sizeof(NoAST));  // Aloca memória para o nó
    novo->tipo = AST_PROGRAMA;            // Define tipo como programa
    novo->esquerda = lista_cmd;           // Lista de comandos do programa
    novo->direita = NULL;                 // Não tem filho direito
    novo->proximo = NULL;                 // Inicializa próximo como nulo
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
            
        case AST_DECL:
            printf("%s %s", raiz->tipo_var, raiz->nome);  // Imprime declaração
            break;
            
        case AST_ATRIB:
            imprimirAST(raiz->esquerda);  // Imprime variável
            printf(" = ");
            imprimirAST(raiz->direita);   // Imprime expressão
            break;
            
        case AST_PRINT:
            printf("print(");
            imprimirAST(raiz->esquerda);  // Imprime expressão a ser impressa
            printf(")");
            break;
            
        case AST_COMP:
            printf("(");
            imprimirAST(raiz->esquerda);  // Imprime operando esquerdo
            
            // Imprime operador de comparação
            switch(raiz->op_comp) {
                case COMP_IGUAL: printf(" == "); break;
                case COMP_DIFERENTE: printf(" != "); break;
                case COMP_MAIOR: printf(" > "); break;
                case COMP_MENOR: printf(" < "); break;
                case COMP_MAIOR_IGUAL: printf(" >= "); break;
                case COMP_MENOR_IGUAL: printf(" <= "); break;
            }
            
            imprimirAST(raiz->direita);   // Imprime operando direito
            printf(")");
            break;
            
        case AST_IF:
            printf("if (");
            imprimirAST(raiz->esquerda);  // Imprime condição
            printf(") {\n");
            imprimirAST(raiz->direita);   // Imprime bloco
            printf("\n}");
            break;
            
        case AST_IF_ELSE:
            printf("if (");
            imprimirAST(raiz->esquerda);  // Imprime condição
            printf(") {\n");
            imprimirAST(raiz->direita->esquerda);  // Imprime bloco if
            printf("\n} else {\n");
            imprimirAST(raiz->direita->direita);   // Imprime bloco else
            printf("\n}");
            break;
            
        case AST_WHILE:
            printf("while (");
            imprimirAST(raiz->esquerda);  // Imprime condição
            printf(") {\n");
            imprimirAST(raiz->direita);   // Imprime bloco
            printf("\n}");
            break;
            
        case AST_FOR:
            printf("for (");
            imprimirAST(raiz->esquerda->esquerda);  // Imprime inicialização
            printf("; ");
            imprimirAST(raiz->esquerda->direita->esquerda);  // Imprime condição
            printf("; ");
            imprimirAST(raiz->esquerda->direita->direita);   // Imprime incremento
            printf(") {\n");
            imprimirAST(raiz->direita);   // Imprime bloco
            printf("\n}");
            break;
            
        case AST_BLOCO:
            printf("{\n");
            imprimirAST(raiz->esquerda);  // Imprime comandos do bloco
            printf("\n}");
            break;
            
        case AST_LISTA_CMD:
            imprimirAST(raiz->esquerda);  // Imprime comando atual
            if (raiz->proximo) {
                printf(";\n");
                imprimirAST(raiz->proximo);  // Imprime próximo comando
            }
            break;
            
        case AST_PROGRAMA:
            printf("Programa:\n");
            imprimirAST(raiz->esquerda);  // Imprime comandos do programa
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
        case AST_DECL:
            printf("decl:%s:%s ", raiz->tipo_var, raiz->nome);
            break;
        case AST_ATRIB:
            printf("= ");
            break;
        case AST_PRINT:
            printf("print ");
            break;
        case AST_COMP:
            switch(raiz->op_comp) {
                case COMP_IGUAL: printf("== "); break;
                case COMP_DIFERENTE: printf("!= "); break;
                case COMP_MAIOR: printf("> "); break;
                case COMP_MENOR: printf("< "); break;
                case COMP_MAIOR_IGUAL: printf(">= "); break;
                case COMP_MENOR_IGUAL: printf("<= "); break;
            }
            break;
        case AST_IF:
            printf("if ");
            break;
        case AST_IF_ELSE:
            printf("if-else ");
            break;
        case AST_WHILE:
            printf("while ");
            break;
        case AST_FOR:
            printf("for ");
            break;
        case AST_BLOCO:
            printf("bloco ");
            break;
        case AST_LISTA_CMD:
            printf("cmd ");
            break;
        case AST_PROGRAMA:
            printf("programa ");
            break;
    }
    
    // Por último visita o filho direito (recursão)
    if (raiz->direita) {
        imprimirASTEmOrdem(raiz->direita);
    }
    
    // Se tiver próximo na lista, também o imprime
    if (raiz->proximo) {
        imprimirASTEmOrdem(raiz->proximo);
    }
}

// Função para imprimir AST detalhada com indentação
void imprimirASTDetalhada(const NoAST *raiz, int nivel) {
    if (!raiz) return;
    
    // Imprime recuo baseado no nível de profundidade na árvore
    for (int i = 0; i < nivel; i++) {
        printf("  ");
    }
    
    // Imprime informações do nó atual
    switch (raiz->tipo) {
        case AST_NUM:
            printf("Número: %d\n", raiz->valor);
            break;
            
        case AST_ID:
            printf("Identificador: %s\n", raiz->nome);
            break;
            
        case AST_OP:
            printf("Operador: %c\n", raiz->operador);
            break;
            
        case AST_DECL:
            printf("Declaração: %s %s\n", raiz->tipo_var, raiz->nome);
            break;
            
        case AST_ATRIB:
            printf("Atribuição:\n");
            break;
            
        case AST_PRINT:
            printf("Comando Print:\n");
            break;
            
        case AST_COMP:
            printf("Comparação: ");
            switch(raiz->op_comp) {
                case COMP_IGUAL: printf("==\n"); break;
                case COMP_DIFERENTE: printf("!=\n"); break;
                case COMP_MAIOR: printf(">\n"); break;
                case COMP_MENOR: printf("<\n"); break;
                case COMP_MAIOR_IGUAL: printf(">=\n"); break;
                case COMP_MENOR_IGUAL: printf("<=\n"); break;
            }
            break;
            
        case AST_IF:
            printf("Comando If:\n");
            break;
            
        case AST_IF_ELSE:
            printf("Comando If-Else:\n");
            break;
            
        case AST_WHILE:
            printf("Laço While:\n");
            break;
            
        case AST_FOR:
            printf("Laço For:\n");
            break;
            
        case AST_BLOCO:
            printf("Bloco de Código:\n");
            break;
            
        case AST_LISTA_CMD:
            printf("Lista de Comandos:\n");
            break;
            
        case AST_PROGRAMA:
            printf("PROGRAMA:\n");
            break;
    }
    
    // Imprime filhos com recuo aumentado
    if (raiz->esquerda) {
        for (int i = 0; i < nivel + 1; i++) {
            printf("  ");
        }
        printf("Esquerda -> ");
        imprimirASTDetalhada(raiz->esquerda, nivel + 1);
    }
    
    if (raiz->direita) {
        for (int i = 0; i < nivel + 1; i++) {
            printf("  ");
        }
        printf("Direita -> ");
        imprimirASTDetalhada(raiz->direita, nivel + 1);
    }
    
    // Se tiver próximo na lista, também o imprime
    if (raiz->proximo) {
        for (int i = 0; i < nivel; i++) {
            printf("  ");
        }
        printf("Próximo -> ");
        imprimirASTDetalhada(raiz->proximo, nivel);
    }
}

// Função para liberar memória utilizada pela AST
void liberarAST(NoAST *raiz) {
    if (!raiz) return;  // Caso base: nó nulo
    
    // Libera recursivamente todos os nós
    liberarAST(raiz->esquerda);  // Libera filho esquerdo (pós-ordem)
    liberarAST(raiz->direita);   // Libera filho direito (pós-ordem)
    liberarAST(raiz->proximo);   // Libera próximo nó da lista, se existir
    
    free(raiz);  // Libera o nó atual
}