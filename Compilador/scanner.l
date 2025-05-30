%{
#include <string.h>
#include <stdlib.h>
#include "tipos.h"
#include "parser.tab.h"
#include "tabela.h"

// Declaração da raiz da AST compartilhada
extern NoAST* raiz_ast;

// Declaração da nova função de parsing com verificação
extern int yyparse_and_check();
extern int linha_atual;  // Linha atual para mensagens de erro
%}

%%

[ \t]               ; // Ignora espaços e tabs
\n                  { linha_atual++; } // Incrementa contador de linhas
"print"             { return PRINT; }
"if"                { return IF; }
"else"              { return ELSE; }
"int"               { return INT; }
"float"             { return FLOAT; }
"char"              { return CHAR; }
"return"            { return RETURN; }
"while"             { return WHILE; }
"for"               { return FOR; }
"break"             { return BREAK; }
"continue"          { return CONTINUE; }
"True"              { return TRUE; }
"False"             { return FALSE; }
"None"              { return NONE; }
"not"               { return NOT; }
"and"               { return AND; }
"or"                { return OR; }
"is"                { return IS; }
"lambda"            { return LAMBDA; }
"del"               { return DEL; }
"global"            { return GLOBAL; }
"nonlocal"          { return NONLOCAL; }
"assert"            { return ASSERT; }
"raise"             { return RAISE; }
"try"               { return TRY; }
"except"            { return EXCEPT; }
"finally"           { return FINALLY; }
"with"              { return WITH; }
"yield"             { return YIELD; }
"def"               { return DEF; }
"class"             { return CLASS; }
"async"             { return ASYNC; }
"await"             { return AWAIT; }
"match"             { return MATCH; }
"case"              { return CASE; }
"type"              { return TYPE; }

"=="                { return EQ; }
"!="                { return NEQ; }
">="                { return GE; }
"<="                { return LE; }
">"                 { return GT; }
"<"                 { return LT; }
"="                 { return ASSIGN; }
";"                 { return SEMICOLON; }
"("                 { return LPAREN; }
")"                 { return RPAREN; }
"+"                 { return PLUS; }
"-"                 { return MINUS; }
"*"                 { return TIMES; }
"/"                 { return DIVIDE; }
":"                 { return COLON; }
"{"                 { return LBRACE; }
"}"                 { return RBRACE; }

[0-9]+              { yylval.intValue = atoi(yytext); return NUM; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.id = strdup(yytext); return ID; }

.                   { fprintf(stderr, "[ERRO LÉXICO] Linha %d: Caractere não reconhecido: '%s'\n", linha_atual, yytext); }

%%

// Função chamada ao fim da entrada
int yywrap(void) {
    return 1;  // Retorna 1 para indicar fim de entrada
}

// Função principal do programa
int main(int argc, char **argv) {
    // Se receber argumento na linha de comando, usa como arquivo de entrada
    if (argc > 1) {
        FILE *f = fopen(argv[1], "r");
        if (!f) {
            fprintf(stderr, "Erro ao abrir arquivo: %s\n", argv[1]);
            return 1;
        }
        yyin = f;  // Define entrada para o analisador léxico
    } else {
        printf("Compilador iniciado. Digite seu código (Ctrl+D para finalizar):\n");
    }

    // Usa a nova função que faz parsing e verificação
    int resultado = yyparse_and_check();
    
    // Imprime a tabela de símbolos
    imprimirTabela();
    
    // Libera a memória da tabela
    liberarTabela();
    
    return resultado;
}