#ifndef TABELA_H
#define TABELA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipos.h"  // Adicionado para acesso aos tipos da AST

// Enumeração para categorizar o símbolo
typedef enum {
    SIM_VARIAVEL,  // Variável comum
    SIM_CONSTANTE, // Constante
    SIM_FUNCAO,    // Função
    SIM_PARAMETRO, // Parâmetro de função
    SIM_CLASSE     // Classe (para suporte futuro a orientação a objetos)
} SimboloCategoria;

// Enumeração para os tipos de dados do Python
typedef enum {
    TIPO_INT,      // int
    TIPO_FLOAT,    // float
    TIPO_STR,      // string
    TIPO_BOOL,     // boolean
    TIPO_NONE,     // None
    TIPO_LIST,     // list
    TIPO_DICT,     // dictionary
    TIPO_OBJECT,   // objeto genérico
    TIPO_FUNCTION, // função
    TIPO_UNKNOWN   // tipo desconhecido (para variáveis não inicializadas)
} TipoDado;

typedef struct simbolo {
    char nome[32];          // Nome da variável
    char tipo[16];          // Tipo da variável como string (int, float, etc.)
    TipoDado tipo_dado;     // Tipo da variável como enum (mais fácil para comparações)
    SimboloCategoria categoria; // Categoria do símbolo
    int linha;              // Linha onde o símbolo foi declarado
    int inicializado;       // Flag que indica se a variável foi inicializada
    int utilizado;          // Flag que indica se a variável foi utilizada
    union {
        int valorInt;       // Valor armazenado (para constantes int)
        float valorFloat;   // Valor armazenado (para constantes float)
        char valorChar;     // Valor armazenado (para constantes char)
        char valorStr[256]; // Valor armazenado (para strings curtas, limitado)
        int valorBool;      // Valor armazenado (para booleanos)
    } valor;
    struct simbolo *prox;   // Próximo símbolo na lista encadeada
} Simbolo;

// Funções básicas
void inserirSimbolo(const char *nome, const char *tipo);  // Insere símbolo na tabela
Simbolo *buscarSimbolo(const char *nome);                 // Busca símbolo pelo nome
void imprimirTabela();                                    // Imprime toda a tabela
void liberarTabela();                                     // Libera memória da tabela

// Funções estendidas
void inserirSimboloCompleto(const char *nome, const char *tipo, SimboloCategoria categoria, 
                          int linha);  // Insere símbolo com informações completas
TipoDado inferirTipo(const NoAST *expr);  // Infere tipo de uma expressão da AST
TipoDado obterTipoSimbolo(const char *nome); // Obtém tipo de um símbolo
void marcarInicializado(const char *nome);  // Marca que uma variável foi inicializada
void marcarUtilizado(const char *nome);     // Marca que uma variável foi utilizada

// Funções para atribuição de valores
void atribuirValorInt(const char *nome, int valor);         // Atribui valor inteiro
void atribuirValorFloat(const char *nome, float valor);     // Atribui valor flutuante
void atribuirValorBool(const char *nome, int valor);        // Atribui valor booleano
void atribuirValorStr(const char *nome, const char *valor); // Atribui valor string

// Funções para análise e verificação
void verificarVariaveisNaoUtilizadas();                     // Verifica variáveis não utilizadas
void verificarTiposCompativel(TipoDado tipo1, TipoDado tipo2, const char *operacao, int linha); // Verifica compatibilidade de tipos
int estaInicializada(const char *nome);                    // Verifica se variável está inicializada

// Funções para acesso a valores
int obterValorInt(const char *nome, int *valor);           // Obtém valor inteiro
int obterValorFloat(const char *nome, float *valor);       // Obtém valor flutuante
int obterValorBool(const char *nome, int *valor);          // Obtém valor booleano
int obterValorStr(const char *nome, char *valor, int max_len); // Obtém valor string

// Funções para integração com a AST
void analisarAST(const NoAST *raiz);        // Analisa uma AST completa para construir a tabela de símbolos
void analisarDeclaracaoAST(const NoAST *no_decl); // Analisa um nó de declaração
void analisarAtribuicaoAST(const NoAST *no_atrib); // Analisa um nó de atribuição
void analisarExpressaoAST(const NoAST *no_expr);   // Analisa um nó de expressão
void verificarReferenciasAST(const NoAST *raiz);   // Verifica todas referências a variáveis

// Estatísticas e contadores para diagnóstico
typedef struct {
    int total_simbolos;       // Total de símbolos na tabela
    int variaveis;            // Total de variáveis
    int constantes;           // Total de constantes
    int funcoes;              // Total de funções
    int nao_inicializadas;    // Total de variáveis não inicializadas
    int nao_utilizadas;       // Total de variáveis não utilizadas
    int redefinicoes;         // Total de redefinições de variáveis
} EstatisticasTabela;

EstatisticasTabela obterEstatisticas();     // Obtém estatísticas da tabela

#endif