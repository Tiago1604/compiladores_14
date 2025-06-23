%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "parser.tab.h"
#define YY_NO_INPUT
#define YY_NO_UNPUT

int num_linha = 1;
%}

%%

"if"            { return IF; }
"else"          { return ELSE; }
"for"           { return FOR; }
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

[ \t]+                 ; /* ignora espaços em branco */
[\n]                   { num_linha++; }
#.*    { fprintf(stderr, "Erro: Comentário encontrado na linha %d\n", num_linha); exit(1); }
.                      { printf("Caractere inválido: %s\n", yytext); }

%%

int yywrap(void) {
    return 1;
}