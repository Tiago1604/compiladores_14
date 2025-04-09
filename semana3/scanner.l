%{
#include <stdio.h>
%}

/* Definições de padrões de token e ações */
%%

if          { printf("KW_IF\n"); }

while       { printf("KW_WHILE\n"); }

switch      { printf("KW_SWITHC\n"); }

for         { printf("KW_FOR\n"); }

print      { printf("KW_PRINTF\n"); }

"("         { printf("KW_PARENTESE_ABRE\n"); }

")"         { printf("KW_PRINTF\n"); }

":"         { printf("KW_PRINTF\n"); }

","         { printf("KW_PRINTF\n"); }

"{"         { printf("KW_PRINTF\n"); }

"}"         { printf("KW_PRINTF\n"); }

";"         { printf("KW_PRINTF\n"); }

"'"         { printf("KW_teste1\n"); }

">"         { printf("KW_teste1\n"); }

"<"         { printf("KW_teste1\n"); }

"return"    { printf("KW_PRINTF\n"); }

"import"    { printf("KW_PRINTF\n"); }

"from"      { printf("KW_PRINTF\n"); }

"def"       { printf("KW_PRINTF\n"); }

"range"     { printf("KW_PRINTF\n"); }

"int"       { printf("KW_PRINTF\n"); }

"float"     { printf("KW_PRINTF\n"); }

"string"    { printf("KW_PRINTF\n"); }

"bool"         { printf("KW_PRINTF\n"); }

"double"         { printf("KW_PRINTF\n"); }

"in"         { printf("KW_PRINTF\n"); }

"with"         { printf("KW_PRINTF\n"); }

"not"         { printf("KW_PRINTF\n"); }

"try"         { printf("KW_PRINTF\n"); }

"except"         { printf("KW_PRINTF\n"); }

"break"         { printf("KW_PRINTF\n"); }

"continue"         { printf("KW_PRINTF\n"); }

"or"         { printf("KW_PRINTF\n"); }

"and"         { printf("KW_PRINTF\n"); }

"elif"         { printf("KW_PRINTF\n"); }

"class"         { printf("KW_PRINTF\n"); }

[//"]         { printf("KW_teste1\n"); }

"//".*     { /* Ignorar comentários de linha */ }

"/*"([^*]|\*+[^*/])*\*+\/    { /* Ignorar comentários de bloco */ }

[a-zA-Z_][a-zA-Z0-9_]*  { printf("IDENT(%s)\n", yytext); }

[0-9]+(\.[0-9]+)?  { printf("NUMBER(%s)\n", yytext); }

[+\-*/=%]   { printf("OPERATOR(%s)\n", yytext); }

[ \t\n]+  { /* Não faz nada */ }

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
