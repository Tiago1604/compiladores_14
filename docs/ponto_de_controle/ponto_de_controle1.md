# Ponto de Controle 1

## Definição do Projeto
O objetivo do projeto é desenvolver um compilador que traduz um subconjunto da linguagem Python para C. O compilador deve realizar análise léxica e sintática, reconhecendo estruturas básicas da linguagem Python, como declarações de variáveis, atribuições, expressões aritméticas, comandos condicionais, e comandos de impressão. O resultado esperado é um código C equivalente ao código Python de entrada.

## Linguagem de Programação Escolhida
A linguagem escolhida para o desenvolvimento do compilador é C, utilizando as ferramentas Flex e Bison. A escolha se justifica pela eficiência dessas ferramentas na construção de analisadores léxicos e sintáticos, além de sua ampla utilização em projetos de compiladores. A tradução para C foi escolhida devido à sua simplicidade e proximidade com o hardware, permitindo a geração de código eficiente.

## Planejamento das Sprints
- **Sprint 1**: Definição do projeto e configuração de ambiente.
- **Sprint 2**: Capacitação Individual em Bison e Analisador Léxico.
- **Sprint 3**: Implementação do analisador léxico (scanner) para reconhecer tokens básicos da linguagem Python, como palavras-chave, identificadores, operadores e delimitadores.
- **Sprint 4**: Implementação do analisador sintático (parser) com suporte a regras gramaticais básicas da linguagem Python.
- **Sprint 5**: Integração do scanner e parser, com geração de código C equivalente ao código Python de entrada.
- **Sprint 6**: Testes e validação do compilador, incluindo casos de uso mais complexos e ajustes finais.

## O que Foi Implementado
- Analisador Léxico (scanner.l):
  - Reconhecimento de palavras-chave da linguagem Python, como `print`, `if`, `else`, `int`, entre outras.
  - Identificação de operadores e delimitadores.
  - Suporte a números inteiros e identificadores.
  - Ignora espaços em branco e caracteres não reconhecidos com mensagens de aviso.

- Analisador Sintático (parser.y):
  - Implementação de regras gramaticais para:
    - Declarações de variáveis.
    - Atribuições.
    - Expressões aritméticas.
    - Comandos condicionais.
    - Comandos de impressão.
  - Suporte a operações aritméticas básicas e comparações.
  - Geração de mensagens de saída que representam o código C equivalente ao código Python de entrada.