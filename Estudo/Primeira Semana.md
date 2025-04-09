# Explicando a Gramática do código
Vamos aprender o que eh cada coisa, o que cada coisa faz

## hello.l
**a parte lexica do codigo**

_codificação para tokens_

```lex
%{
#include "hello.tab.h"  /* Importa definições dos tokens */
#include <stdio.h>
%}


%%

"Hello"    { return HELLO; }  /* Se encontrar "Hello", retorna o token HELLO */
"World"    { return WORLD; }  /* Se encontrar "World", retorna o token WORLD */

[ \t\n]+   { /* Ignora espaços e quebras de linha */ }

.          { /* Ignora qualquer outro caractere */ }

%%

int yywrap(void) {
    return 1;  /* Indica fim da entrada */
}

int main(int argc, char **argv) {
    return yyparse();  /* Chama o parser gerado pelo Bison */
}

```

A unica coisa que vamos fazer É mexer com o que ta dentro dos dois *%%*

```"Hello"    { return HELLO; }  /* Se encontrar "Hello", retorna o token HELLO */```

**_palavra que queremos encontrar no texto_"   { return _NOMETOKEN_; }**

começamos pela palavra que queremos encontrar no texto, a colocamos entre ""
depois entre {} colocamos o comando
nesse caso quando encontramos a palavra X retornamos o token NOMETOKEN

**[ \t\n]+** significa espaços, tabulações ou quebras de linha

colocamos ele pra significar _espaços, tabulações ou quebras de linha_
e depois dizemos ao codigo o que devemos fazer ao encontrar eles

```[ \t\n]+    { /* Ignora espaços e quebras de linha */ }```

**[ \t\n]+    {_ordem_}**

do mesmo jeito que tinhamos usado no reconhecimento e agregacao de token:

```"Hello"    { return HELLO; }  /* Se encontrar "Hello", retorna o token HELLO */```

se deixamos as chaves vazias

**[ \t\n]+    {}**

queremos dizer para ignorar esses caracteres, nao fazer nada com esses caracteres

o mesmo acontece com o **.**
ele significa _qualquer outro caracter que nao seja _espaços, tabulações ou quebras de linha_

nesse codigo então estamos pedindo que ele ignore espaços, tabulações e qualquer outro caracter lixo

**Exemplo:**

```Hello   World!```

**[ \t\n]+:** O Flex vai passar pelos espaços e não vai fazer nada com eles, vai apenas pular para o próximo caractere, que é W.

**.:** O Flex vai passar pelo !, que não corresponde a "Hello" nem "World", e como não há ação associada, ele apenas descarte esse caractere.

## hello.y
**analisador sintatico do codigo**

_definir a gramatica: o gato come o rato - o come rato gato_

```#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void);  // Declara a função yylex() gerada pelo Flex
void yyerror(const char *s);  // Declara a função de erro
%}

// Declaraçoes de variaveis:
%token HELLO   // Define o token HELLO, estamos apenas dizendo ao bison que podemos receber um token chamado HELLO, esse nome desse token tem que ser o mesmo nome do token enviado(return) em hello.l
%token WORLD   // Define o token WORLD, o mesmo

// Agora começa a brincadeira:
%%

start:
    HELLO WORLD { printf("Hello, World!\n"); }   // Quando encontrar "HELLO" seguido de "WORLD", imprime a mensagem
  ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático: %s\n", s);   // Imprime a mensagem de erro em caso de falha na análise sintática
}
```

```%token HELLO   // Define o token HELLO```

estamos declarando e apenas dizendo ao bison que podemos receber um token chamado HELLO, esse nome desse token tem que ser o mesmo nome do token enviado(return) em hello.l

**No Flex, você pode definir qualquer nome para os tokens, mas no Bison esses nomes precisam ser os mesmos.**

essa parte em **hello.l:**

```"Hello"    { return HELLO; }  /* Se encontrar "Hello", retorna o token HELLO */```

tem que ter o mesmo nome dessa parte em **hello.y:**

```%token HELLO   // declara o token HELLO```

porque estamos primeiro dizendo **o que vamos enviar** ao ver a palavra x
e depois estamos declarando que **podemos receber essa coisa**


```
%%

start:
    HELLO WORLD { printf("Hello, World!\n"); }   // Quando encontrar "HELLO" seguido de "WORLD", imprime a mensagem
  ;

%%
```

estamos dizendo que quando encontrarmos os tokens **nessa ordem** fazemos tal coisa, que no caso é imprimir uma mensagem


```
void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático: %s\n", s);   // Imprime a mensagem de erro em caso de falha na análise sintática
}
```

mensagem de erro: se der erro vai aparecer isso!


```
int yylex(void);  // Declara a função yylex() gerada pelo Flex
void yyerror(const char *s);  // Declara a função de erro
```

💡 **Por que declaramos int yylex(void); em hello.y?**

Porque o Bison precisa saber que essa função existe, já que ele a chama para receber tokens. Essa linha só declara a função, mas o código real dela está no arquivo gerado pelo Flex (lex.yy.c).

💡 **Por que declaramos void yyerror(const char s); em hello.y?**

Porque o Bison chama essa função quando encontra um erro, então precisamos garantir que ela está declarada antes de ser usada.

**int yylex(void);**

Declara a função yylex(), que o Flex cria para reconhecer tokens
O Bison chama essa função automaticamente para pegar tokens da entrada

**void yyerror(const char s);**

Declara a função yyerror(), que trata erros sintáticos
O Bison chama essa função quando encontra um erro

# Como compilar e rodar
**📌 Passos no terminal:**

**ATENÇÃO:**  você deve estar dentro da pasta mais dentro de onde estão todos esses arquivos, se estiver em uma pasta mt geral nao vai funcionar.

**1️. Gerar o parser (Bison)**


```bison -d hello.y```

Isso cria:

**hello.tab.c** (código C do parser)

**hello.tab.h** (definições dos tokens)


**2. Gerar o analisador léxico (Flex)**

```flex hello.l```

Isso cria:
**lex.yy.c** (código C do analisador léxico)


**3. Compilar tudo junto**

```gcc -o hello hello.tab.c lex.yy.c -ll```
**Atenção:** eh -ll e não -lfl porque estamos usando um macbook

**Erro:**
isacosta@MacBook-Air-de-Isabelle src % gcc -o hello hello.tab.c lex.yy.c -ll
hello.l:22:12: error: call to undeclared function 'yyparse'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
   22 |     return yyparse();  /* Chama o parser gerado pelo Bison */
      |            ^
1 error generated.

Adicione
```int yyparse(void); ```
no cabeçalho do arquivo .l


**4. Executar:**

```./hello```

### O que faz cada arquivo?

**hello.tab.c**	

Quem cria: Bison

O que faz: Implementa o analisador sintático em C


**hello.tab.h**

Quem cria: Bison

O que faz: Define os tokens que o Flex precisa conhecer


**lex.yy.c**

Quem cria: Flex

O que faz: Implementa o analisador léxico em C
 
 
 
1️⃣ **hello.tab.c (Código C do Parser – Bison)**


Contém a implementação do analisador sintático.


Ele define as regras da gramática e chama yylex() para obter tokens do analisador léxico.


Esse código verifica se a sequência de tokens faz sentido, de acordo com as regras definidas no hello.y.


2️⃣ **hello.tab.h (Definições dos Tokens – Bison)**


Contém as definições dos tokens como HELLO e WORLD.


O Flex importa esse arquivo para saber quais tokens pode devolver para o Bison.


Sem esse arquivo, o Flex não reconheceria os nomes dos tokens.


3️⃣ **lex.yy.c (Código C do Analisador Léxico – Flex)**


Contém a implementação do analisador léxico.


Ele escaneia o texto de entrada, encontra padrões (Hello, World) e retorna tokens (HELLO, WORLD) para o Bison.


Essa função gerada chama-se yylex() e é usada pelo parser (hello.tab.c).
