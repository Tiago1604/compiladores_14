#ifndef TABELA_H
#define TABELA_H

typedef struct simbolo {
    char nome[32];
    char tipo[16];
    struct simbolo *prox;
} Simbolo;

void inserirSimbolo(const char *nome, const char *tipo);
Simbolo *buscarSimbolo(const char *nome);
void imprimirTabela();
void liberarTabela();

#endif