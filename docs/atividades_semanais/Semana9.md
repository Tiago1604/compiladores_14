# Semana 9 – Otimização de Código (Constant Folding)

Na nona semana, o foco foi a otimização de código intermediário, implementando técnicas de simplificação de expressões constantes (constant folding) utilizando **Flex** e **Bison**.

## Atividades Realizadas

Durante a semana, aprimoramos o compilador para identificar e simplificar operações envolvendo apenas constantes, tornando o código gerado mais eficiente.

As principais atividades desenvolvidas foram:

- **Implementação do constant folding**: criamos funções para percorrer a AST e substituir operações entre constantes por seus resultados.
- **Testes com diferentes expressões**: validamos a otimização em casos simples e compostos, garantindo que apenas expressões constantes fossem simplificadas.
- **Automação de testes**: utilizamos arquivos de entrada e scripts para rodar exemplos automaticamente e comparar a saída otimizada.

Essas atividades fortaleceram a etapa de otimização do compilador, preparando-o para gerar código mais eficiente.

## Compilando e executando o exemplo

1. **Gerar os arquivos necessários**  
   No diretório raiz do projeto:
   ```bash
   make
   ```
   - Isso gera o executável `optimize`.

2. **Executar os testes**  
   ```bash
   make test
   ```
   - O alvo `test` executa o programa para cada arquivo em `tests/`, exibindo entrada e saída.

3. **Verificar a saída**  
   - O programa imprime a versão otimizada das expressões analisadas.

4. **Limpar arquivos gerados**  
   Para remover arquivos intermediários e o executável:
   ```bash
   make clean
   ```

--- 