# Semana 5 – Parser com Tratamento de Erros e Precedência

Na quinta semana, demos continuidade ao desenvolvimento do compilador, aprimorando o parser para lidar com erros sintáticos e implementar precedência de operadores, utilizando **Flex** e **Bison**.

## Atividades Realizadas

Durante a semana, o foco foi tornar o analisador mais robusto, capaz de reconhecer expressões aritméticas completas, tratar erros e continuar a análise após encontrar problemas na entrada.

As principais atividades desenvolvidas foram:

- **Implementação de regras gramaticais no Bison**: definimos uma gramática para expressões aritméticas, exigindo que cada expressão termine com `;` e utilizando declarações de precedência para evitar conflitos.
- **Tratamento de erros sintáticos**: adicionamos regras para detectar e recuperar de erros, permitindo que o parser continue analisando as próximas expressões.
- **Ajuste do analisador léxico**: o Flex foi configurado para reconhecer números, operadores, parênteses e ponto e vírgula, além de ignorar espaços e emitir mensagens para caracteres desconhecidos.
- **Automatização da compilação**: utilizamos um Makefile para facilitar o processo de geração dos arquivos e do executável.
- **Testes com entradas válidas e inválidas**: verificamos o comportamento do parser diante de diferentes cenários, observando a recuperação de erros e a correta avaliação das expressões.

Essas atividades fortaleceram a base do compilador, preparando-o para lidar com entradas mais complexas e erros de forma eficiente.

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
   - Digite expressões aritméticas terminadas com `;` (ex: `3+4*2;`). Pressione **Ctrl+D** (Linux/macOS) ou **Ctrl+Z** (Windows) para encerrar.

3. **Verificar a saída**  
   - O parser imprime o resultado de cada expressão reconhecida.
   - Em caso de erro sintático, exibe uma mensagem e recupera até o próximo `;`, permitindo continuar a análise das próximas expressões.

4. **Limpar arquivos gerados**  
   Para remover arquivos intermediários e o executável:
   ```bash
   make clean
   ```

---

Esta semana foi dedicada ao aprimoramento do parser, com foco em robustez, tratamento de erros e precedência de operadores, preparando a base para futuras extensões do compilador. 