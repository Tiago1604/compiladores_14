# Semana 10 – Geração de Bitcode Simples

Na décima semana, finalizamos o ciclo do compilador com a geração de código em formato de bitcode textual, a partir de código-fonte Java simples, utilizando **Flex** e **Bison**.

## Atividades Realizadas

Durante a semana, o foco foi transformar comandos de atribuição e expressões aritméticas em uma sequência de instruções intermediárias (bitcode), aproximando o compilador de um backend real.

As principais atividades desenvolvidas foram:

- **Implementação da geração de bitcode**: criamos funções para percorrer a AST e gerar instruções como `LOAD_CONST`, `ADD` e `STORE`.
- **Testes com arquivos Java de entrada**: validamos a geração correta do bitcode para diferentes exemplos de atribuição e operações.
- **Automação de testes**: utilizamos scripts e arquivos de teste para rodar exemplos automaticamente e verificar a saída do bitcode.

Essas atividades consolidaram o entendimento do processo de tradução de código fonte para uma representação intermediária executável.

## Compilando e executando o exemplo

1. **Gerar os arquivos necessários**  
   Dentro da pasta do projeto:
   ```bash
   make
   ```
   - Isso gera o executável responsável pela análise e geração de bitcode.

2. **Executar os testes**  
   ```bash
   make test
   ```
   - O alvo `test` executa o programa para cada arquivo em `tests/`, exibindo a entrada e a saída em bitcode.

3. **Verificar a saída**  
   - O programa imprime o bitcode correspondente às operações do código-fonte Java analisado.

4. **Limpar arquivos gerados**  
   Para remover arquivos intermediários e o executável:
   ```bash
   make clean
   ```

--- 