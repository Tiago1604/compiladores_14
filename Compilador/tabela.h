#ifndef TABELA_H
#define TABELA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Enumeração para categorizar o símbolo
typedef enum {
    SIM_VARIAVEL,  // Variável comum
    SIM_CONSTANTE, // Constante
    SIM_FUNCAO,    // Função
    SIM_PARAMETRO  // Parâmetro de função
} SimboloCategoria;

typedef struct simbolo {
    char nome[32];          // Nome da variável
    char tipo[16];          // Tipo da variável (int, float, etc.)
    SimboloCategoria categoria; // Categoria do símbolo
    int linha;              // Linha onde o símbolo foi declarado
    int inicializado;       // Flag que indica se a variável foi inicializada
    int utilizado;          // Flag que indica se a variável foi utilizada
    union {
        int valorInt;       // Valor armazenado (para constantes)
        float valorFloat;   // Valor armazenado (para constantes)
        char valorChar;     // Valor armazenado (para constantes)
    } valor;
    struct simbolo *prox;   // Próximo símbolo na lista encadeada
} Simbolo;

// Funções básicas
void inserirSimbolo(const char *nome, const char *tipo);  // Insere símbolo na tabela
Simbolo *buscarSimbolo(const char *nome);                 // Busca símbolo pelo nome
void imprimirTabela();                                    // Imprime toda a tabela
void liberarTabela();                                     // Libera memória da tabela

// Novas funções
void inserirSimboloCompleto(const char *nome, const char *tipo, SimboloCategoria categoria, 
                          int linha);  // Insere símbolo com informações completas (sem escopo)
void marcarInicializado(const char *nome);                  // Marca que uma variável foi inicializada
void marcarUtilizado(const char *nome);                     // Marca que uma variável foi utilizada
void atribuirValorInt(const char *nome, int valor);         // Atribui valor inteiro a uma variável
void verificarVariaveisNaoUtilizadas();                     // Verifica variáveis declaradas mas não utilizadas

// Funções para acesso a valores
int obterValorInt(const char *nome, int *valor);  // Obtém o valor inteiro de uma variável
int estaInicializada(const char *nome);          // Verifica se uma variável está inicializada

#endif