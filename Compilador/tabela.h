#ifndef TABELA_H
#define TABELA_H

#include "tipos.h"

#define TAMANHO_TABELA 211

typedef struct Simbolo {
    char *nome;             // Nome da variável ou função
    int tipo;               // Tipo do identificador (e.g., TIPO_INT, TIPO_FLOAT)
    int escopo;             // Escopo: global ou local
    struct Simbolo *proximo; // Para resolver colisões (lista encadeada)
} Simbolo;

extern Simbolo *tabela_simbolos[TAMANHO_TABELA];


void inicializar_tabela();
int inserir_identificador(char *nome, int tipo, int escopo);
int buscar_tipo(char *nome);
int verificar_existencia(char *nome);
void liberar_tabela();

#endif 