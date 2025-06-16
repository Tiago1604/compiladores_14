#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

// Declaração de variáveis externas
extern FILE *yyin;
extern int yyparse(void);
No *raiz;

int main(int argc, char **argv) {
    // Verifica se o número de argumentos está correto
    if (argc != 3) {
        fprintf(stderr, "Uso: %s arquivo_entrada arquivo_saida\n", argv[0]);
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

    //Abre o arquivo de saída para escrita do código C gerado
    FILE *saida = fopen(argv[2], "w");
    if (!saida) {
        fprintf(stderr, "Não foi possível abrir o arquivo de saída %s\n", argv[2]);
        exit(1);
    }

    // Adiciona os includes necessários no código gerado
    fprintf(saida, "#include <stdio.h>\n\n");

    // Gera o código C a partir da árvore sintática
    gerar_codigo_c(raiz, saida);

    // Fecha os arquivos abertos
    fclose(yyin);
    fclose(saida);

    return 0;
} 