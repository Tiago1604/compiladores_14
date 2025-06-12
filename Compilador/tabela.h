#ifndef TABELA_H
#define TABELA_H

typedef enum { TIPO_INT, TIPO_FLOAT } Tipo;

typedef struct simbolo {
    char nome[64];
    Tipo tipo;
    int escopo;
    int inicializada;
    struct simbolo *proximo;
} Simbolo;

void inserirSimbolo(char *nome, Tipo tipo, int escopo);
Simbolo *buscarSimbolo(char *nome, int escopo);
void imprimirTabela();

#endif 