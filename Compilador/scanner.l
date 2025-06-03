
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

// Referência à variável definida no parser.y
extern int indent_level;  // ALTERADO: usar extern em vez de redefinir

// Variáveis para controle de indentação (apenas aquelas exclusivas do scanner)
int pending_indents = 0; // Indentações pendentes para processar
%}

%%

[ \t]               ; // Ignora espaços e tabs
\n                  { linha_atual++; } // Incrementa contador de linhas

#.*                 ; // Comentários em Python (ignora até o final da linha)

"print"             { return PRINT; }
"if"                { return IF; }
"else"              { return ELSE; }
"int"               { return INT; }
"float"             { return FLOAT; }
"char"              { return CHAR; }
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
"def"               { return DEF; }
"return"            { return RETURN; }
"class"             { return CLASS; }

"=="                { return EQ; }
"!="                { return NEQ; }
">="                { return GE; }
"<="                { return LE; }
">"                 { return GT; }
"<"                 { return LT; }
"="                 { return ASSIGN; }
";"                 { return SEMICOLON; } // Usado para terminação em nossa sintaxe
"("                 { return LPAREN; }
")"                 { return RPAREN; }
"+"                 { return PLUS; }
"-"                 { return MINUS; }
"*"                 { return TIMES; }
"/"                 { return DIVIDE; }
":"                 { return COLON; }  // Importante para blocos em Python
"{"                 { return LBRACE; } // Para blocos explícitos em nossa sintaxe
"}"                 { return RBRACE; } // Para blocos explícitos em nossa sintaxe

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
        printf("Compilador Python para C iniciado. Digite seu código Python (Ctrl+D para finalizar):\n");
    }

    // Usa a nova função que faz parsing e verificação
    int resultado = yyparse_and_check();
    
    // Imprime a tabela de símbolos
    imprimirTabela();
    
    // Libera a memória da tabela
    liberarTabela();
    
    return resultado;
}
