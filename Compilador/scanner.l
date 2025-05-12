%{
#include <string.h>
#include <stdlib.h>
#include "parser.tab.h"
extern int yyparse(void);

%}

%% 

[ \t\n]            ;          // Ignorar espaços, tabulação, nova linha
"print"            { return PRINT; }
"if"               { return IF; }
"else"             { return ELSE; }
"int"              { return INT; }
"float"            { /* FLOAT reconhecido */  }
"char"             { /* CHAR reconhecido */  }
"return"           { /* RETURN reconhecido */  }
"while"            { /* WHILE reconhecido */  }
"for"              { /* FOR reconhecido */  }
"break"            { /* BREAK reconhecido */  }
"continue"         { /* CONTINUE reconhecido */  }
[0-9]+             { yylval.intValue = atoi(yytext); return NUM; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.id = strdup(yytext); return ID; }
"=="               { return EQ; }
"!="               { return NEQ; }
">="               { return GE; }
"<="               { return LE; }
">"                { return GT; }
"<"                { return LT; }
"="                { return ASSIGN; }
";"                { return SEMICOLON; }
"("                { return LPAREN; }
")"                { return RPAREN; }
"+"                { return PLUS; }
"-"                { return MINUS; }
"*"                { return TIMES; }
"/"                { return DIVIDE; }
":"                { return COLON; }

[ \t\n]+  { /* não faz nada */ }

.        { printf("Caractere não reconhecido: %s\n", yytext); }

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