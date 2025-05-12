%{
#include <string.h>
#include <stdlib.h>
#include "par.tab.h"
extern int yyparse(void);

%}

%% 
[ \t\n]            ;          // Ignorar espaços, tabulação, nova linha

"+"         { return operador_mais; }
"-"         { return operador_menos; }
"*"         { return operador_multiplicacao; }
"/"         { return operador_divisao; }

"="         { return atribuicao_igual; }

"print"         { return comando_print; }

"=="   { yylval.str = strdup("=="); return comparador_igual; }
"!="   { yylval.str = strdup("!="); return comparador_diferente; }
">"    { yylval.str = strdup(">"); return comparador_maior_que; }
"<"    { yylval.str = strdup("<"); return comparador_menor_que; }
">="   { yylval.str = strdup(">="); return comparador_maior_igual; }
"<="   { yylval.str = strdup("<="); return comparador_menor_igual; }

[0-9]+             { yylval.intValue = atoi(yytext); return NUM; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.id = strdup(yytext); return ID; }

[ \t\n]+    { /* Espaços */ }

.           { printf("UNKNOWN_CHAR(%s)\n", yytext); }

%%

int yywrap(void) {
    return 1;
}

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *f = fopen(argv[1], "r");
        if (!f) {
            fprintf(stderr, "Erro ao abrir arquivo: %s\n", argv[1]);
            return 1;
        }
        yyin = f;
    }

    return yyparse();
}