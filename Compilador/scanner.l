%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"
%}

%option yylineno

%%

[ \t\r]            ; // Ignorar espaços, tabulação
[\n]               ; // Ignorar nova linha
"print"            { return PRINT; }
"if"               { return IF; }
"else"             { return ELSE; }
"int"              { return INT; }
"float"            { return FLOAT; }
"char"             { /* CHAR reconhecido, mas não processado nesta versão */ }
"return"           { /* RETURN reconhecido, mas não processado nesta versão */ }
"while"            { /* WHILE reconhecido, mas não processado nesta versão */ }
"for"              { /* FOR reconhecido, mas não processado nesta versão */ }
"break"            { /* BREAK reconhecido, mas não processado nesta versão */ }
"continue"         { /* CONTINUE reconhecido, mas não processado nesta versão */ }
[0-9]+             { yylval.intValue = atoi(yytext); return NUM; }
[0-9]+\.[0-9]+     { yylval.floatValue = atof(yytext); return FLOAT_NUM; }
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
"//".*             ; // Comentários de linha única
[/][*][^*]*[*]+([^*/][^*]*[*]+)*[/] ; // Comentários de múltiplas linhas

.        { printf("Caractere não reconhecido: %s\n", yytext); }

%%

int yywrap(void) {
    return 1;
}