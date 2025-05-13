#include "tabela.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Simbolo *tabela_simbolos[TAMANHO_TABELA];

// Inicializa a tabela de símbolos
void inicializar_tabela() {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabela_simbolos[i] = NULL;
    }
}

// Função de hash simples
unsigned int hash(char *str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash << 5) + *str++;
    }
    return hash % TAMANHO_TABELA;
}

// Verifica se um identificador já existe na tabela
int verificar_existencia(char *nome) {
    unsigned int h = hash(nome);
    Simbolo *s = tabela_simbolos[h];
    while (s) {
        if (strcmp(s->nome, nome) == 0) {
            return 1; // Encontrado
        }
        s = s->proximo;
    }
    return 0; // Não encontrado
}

// Insere um identificador na tabela de símbolos
int inserir_identificador(char *nome, int tipo, int escopo) {
    if (verificar_existencia(nome)) {
        printf("Erro semântico: Identificador '%s' já declarado\n", nome);
        return 0; // Falha - identificador já existe
    }
    
    unsigned int h = hash(nome);
    Simbolo *novo_simbolo = (Simbolo*) malloc(sizeof(Simbolo));
    if (!novo_simbolo) {
        printf("Erro: Falha na alocação de memória\n");
        return 0;
    }
    
    novo_simbolo->nome = strdup(nome);
    novo_simbolo->tipo = tipo;
    novo_simbolo->escopo = escopo;
    novo_simbolo->proximo = tabela_simbolos[h];
    tabela_simbolos[h] = novo_simbolo;
    return 1;  // Sucesso
}

// Busca o tipo de um identificador na tabela
int buscar_tipo(char *nome) {
    unsigned int h = hash(nome);
    Simbolo *s = tabela_simbolos[h];
    while (s) {
        if (strcmp(s->nome, nome) == 0) {
            return s->tipo;
        }
        s = s->proximo;
    }
    return -1;  // Identificador não encontrado
}

// Libera a memória alocada para a tabela de símbolos
void liberar_tabela() {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        Simbolo *atual = tabela_simbolos[i];
        while (atual) {
            Simbolo *temp = atual;
            atual = atual->proximo;
            free(temp->nome);
            free(temp);
        }
        tabela_simbolos[i] = NULL;
    }
}