#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela.h"

// Define o tamanho da tabela hash para armazenar os símbolos
#define TAM 211

// Referência ao escopo atual definido no parser
extern int escopo_atual;    // capturar o escopo global declarado no parser.c

/* Incrementa o escopo atual */
void abrir_escopo() {
    escopo_atual++;  // Aumenta o nível de escopo quando entramos em um bloco novo
}

/* Decrementa o escopo atual */
void fechar_escopo() {
    escopo_atual--;  // Diminui o nível de escopo quando saímos de um bloco
}

// Array de ponteiros para listas encadeadas de símbolos (tabela hash)
static Simbolo *tabela[TAM] = {NULL};

// Função de hash para distribuir os símbolos na tabela
static unsigned hash(char *s) {
    unsigned h = 0;
    while (*s) h = (h << 4) + *s++;  // Desloca bits e soma valor do caractere
    return h % TAM;  // Garante que o índice está dentro do tamanho da tabela
}

// Insere um novo símbolo na tabela de símbolos
void inserirSimbolo(char *nome, Tipo tipo, int escopo) {
    unsigned i = hash(nome);  // Calcula o índice hash para o nome
    // Evita duplicatas no mesmo escopo
    if (buscarSimbolo(nome, escopo)) return;
    
    // Aloca e inicializa um novo símbolo
    Simbolo *s = malloc(sizeof(Simbolo));
    strncpy(s->nome, nome, sizeof(s->nome));  // Copia o nome com segurança
    s->nome[sizeof(s->nome)-1] = '\0';  // Garante terminação da string
    s->tipo = tipo;  // Define o tipo (int, float, função)
    s->escopo = escopo;  // Define o escopo onde o símbolo foi declarado
    s->inicializada = 0;  // Marca como não inicializada inicialmente
    
    // Insere no início da lista encadeada (colisões são resolvidas por encadeamento)
    s->proximo = tabela[i];
    tabela[i] = s;
}

// Busca um símbolo na tabela pelo nome, verificando do escopo atual até o global
Simbolo *buscarSimbolo(char *nome, int escopo) {
    unsigned i = hash(nome);  // Calcula o índice hash para o nome
    // Procura do escopo atual até o global (escopo 0)
    for (; escopo >= 0; escopo--) {
        // Verifica cada símbolo na lista encadeada neste índice
        for (Simbolo *s = tabela[i]; s; s = s->proximo) {
            // Retorna o primeiro símbolo que corresponda ao nome e escopo
            if (strcmp(s->nome, nome) == 0 && s->escopo == escopo)
                return s;
        }
    }
    return NULL;  // Símbolo não encontrado em nenhum escopo
}

// Imprime todos os símbolos da tabela, organizados por escopo
void imprimirTabela() {
    // Primeiro, encontrar o maior escopo
    int max_escopo = -1;
    for (int i = 0; i < TAM; i++) {
        for (Simbolo *s = tabela[i]; s; s = s->proximo) {
            if (s->escopo > max_escopo) max_escopo = s->escopo;
        }
    }

    // Imprime os símbolos agrupados por escopo, do global para os locais
    printf("\n=== Tabela de Símbolos ===\n");
    for (int e = 0; e <= max_escopo; e++) {
        if (e == 0) {
            printf("\nEscopo Global:\n");  // Escopo 0 é o global
        } else {
            printf("\nEscopo %d (local):\n", e);  // Escopos > 0 são locais
        }
        printf("------------------\n");
        
        // Verifica se encontrou algum símbolo neste escopo
        int encontrou = 0;
        for (int i = 0; i < TAM; i++) {
            for (Simbolo *s = tabela[i]; s; s = s->proximo) {
                if (s->escopo == e) {
                    encontrou = 1;
                    // Converte o tipo numérico para string para melhor visualização
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
        // Se não encontrou símbolos neste escopo, mostra como vazio
        if (!encontrou) {
            printf("  (vazio)\n");
        }
    }
    printf("\n");
}