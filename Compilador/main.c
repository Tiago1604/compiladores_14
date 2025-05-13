#include <stdio.h>
#include <stdlib.h>
#include "tabela.h"

extern FILE *yyin;
extern int yyparse();

int main(int argc, char **argv) {
    // Inicializar a tabela de símbolos
    inicializar_tabela();
    
    if (argc > 1) {
        FILE *f = fopen(argv[1], "r");
        if (!f) {
            fprintf(stderr, "Erro ao abrir arquivo: %s\n", argv[1]);
            return 1;
        }
        yyin = f;
    } else {
        printf("Modo interativo. Digite seu código e pressione Ctrl+D para terminar.\n");
    }

    // Iniciar o processamento
    int resultado = yyparse();
    
    // Liberar recursos
    liberar_tabela();
    
    if (yyin != stdin) {
        fclose(yyin);
    }
    
    return resultado;
}