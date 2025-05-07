#include "tabela.h"
#include <stdlib.h>
#include <string.h>

Simbolo *tabela_simbolos[TAMANHO_TABELA];

// Função de hash simples
unsigned int hash(char *str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash << 5) + *str++;
    }
    return hash % TAMANHO_TABELA;
}

// Insere um identificador na tabela de símbolos
int inserir_identificador(char *nome, int tipo, int escopo) {
    unsigned int h = hash(nome);
    Simbolo *novo_simbolo = (Simbolo*) malloc(sizeof(Simbolo));
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
