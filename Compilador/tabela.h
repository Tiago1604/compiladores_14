#ifndef TABELA_H
#define TABELA_H

// Enumeração dos possíveis tipos de símbolos na linguagem
typedef enum { TIPO_INT, TIPO_FLOAT, TIPO_FUNC} Tipo;

// Estrutura para armazenar informações sobre cada símbolo (variáveis e funções)
typedef struct simbolo {
    char nome[64];         // Nome do símbolo (variável ou função)
    Tipo tipo;             // Tipo do símbolo (int, float ou função)
    int escopo;            // Escopo onde o símbolo foi declarado (0=global, >0=local)
    int inicializada;      // Flag indicando se variável foi inicializada (1) ou não (0)
    struct simbolo *proximo; // Ponteiro para próximo símbolo na lista encadeada (hash)
    
} Simbolo;

// Função para inserir um novo símbolo na tabela
void inserirSimbolo(char *nome, Tipo tipo, int escopo);

// Função para buscar um símbolo na tabela pelo nome e escopo
Simbolo *buscarSimbolo(char *nome, int escopo);

// Função para imprimir todos os símbolos da tabela (para depuração)
void imprimirTabela();

// Função para incrementar o nível de escopo (ao entrar em blocos)
void abrir_escopo();

// Função para decrementar o nível de escopo (ao sair de blocos)
void fechar_escopo();

#endif