# Semana 8 – Geração de Código Intermediário (TAC)

Na oitava semana, avançamos para a etapa de geração de código intermediário, implementando a produção de Código de Três Endereços (TAC) a partir da AST, utilizando **Flex** e **Bison**.

## Atividades Realizadas

Durante a semana, o foco foi transformar a árvore sintática abstrata em uma sequência de instruções intermediárias, facilitando etapas futuras de otimização e geração de código final.

As principais atividades desenvolvidas foram:

- **Implementação da geração de TAC**: criamos funções para percorrer a AST e gerar instruções de três endereços correspondentes às operações analisadas.
- **Testes com expressões aritméticas e atribuições**: validamos a geração correta do TAC para diferentes entradas.
- **Automação de testes**: utilizamos scripts para rodar exemplos automaticamente e verificar a saída do código intermediário.

Essas atividades consolidaram a ponte entre a análise sintática/semântica e a geração de código.

## Compilando e executando o exemplo

1. **Gerar os arquivos necessários**  
   Dentro da pasta `src`:
   ```bash
   make
   ```
   - Isso gera o executável `main`.

2. **Executar o programa**  
   ```bash
   ./main
   ```
   - Digite expressões ou comandos e pressione **Ctrl+D** (Linux/macOS) para finalizar a entrada.

3. **Verificar a saída**  
   - O programa imprime o código TAC gerado para as expressões analisadas.

4. **Testes automatizados**  
   - Para rodar os testes automáticos:
     ```bash
     ./run_tests.sh
     ```
   - Os arquivos de teste cobrem diferentes exemplos de expressões e atribuições.

5. **Limpar arquivos gerados**  
   Para remover arquivos intermediários e o executável:
   ```bash
   make clean
   ```

--- 