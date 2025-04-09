%{
#include "scanner.tab.h"  /* Inclusão do cabeçalho gerado pelo Bison, que contém as definições de tokens */
int yyparse(void); 
%}

/* Definições de padrões de token e ações */
%%

[+\-]?[0-9]+        {
                    yylval.inteiro = atoi(yytext);
                    return NUM;
                    }

[ ]+                 { return ESPA; 
                        /* nao faz nada pq a gnt n tem q retornar, so falar */
                        }

[a-zA-Z_][a-zA-Z0-9_]*  {
                        yylval.texto = strdup(yytext);
                        /* copiar pq yytext pd ser reescrito */
                        return IDENT; 
                        }

[\t\n]+             {}

%%

/* Função auxiliar do Flex (quando termina o arquivo de entrada) */
int yywrap(void) {
    return 1;
}

/* Função principal: chamará o parser ao ser executado */
/* diferente so p poder ler arquivo */
int main(int argc, char **argv) {
    /* Se houver arquivo de entrada como parâmetro, redireciona o yyin */
    if (argc > 1) {
        FILE *f = fopen(argv[1], "r");
        if (f) {
            yyin = f;
        }
    }
    return yyparse();
}