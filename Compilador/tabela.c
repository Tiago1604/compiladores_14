#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela.h"

#define TAM 211

extern int escopo_atual;    // capturar o escopo global declarado no parser.c

#define TAM 211

/* Incrementa o escopo atual */
void abrir_escopo() {
    escopo_atual++;
}

/* Decrementa o escopo atual */
void fechar_escopo() {
    escopo_atual--;
}

static Simbolo *tabela[TAM] = {NULL};

static unsigned hash(char *s) {
    unsigned h = 0;
    while (*s) h = (h << 4) + *s++;
    return h % TAM;
}

void inserirSimbolo(char *nome, Tipo tipo, int escopo) {
    unsigned i = hash(nome);
    // Evita duplicatas no mesmo escopo
    if (buscarSimbolo(nome, escopo)) return;
    Simbolo *s = malloc(sizeof(Simbolo));
    strncpy(s->nome, nome, sizeof(s->nome));
    s->nome[sizeof(s->nome)-1] = '\0';
    s->tipo = tipo;
    s->escopo = escopo;
    s->inicializada = 0;
    s->proximo = tabela[i];
    tabela[i] = s;
}

Simbolo *buscarSimbolo(char *nome, int escopo) {
    unsigned i = hash(nome);
    for (; escopo >= 0; escopo--) {
        for (Simbolo *s = tabela[i]; s; s = s->proximo) {
            if (strcmp(s->nome, nome) == 0 && s->escopo == escopo)
                return s;
        }
    }
    return NULL;
}

void imprimirTabela() {
    // Primeiro, encontrar o maior escopo
    int max_escopo = -1;
    for (int i = 0; i < TAM; i++) {
        for (Simbolo *s = tabela[i]; s; s = s->proximo) {
            if (s->escopo > max_escopo) max_escopo = s->escopo;
        }
    }

    // Imprimir por escopo
    printf("\n=== Tabela de Símbolos ===\n");
    for (int e = 0; e <= max_escopo; e++) {
        if (e == 0) {
            printf("\nEscopo Global:\n");
        } else {
            printf("\nEscopo %d (local):\n", e);
        }
        printf("------------------\n");
        
        int encontrou = 0;
        for (int i = 0; i < TAM; i++) {
            for (Simbolo *s = tabela[i]; s; s = s->proximo) {
                if (s->escopo == e) {
                    encontrou = 1;
                    const char *tipo_str;
                    switch(s->tipo) {
                        case TIPO_INT: tipo_str = "inteiro"; break;
                        case TIPO_FLOAT: tipo_str = "float"; break;
                        case TIPO_FUNC: tipo_str = "função"; break;
                        default: tipo_str = "desconhecido"; break;
                    }
                    printf("  %s: %s\n", s->nome, tipo_str);
                }
            }
        }
        if (!encontrou) {
            printf("  (vazio)\n");
        }
    }
    printf("\n");
}