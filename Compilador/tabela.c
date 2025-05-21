#include "tabela.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Simbolo *tabela = NULL;  // Ponteiro para o início da tabela (implementada como lista encadeada)

// Função para inserir um símbolo na tabela (mantida para compatibilidade)
void inserirSimbolo(const char *nome, const char *tipo) {
    // Delega para a função completa, considerando:
    // - Categoria padrão: variável
    // - Linha desconhecida (-1)
    inserirSimboloCompleto(nome, tipo, SIM_VARIAVEL, -1);
}

// Função para inserir um símbolo completo na tabela (sem escopo)
void inserirSimboloCompleto(const char *nome, const char *tipo, SimboloCategoria categoria, int linha) {
    Simbolo *s = tabela;
    
    // Verifica se o símbolo já existe na tabela
    while (s) {
        if (strcmp(s->nome, nome) == 0) {
            // O símbolo já existe
            if (strcmp(s->tipo, tipo) != 0) {
                fprintf(stderr, "Aviso: Variável '%s' alterou tipo de '%s' para '%s'\n", 
                        nome, s->tipo, tipo);
                // Em Python, podemos mudar o tipo de uma variável, então atualizamos
                strncpy(s->tipo, tipo, 15);
                s->tipo[15] = '\0';
            }
            return; // Não insere novamente
        }
        s = s->prox;
    }
    
    // Cria um novo símbolo
    Simbolo *novo = malloc(sizeof(Simbolo));
    strncpy(novo->nome, nome, 31);      // Copia o nome (limitado a 31 caracteres)
    novo->nome[31] = '\0';              // Garante terminação nula
    strncpy(novo->tipo, tipo, 15);      // Copia o tipo (limitado a 15 caracteres)
    novo->tipo[15] = '\0';              // Garante terminação nula
    
    // Inicializa os novos campos
    novo->categoria = categoria;
    novo->linha = linha;
    novo->inicializado = (categoria == SIM_CONSTANTE) ? 1 : 0;  // Constantes já estão inicializadas
    novo->utilizado = 0;  // Inicialmente não utilizado
    
    // Insere no início da lista
    novo->prox = tabela;
    tabela = novo;
}

// Função para buscar um símbolo pelo nome (simplificada, sem escopo)
Simbolo *buscarSimbolo(const char *nome) {
    for (Simbolo *s = tabela; s; s = s->prox) {
        if (strcmp(s->nome, nome) == 0) {
            return s;  // Retorna o símbolo se encontrado
        }
    }
    return NULL;  // Não encontrado
}

// Função para marcar uma variável como inicializada
void marcarInicializado(const char *nome) {
    Simbolo *s = buscarSimbolo(nome);
    if (s) {
        s->inicializado = 1;
    }
}

// Função para marcar uma variável como utilizada
void marcarUtilizado(const char *nome) {
    Simbolo *s = buscarSimbolo(nome);
    if (s) {
        s->utilizado = 1;
    }
}

// Função para atribuir valor inteiro a uma variável
void atribuirValorInt(const char *nome, int valor) {
    Simbolo *s = buscarSimbolo(nome);
    if (s) {
        if (strcmp(s->tipo, "int") == 0) {
            s->valor.valorInt = valor;
            marcarInicializado(nome);
        } else {
            fprintf(stderr, "Aviso: Atribuindo valor inteiro a variável de tipo %s\n", s->tipo);
            // Em Python, podemos mudar o tipo, então atualizamos
            strncpy(s->tipo, "int", 15);
            s->valor.valorInt = valor;
            marcarInicializado(nome);
        }
    }
}

// Função para verificar variáveis não utilizadas
void verificarVariaveisNaoUtilizadas() {
    int count = 0;
    printf("\nVariáveis declaradas mas não utilizadas:\n");
    
    for (Simbolo *s = tabela; s; s = s->prox) {
        if (s->categoria == SIM_VARIAVEL && !s->utilizado) {
            printf("- '%s' (linha %d)\n", s->nome, s->linha);
            count++;
        }
    }
    
    if (count == 0) {
        printf("Nenhuma variável não utilizada encontrada.\n");
    } else {
        printf("Total: %d variáveis não utilizadas.\n", count);
    }
}

// Função para imprimir toda a tabela de símbolos
void imprimirTabela() {
    printf("\nTabela de Símbolos:\n");
    printf("----------------------------------------------------\n");
    printf("| %-15s | %-10s | %-10s | %-6s |\n", 
           "Nome", "Tipo", "Categoria", "Linha");
    printf("----------------------------------------------------\n");
    
    for (Simbolo *s = tabela; s; s = s->prox) {
        char *categoria_str;
        switch (s->categoria) {
            case SIM_VARIAVEL: categoria_str = "Variável"; break;
            case SIM_CONSTANTE: categoria_str = "Constante"; break;
            case SIM_FUNCAO: categoria_str = "Função"; break;
            case SIM_PARAMETRO: categoria_str = "Parâmetro"; break;
            default: categoria_str = "Desconhecido";
        }
        
        printf("| %-15s | %-10s | %-10s | %-6d |\n", 
               s->nome, s->tipo, categoria_str, s->linha);
    }
    printf("----------------------------------------------------\n");
}

// Função para liberar a memória da tabela de símbolos
void liberarTabela() {
    Simbolo *s = tabela;
    while (s) {
        Simbolo *prox = s->prox;
        free(s);
        s = prox;
    }
    tabela = NULL;  // Reinicia a tabela
}

// Função para obter o valor inteiro de uma variável
// Retorna 1 se sucesso, 0 se falha
int obterValorInt(const char *nome, int *valor) {
    Simbolo *s = buscarSimbolo(nome);
    if (s && strcmp(s->tipo, "int") == 0 && s->inicializado) {
        *valor = s->valor.valorInt;
        return 1;  // Sucesso
    }
    return 0;  // Falha
}

// Função para verificar se uma variável está inicializada
int estaInicializada(const char *nome) {
    Simbolo *s = buscarSimbolo(nome);
    return (s && s->inicializado) ? 1 : 0;
}