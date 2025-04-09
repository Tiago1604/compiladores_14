# Explicando

```
%{
#include "exemplo.tab.h"  /* Inclusão do cabeçalho gerado pelo Bison, que contém as definições de tokens */
int yyparse(void); 
%}

/* Definições de padrões de token e açõess */
%%

[ \t\n]+              { /* Não faz nada, apenas ignora */ }

[+\-]?[0-9]{1,10}     {
                        /* Converter o lexema para inteiro (pode estourar se for maior que INT, 
                           mas servirá como exemplo didático) */
                        yylval.intValue = atoi(yytext);
                        return NUM;

                        /* {1,10}
                        aceita numero de so ate 10 digitos*/
                      }


%%

/* Função auxiliar do Flex (quando termina o arquivo de entrada) */
int yywrap(void) {
    return 1;
}

/* Função principal: chamará o parser ao ser executado */
/* diferente so p poder ler arquivo */
int main(int argc, char **argv) {
    /* Se houver arquivo de entrada como parâmetro, redireciona o yyin */
    if (argc > 1) {
        FILE *f = fopen(argv[1], "r");
        if (f) {
            yyin = f;
        }
    }
    return yyparse();
}
```


```yytext```

É uma variavel automatica do flex que guarda a string que entrou na regra
Por exemplo, se digitamos 42 e 42 entra nessa regra agora yytext = '42''

```atoi(yytext)```

Transforma a string yytext em um int
*atoi('42')

```yylval```

é uma variavel usada entre o lex e o byson pra se comunicar, eh como se o lex precisasse dizer pro byson que achou alguma coisa, ele diz o tipo do que achoou e guarda o valor numa variavel que vai pra byson (essa var eh a yylval)

```yylval.intValue```

intValue é so o nome que criarmos pra esse tipo de dado, podia ser valordonumero, biscoito, bolacha... tanto faz, o importante eh que no byson dissemos que:
*int bolacha;*
entao o lex sabe que vamos enviar uma variavek usando yylval pro byson do tipo bolacha e essa variavel eh o atoi da string que fez a regra funcionar

## Byson

```
/* exemplo.y */

%{
#include <stdio.h>
#include <stdlib.h>

/* 
   Declarações explícitas para evitar warnings de 
   “implicit declaration of function yylex/yyerror”
*/
int yylex(void);
void yyerror(const char *s);

%}

%token NUM /* declaramo q vamos receber um token chamado NUM */

%union {
    int intValue; /* dizemos q existe um tipo chamado intValue que eh um inteiro */
}

%type <intValue> NUM /*dizemos que NUM eh do tipo intValue*/

%%
%%
/* A gramática */
programa:
    lista_numeros
    ;

lista_numeros:
/*recursao pura*/
      lista_numeros NUM { printf("Número lido: %d\n", $2); }
    /* se temos uma lista imprimimos o segunda valor passado, a lista eh $1
    e o novo valor $2, se a lista era [10,20,30] todos esses valor sao $1 
    so ver a gramatica:
    lista_numeros NUM
         $1        $2
    */

    | NUM               { printf("Número lido: %d\n", $1); }
    /* se o num ta sozinho entao eh so ele, a gnt imprime ele mesmo, $1
    pq eh o primeiro item q apareceu na regra 
    | significa ou */
    ;
%%

/* Definição de yyerror */
void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático: %s\n", s);
}
```

### Lista_numero Recursao
🔁 Exemplo 1: Entrada = 10
10 é um NUM

Bate com a regra: lista_numeros → NUM

Então lista_numeros = [10]

🔁 Exemplo 2: Entrada = 10 20
10 → vira lista_numeros (caso base)

Agora tem: lista_numeros NUM → que é 10 20

Então lista_numeros = [10, 20]

🔁 Exemplo 3: Entrada = 10 20 30
Começa com 10 → vira lista_numeros

Depois: lista_numeros NUM → 10 20

Depois: lista_numeros NUM de novo → 10 20 30


###Se tivessemos mais variaveis e regras:
**LEX:**

```
[0-9]+ {
    yylval.inteiro = atoi(yytext);  // Decimal
    return NUM_INTEIRO;
}

[01]+b {
    int valor = 0;
    for (int i = 0; yytext[i] != 'b'; ++i)
        valor = valor * 2 + (yytext[i] - '0');

    yylval.inteiro = valor;         // Binário convertido
    return NUM_BINARIO;
}
```

**BISON:**

```
%token NUM_INTEIRO /* declaramo q vamos receber um token chamado NUM */
%token NUM_BINARIO

%union {
    int inteiro; /* dizemos q existe um tipo chamado intValue que eh um inteiro */
}

%type <inteiro> NUM_INTEIRO /*dizemos que NUM eh do tipo intValue*/
%type <inteiro> NUM_BINARIO
```

GRAMATICA:
 
numero:
      NUM_INTEIRO  { printf("Número decimal: %d\n", $1); }
    | NUM_BINARIO  { printf("Número binário convertido: %d\n", $1); }
    ;
