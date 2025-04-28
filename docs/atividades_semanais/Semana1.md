# Semana 1 - Hello World

Na primeira semana, realizamos a instalação e configuração do ambiente de desenvolvimento e fizemos a implementação básica e testes inicias.

##S Atividades realizadas

- Realizamos a implementação de dois principais exemplos, ambos utilizando as ferramentas **Flex** e **Bison**;
 - O primeiro se referia à implementação de um exemplo simples de "Hello World";
 - O segundo se referia à implementação de uma simples calculadora que aceitava uma cadeia de números e símbolos.

Os exemplos permitiram enteder o funcionamento e implementação inicial de um compilador, entendendo o processo de análise léxica e sintática realizada pelas ferramentas utilizadas.

Segue o guia para compilar o exemplo "Hello World" que está na pasta "semana 1":

## Compilando e executando o exemplo `hello.l` + `hello.y`

Para compilar e executar o exemplo, siga os passos abaixo:

1. **Gerar os arquivos do *Bison*** (no terminal, no mesmo diretório):
    ```bash
    bison -d hello.y
    ```
    - Isso criará o **hello.tab.c** (com o código C do parser) e o **hello.tab.h** (com as definições dos tokens).

2. **Gerar o arquivo do *Flex***:
    ```bash
    flex hello.l
    ```
    - Isso criará o **lex.yy.c** (código C do analisador léxico).

3. **Compilar tudo junto** (usando o *gcc* ou outro compilador C):
    ```bash
    gcc -o hello hello.tab.c lex.yy.c -lfl
    ```
    - A opção `-lfl` linka a biblioteca do Flex (em algumas distribuições, pode ser necessário usar `-ll`).

4. **Executar** o binário gerado:
    ```bash
    ./hello
    ```
    - Se você digitar *HelloWorld* (ou usar um arquivo de entrada contendo `Hello World`), o parser deve reconhecer e imprimir *Hello, World!* na tela, conforme as regras de gramática definidas.

---
