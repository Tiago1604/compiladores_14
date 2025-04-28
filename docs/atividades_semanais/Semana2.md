# Semana 2 - Analisador

Na segunda semana, avançamos no uso das ferramentas **Flex** e **Bison**, implementando um analisador mais complexo que reconhece números e processa entradas.

## Atividades Realizadas

Durante a segunda semana, focamos no desenvolvimento de um analisador léxico e sintático mais robusto, utilizando novamente as ferramentas **Flex** e **Bison**.

As atividades principais realizadas foram:

- **Implementação de um analisador de números**: criamos regras no Flex para reconhecer números inteiros (positivos e negativos), usando expressões regulares.
- **Definição de uma gramática simples no Bison**: definimos regras para que o parser pudesse interpretar as entradas recebidas, associando-as a ações específicas, como imprimir o número lido.
- **Configuração do fluxo de entrada**: testamos tanto a entrada manual no terminal quanto a leitura de dados a partir de um arquivo (`entrada.txt`), garantindo flexibilidade na forma de uso do programa.
- **Tratamento de entradas inválidas**: deixamos o analisador preparado para lidar com caracteres não reconhecidos, com a possibilidade de estender o tratamento de erros caso necessário.

Além da prática de programação, também aprofundamos nossos estudos:
- Revisamos o funcionamento da comunicação entre o analisador léxico (Flex) e o sintático (Bison).
- Entendemos melhor como o Flex gera tokens e como o Bison organiza a lógica de parser através das produções e ações associadas.
- Aprendemos como compilar e linkar corretamente os arquivos gerados, ajustando comandos conforme o ambiente de desenvolvimento.

Essas atividades ajudaram a consolidar a base para projetos mais complexos nas próximas semanas.

## Compilando e executando o exemplo `exemplo.l` + `exemplo.y`

1. **Gerar o arquivo do Bison**  
    ```bash
    bison -d exemplo.y
    ```
    - Isso criará dois arquivos: `exemplo.tab.c` e `exemplo.tab.h` (o `-d` gera o `.h` que contém as definições dos tokens).

2. **Gerar o arquivo do Flex**  
    ```bash
    flex exemplo.l
    ```
    - Isso criará um arquivo `lex.yy.c`.

3. **Compilar tudo junto**  
    Use um compilador C (por exemplo, *gcc*) para gerar o executável:
    ```bash
    gcc -o parser exemplo.tab.c lex.yy.c -lfl
    ```
    - A opção `-lfl` linka a biblioteca do Flex. Em algumas distros, pode ser necessário `-ll` (ou `-lfl -ll`) dependendo das versões, mas normalmente `-lfl` é suficiente.

4. **Executar o programa**  
    - Se quiser digitar manualmente os dados:
      ```bash
      ./parser
      ```
      Em seguida, digite os números na tela e pressione *Enter* ao final de cada. Para encerrar, pressione `Ctrl+D` (em sistemas Unix) ou `Ctrl+Z` (em Windows).
    - Se quiser processar o arquivo `entrada.txt`:
      ```bash
      ./parser entrada.txt
      ```

5. **Verificar a saída**  
    - A cada número reconhecido, o programa imprime `Número lido: <valor>`.
    - O que não bater com `[+\-]?[0-9]{1,10}` será ignorado ou tratado conforme suas regras.  
    - Caso queira tratar caracteres não reconhecidos como erro, basta ajustar a regra `.` no arquivo `.l` para gerar alguma mensagem ou retornar um token de erro.

---
