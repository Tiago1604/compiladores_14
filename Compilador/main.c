#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

// Declaração de variáveis externas
extern FILE *yyin;
extern int yyparse(void);
extern int tem_erro(); // Nova função para verificar se houve erros
No *raiz;

int main(int argc, char **argv) {
    // Verifica se o número de argumentos está correto
    if (argc != 3) {
        fprintf(stderr, "Uso: %s arquivo_entrada[.py|.txt] arquivo_saida.c\n", argv[0]);
        exit(1);
    }

    // Verifica se o arquivo de entrada tem extensão .py ou .txt
    const char *entrada = argv[1];
    int len = strlen(entrada);
    if (len < 4 || (strcmp(entrada + len - 3, ".py") != 0 && 
                    strcmp(entrada + len - 4, ".txt") != 0)) {
        fprintf(stderr, "Erro: O arquivo de entrada deve ter extensão .py ou .txt\n");
        exit(1);
    }

    //Abre o arquivo de entrada para análise léxica
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "Não foi possível abrir o arquivo de entrada %s\n", argv[1]);
        exit(1);
    }

    // Executa o parser (análise sintática)
    yyparse();

    // Se houver erros, não gera o arquivo de saída
    if (tem_erro()) {
        fprintf(stderr, "\nErros encontrados. Arquivo de saída não foi gerado.\n");
        fclose(yyin);
        return 1;
    }

    //Abre o arquivo de saída para escrita do código C gerado
    FILE *saida = fopen(argv[2], "w");
    if (!saida) {
        fprintf(stderr, "Não foi possível abrir o arquivo de saída %s\n", argv[2]);
        exit(1);
    }

    
    printf("[DEBUG] Parser terminou, começando geração de código...\n");
    
    // Gera o código C a partir da árvore sintática
    gerar_codigo_c(raiz, saida);
  
    // Fecha os arquivos abertos
    fclose(yyin);
    fclose(saida);

    return 0;
} 