%{
#include "exemplo.tab.h"
int yyparse(void); 
%}

/* Definições de padrões de token e ações */
%%

" "                  { return ESPACO; }  /* Retorna ESPACO para cada espaço encontrado */
[\t\n]+              { /* Ignora tabulações e quebras de linha */ }

[+\-]?[0-9]{1,10}    {
                        yylval.intValue = atoi(yytext);
                        return NUM;
                      }

%%

int yywrap(void) {
    return 1;
}

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *f = fopen(argv[1], "r");
        if (f) {
            yyin = f;
        }
    }
    return yyparse();
}
