# Semana 6 – AST e Tabela de Símbolos

Na sexta semana, avançamos na implementação de estruturas internas essenciais para o compilador: a Árvore Sintática Abstrata (AST) e a Tabela de Símbolos, utilizando **Flex** e **Bison**.

## Atividades Realizadas

Durante a semana, o foco foi construir mecanismos para representar a estrutura do código-fonte e armazenar informações sobre identificadores.

As principais atividades desenvolvidas foram:

- **Implementação da AST**: criamos funções e estruturas para construir e exibir a árvore sintática abstrata das expressões analisadas.
- **Implementação da Tabela de Símbolos**: desenvolvemos uma tabela para registrar identificadores e seus tipos.
- **Integração com o analisador léxico e sintático**: conectamos a geração da AST e o preenchimento da tabela de símbolos ao parser e scanner.
- **Testes com entradas válidas e inválidas**: verificamos a construção da AST, o preenchimento correto da tabela e a emissão de mensagens de erro para casos léxicos e sintáticos.

Essas atividades consolidaram a base para a análise semântica e a evolução do compilador.

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
   - Digite expressões ou comandos e pressione **Ctrl+D** (Linux/macOS) para finalizar a entrada.

3. **Verificar a saída**  
   - O programa exibe a AST construída e a tabela de símbolos.
   - Em caso de erro léxico ou sintático, exibe mensagens claras indicando o problema.

4. **Limpar arquivos gerados**  
   Para remover arquivos intermediários e o executável:
   ```bash
   make clean
   ```

--- 