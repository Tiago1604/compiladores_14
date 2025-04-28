# Semana 3 - Analisador Léxico Inicial

Na terceira semana, realizamos a implementação inicial do analisador léxico do compilador. 

Adicionamos os tokens conforme a linguagem definida, incluindo:
- Palavras-chave,
- Números,
- Identificadores,
- Símbolos.

Essa etapa foi essencial para identificar e categorizar os elementos básicos do código-fonte, garantindo que o compilador reconheça corretamente os componentes da linguagem alvo.

O trabalho foi baseado no conteúdo apresentado durante a aula prática, com foco na criação do arquivo **scanner.l**.

## Arquivo inicial "scanner.l"

```
%{
#include <stdio.h>
%}

/* Definições de padrões de token e ações */
%%

if          { printf("KW_IF\n"); }
while       { printf("KW_WHILE\n"); }

"//".*     { /* Ignorar comentários de linha */ }

"/*"([^*]|\*+[^*/])*\*+\/    { /* Ignorar comentários de bloco */ }

[a-zA-Z_][a-zA-Z0-9_]*  { printf("IDENT(%s)\n", yytext); }

[0-9]+(\.[0-9]+)?  { printf("NUMBER(%s)\n", yytext); }

[+\-*/=]   { printf("OPERATOR(%s)\n", yytext); }

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
```
