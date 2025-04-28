%{
#include <stdio.h>
%}

/* Definições de padrões de token e ações */
%%

if          { printf("KW_IF\n"); }

while       { printf("KW_WHILE\n"); }

switch      { printf("KW_SWITCH\n"); }

for         { printf("KW_FOR\n"); }

print      { printf("KW_PRINTF\n"); }

"("         { printf("KW_PARENTESE_ABRE\n"); }

")"         { printf("KW_PARENTESE_FECHA\n"); }

":"         { printf("KW_COLON\n"); }

","         { printf("KW_VIRGULA\n"); }

"{"         { printf("KW_ABRE_CHAVE\n"); }

"}"         { printf("KW_FECHA_CHAVE\n"); }

";"         { printf("KW_PONTO_VIRGULA\n"); }

"'"         { printf("KW_TEXTO_SIMBOLO\n"); }

">"         { printf("KW_MAIOR_QUE\n"); }

"<"         { printf("KW_MENOR_QUE\n"); }

"return"    { printf("KW_RETURN\n"); }

"import"    { printf("KW_IMPORT\n"); }

"from"      { printf("KW_FROM\n"); }

"def"       { printf("KW_DEF\n"); }

"range"     { printf("KW_RANGE\n"); }

"int"       { printf("KW_INT\n"); }

"float"     { printf("KW_FLOAT\n"); }

"string"    { printf("KW_STRING\n"); }

"bool"      { printf("KW_BOOL\n"); }

"double"    { printf("KW_DOUBLE\n"); }

"in"        { printf("KW_IN\n"); }

"with"      { printf("KW_WITH\n"); }

"not"       { printf("KW_NOT\n"); }

"try"       { printf("KW_TRY\n"); }

"except"    { printf("KW_EXCEPT\n"); }

"break"     { printf("KW_BREAK\n"); }

"continue"  { printf("KW_CONTINUE\n"); }

"or"        { printf("KW_OR\n"); }

"and"       { printf("KW_AND\n"); }

"elif"      { printf("KW_ELIF\n"); }

"class"     { printf("KW_CLASS\n"); }
"//".*     { /* Ignorar comentários de linha */ }

"/*"([^*]|\*+[^*/])*\*+\/    { /* Ignorar comentários de bloco */ }

[a-zA-Z_][a-zA-Z0-9_]*  { printf("IDENT(%s)\n", yytext); }

[0-9]+(\.[0-9]+)?  { printf("NUMBER(%s)\n", yytext); }

[+\-*/=%]   { printf("OPERATOR(%s)\n", yytext); }

[ \t\n]+  { /* Não faz nada */ }

\"([^\"\n\\]|\\.)*\"  { printf("STRING(%s)\n", yytext); }

'([^'\n\\]|\\.)*'     { printf("STRING(%s)\n", yytext); }

.  { printf("UNKNOWN(%s)\n", yytext); }

%%

/* Função auxiliar do Flex (quando termina o arquivo de entrada) */
int yywrap(void) {
    return 1;
}

/* Função principal: executa o analisador léxico */
int main(void) {
    yylex();
    return 0;
}
