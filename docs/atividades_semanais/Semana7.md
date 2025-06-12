# Semana 7 – Análise Semântica: Tipos e Escopo

Na sétima semana, integramos a análise semântica ao compilador, adicionando verificação de tipos e escopo, além de aprimorar a manipulação da AST, utilizando **Flex** e **Bison**.

## Atividades Realizadas

Durante a semana, o foco foi garantir a correção semântica do código analisado, detectando erros de declaração, tipos e escopo.

As principais atividades desenvolvidas foram:

- **Verificação de declaração de variáveis**: o compilador passou a identificar o uso de variáveis não declaradas.
- **Detecção de redeclaração**: implementamos mecanismos para impedir que uma variável seja declarada mais de uma vez.
- **Verificação de compatibilidade de tipos**: o parser agora detecta atribuições e operações com tipos incompatíveis.
- **Anotação da AST com tipos**: a árvore sintática abstrata passou a registrar informações de tipo para cada nó.
- **Testes automatizados**: utilizamos arquivos de teste para validar casos de sucesso e erro, garantindo robustez na análise semântica.

Essas atividades fortaleceram a base para a geração de código e a evolução do compilador.

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
   - Digite comandos e expressões, pressionando **Ctrl+D** (Linux/macOS) para finalizar a entrada.

3. **Testes automatizados**  
   - Para rodar os testes automáticos:
     ```bash
     ./run_tests.sh
     ```
   - Os arquivos de teste cobrem casos válidos e inválidos de declaração, atribuição e tipos.

4. **Verificar a saída**  
   - O programa exibe mensagens de sucesso ou erro conforme a análise semântica.

5. **Limpar arquivos gerados**  
   Para remover arquivos intermediários e o executável:
   ```bash
   make clean
   ```

--- 