#include "tabela.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Simbolo *tabela = NULL;

void inserirSimbolo(const char *nome, const char *tipo) {
    Simbolo *s = tabela;
    while (s) {
        if (strcmp(s->nome, nome) == 0)
            return; // Já existe
        s = s->prox;
    }
    Simbolo *novo = malloc(sizeof(Simbolo));
    strncpy(novo->nome, nome, 31);
    novo->nome[31] = '\0';
    strncpy(novo->tipo, tipo, 15);
    novo->tipo[15] = '\0';
    novo->prox = tabela;
    tabela = novo;
}

Simbolo *buscarSimbolo(const char *nome) {
    for (Simbolo *s = tabela; s; s = s->prox)
        if (strcmp(s->nome, nome) == 0)
            return s;
    return NULL;
}

void imprimirTabela() {
    printf("\nTabela de Símbolos:\n");
    for (Simbolo *s = tabela; s; s = s->prox)
        printf("Nome: %s, Tipo: %s\n", s->nome, s->tipo);
}

void liberarTabela() {
    Simbolo *s = tabela;
    while (s) {
        Simbolo *prox = s->prox;
        free(s);
        s = prox;
    }
    tabela = NULL;
}