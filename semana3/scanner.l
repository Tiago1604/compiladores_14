%{
#include <stdio.h>
%}

/* Padrões de tokens e ações correspondentes */
%%

"+"         { printf("OPERATOR(%s)\n", yytext); }
"-"         { printf("OPERATOR(%s)\n", yytext); }
"*"         { printf("OPERATOR(%s)\n", yytext); }
"/"         { printf("OPERATOR(%s)\n", yytext); }
"//"        { printf("OPERATOR(%s)\n", yytext); }
"%"         { printf("OPERATOR(%s)\n", yytext); }
"**"        { printf("OPERATOR(%s)\n", yytext); }
"@"         { printf("OPERATOR(%s)\n", yytext); }

"=="        { printf("OPERATOR(%s)\n", yytext); }
"!="        { printf("OPERATOR(%s)\n", yytext); }
">"         { printf("OPERATOR(%s)\n", yytext); }
"<"         { printf("OPERATOR(%s)\n", yytext); }
">="        { printf("OPERATOR(%s)\n", yytext); }
"<="        { printf("OPERATOR(%s)\n", yytext); }

"="         { printf("OPERATOR(%s)\n", yytext); }
"+="        { printf("OPERATOR(%s)\n", yytext); }
"-="        { printf("OPERATOR(%s)\n", yytext); }
"*="        { printf("OPERATOR(%s)\n", yytext); }
"/="        { printf("OPERATOR(%s)\n", yytext); }
"//="       { printf("OPERATOR(%s)\n", yytext); }
"%="        { printf("OPERATOR(%s)\n", yytext); }
"**="       { printf("OPERATOR(%s)\n", yytext); }
"@="        { printf("OPERATOR(%s)\n", yytext); }

"and"       { printf("OPERATOR(%s)\n", yytext); }
"or"        { printf("OPERATOR(%s)\n", yytext); }
"not"       { printf("OPERATOR(%s)\n", yytext); }

"in"        { printf("OPERATOR(%s)\n", yytext); }
"not"[ \t]+"in"  { printf("OPERATOR(not in)\n"); }

"is"        { printf("OPERATOR(%s)\n", yytext); }
"is"[ \t]+"not" { printf("OPERATOR(is not)\n"); }

"False"     { printf("KEYWORD(%s)\n", yytext); }
"None"      { printf("KEYWORD(%s)\n", yytext); }
"True"      { printf("KEYWORD(%s)\n", yytext); }
"as"        { printf("KEYWORD(%s)\n", yytext); }

"break"     { printf("KEYWORD(%s)\n", yytext); }
"continue"  { printf("KEYWORD(%s)\n", yytext); }
"elif"      { printf("KEYWORD(%s)\n", yytext); }
"else"      { printf("KEYWORD(%s)\n", yytext); }
"if"        { printf("KEYWORD(%s)\n", yytext); }
"for"       { printf("KEYWORD(%s)\n", yytext); }
"while"     { printf("KEYWORD(%s)\n", yytext); }

"try"       { printf("KEYWORD(%s)\n", yytext); }
"except"    { printf("KEYWORD(%s)\n", yytext); }
"finally"   { printf("KEYWORD(%s)\n", yytext); }
"raise"     { printf("KEYWORD(%s)\n", yytext); }

"class"     { printf("KEYWORD(%s)\n", yytext); }
"def"       { printf("KEYWORD(%s)\n", yytext); }
"del"       { printf("KEYWORD(%s)\n", yytext); }
"lambda"    { printf("KEYWORD(%s)\n", yytext); }
"pass"      { printf("KEYWORD(%s)\n", yytext); }
"return"    { printf("KEYWORD(%s)\n", yytext); }
"yield"     { printf("KEYWORD(%s)\n", yytext); }

"from"      { printf("KEYWORD(%s)\n", yytext); }
"import"    { printf("KEYWORD(%s)\n", yytext); }
"global"    { printf("KEYWORD(%s)\n", yytext); }
"nonlocal"  { printf("KEYWORD(%s)\n", yytext); }

"with"      { printf("KEYWORD(%s)\n", yytext); }

"("         { printf("SYMBOL(%s)\n", yytext); }
")"         { printf("SYMBOL(%s)\n", yytext); }
"["         { printf("SYMBOL(%s)\n", yytext); }
"]"         { printf("SYMBOL(%s)\n", yytext); }
"{"         { printf("SYMBOL(%s)\n", yytext); }
"}"         { printf("SYMBOL(%s)\n", yytext); }

":"         { printf("SYMBOL(%s)\n", yytext); }
";"         { printf("SYMBOL(%s)\n", yytext); }
","         { printf("SYMBOL(%s)\n", yytext); }
"."         { printf("SYMBOL(%s)\n", yytext); }


"'"         { printf("SYMBOL(%s)\n", yytext); }
"\""        { printf("SYMBOL(%s)\n", yytext); }


"_"         { printf("SYMBOL(%s)\n", yytext); }
"\\"        { printf("SYMBOL(%s)\n", yytext); }
"#"         { printf("SYMBOL(%s)\n", yytext); }

"//".*      { /* Comentário de linha */ }
"/*"([^*]|\*+[^*/])*\*+\/ { /* Comentário de bloco */ }

[a-zA-Z_][a-zA-Z0-9_]*  { printf("IDENTIFIER(%s)\n", yytext); }
[0-9]+(\.[0-9]+)?       { printf("LITERAL_NUMBER(%s)\n", yytext); }
\"([^\"\n\\]|\\.)*\"    { printf("LITERAL_STRING(%s)\n", yytext); }
'([^'\n\\]|\\.)*'       { printf("LITERAL_STRING(%s)\n", yytext); }

[ \t\n]+    { /* Espaços */ }

.           { printf("UNKNOWN_CHAR(%s)\n", yytext); }

%%

/* Função para finalizar análise */
int yywrap(void) {
    return 1;
}

/* Ponto de entrada principal */
int main(void) {
    yylex();
    return 0;
}