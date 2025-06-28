%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "parser.tab.h"
#define YY_NO_INPUT
#define YY_NO_UNPUT

int num_linha = 1;
extern void adicionar_erro(const char *mensagem);
%}

%%

"if"            { return IF; }
"else"          { return ELSE; }
"for"           { return FOR; }
"while"         { return WHILE; } 
"in"            { return IN; }
"range"         { return RANGE; }
"print"         { return PRINT; }
"def"           { return DEF; }

[0-9]+           { yylval.inteiro = atoi(yytext); return INTEIRO; }
[0-9]+\.[0-9]+  { yylval.flutuante = atof(yytext); return FLUTUANTE; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.str = strdup(yytext); return IDENTIFICADOR; }

"+"                    { return SOMA; }
"-"                    { return SUBTRACAO; }
"*"                    { return MULTIPLICACAO; }
"/"                    { return DIVISAO; }
"="                    { return ATRIBUICAO; }
">"                    { return MAIOR; }
"<"                    { return MENOR; }
">="                   { return MAIOR_IGUAL; }
"<="                   { return MENOR_IGUAL; }
"=="                   { return IGUAL; }
"!="                   { return DIFERENTE; }

"("                    { return ABRE_PAR; }
")"                    { return FECHA_PAR; }
":"                    { return DOIS_PONTOS; }

\"[^\"]*\"  { 
    // Remove as aspas
    yylval.str = strdup(yytext + 1); 
    if (yylval.str[strlen(yylval.str) - 1] == '"')
        yylval.str[strlen(yylval.str) - 1] = '\0';
    return STRING; 
}

[ \t]+                 ; /* ignora espaços em branco */
[\n]                   { num_linha++; }
#.*    { adicionar_erro("Comentário não permitido nesta linguagem"); }
.                      { 
    char erro[256];
    snprintf(erro, sizeof(erro), "Caractere inválido: '%s'", yytext);
    adicionar_erro(erro);
}

%%

int yywrap(void) {
    return 1;
}