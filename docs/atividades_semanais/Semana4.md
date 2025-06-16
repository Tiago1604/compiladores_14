# Semana 4 – Compilador de Expressões Aritméticas

Na quarta semana, avançamos no desenvolvimento do compilador, implementando um analisador léxico e sintático capaz de reconhecer e validar expressões aritméticas básicas, utilizando as ferramentas **Flex** e **Bison**.

## Atividades Realizadas

Durante a semana, focamos na construção de um analisador que reconhece expressões envolvendo soma, subtração, multiplicação, divisão e parênteses, respeitando a precedência dos operadores.

As principais atividades desenvolvidas foram:

- **Implementação do analisador léxico**: criamos regras no Flex para identificar números, operadores aritméticos e parênteses.
- **Definição da gramática no Bison**: estabelecemos regras para que o parser reconhecesse corretamente as expressões, incluindo a precedência dos operadores.
- **Automatização da compilação**: utilizamos um Makefile para facilitar o processo de geração dos arquivos e do executável.
- **Testes com diferentes entradas**: validamos o funcionamento do analisador com expressões válidas e inválidas, observando o comportamento do parser.

Além da implementação, revisamos conceitos de precedência e associatividade de operadores, fundamentais para a correta análise das expressões.

Essas atividades consolidaram a base para a evolução do compilador nas próximas semanas.

## Compilando e executando o exemplo

1. **Gerar os arquivos necessários**  
   Dentro da pasta `src`:
   ```bash
   make
   ```
   - Isso executa o Bison, o Flex e o compilador C, gerando o executável `parser`.

2. **Executar o programa**  
   ```bash
   ./parser
   ```
   - Digite uma expressão aritmética (ex: `3+4*2`) e pressione **Ctrl+D** (Linux/macOS) ou **Ctrl+Z** (Windows) para finalizar a entrada.
   - Também é possível executar com entrada direta:
     ```bash
     echo "3+4*2" | ./parser
     ```

3. **Verificar a saída**  
   - Se a expressão for reconhecida corretamente, o programa encerra silenciosamente.
   - Em caso de erro sintático, será exibida uma mensagem de erro.

4. **Limpar arquivos gerados**  
   Para remover arquivos intermediários e o executável:
   ```bash
   make clean
   ```

---

Projeto focado em consolidar o uso de Flex e Bison para análise léxica e sintática, com ênfase em precedência de operadores e estrutura básica de um compilador de expressões. 