# Especificação do Projeto: PYtoC

## 1. Visão Geral

PYtoC é um compilador que traduz um subconjunto da linguagem Python para código C. O projeto foi desenvolvido como parte da disciplina de Compiladores, utilizando as ferramentas Flex e Bison.

## 2. Funcionalidades Implementadas

### 2.1 Estruturas Suportadas
- Variáveis e tipos básicos (int, float)
- Operações aritméticas (+, -, *, /)
- Operações de comparação (==, !=, <, >, <=, >=)
- Estruturas de controle:
  - if/else
  - for in range()
  - while
- Funções (definição e chamada)
- Comando print para saída

### 2.2 Análise Léxica (Scanner)
- Reconhecimento de tokens:
  - Palavras-chave (if, else, for, while, in, range, print, def)
  - Identificadores
  - Números (inteiros e flutuantes)
  - Operadores
  - Delimitadores

### 2.3 Análise Sintática (Parser)
- Gramática livre de contexto para o subconjunto Python
- Construção da AST (Árvore Sintática Abstrata)
- Tratamento de precedência de operadores
- Gerenciamento de escopo

### 2.4 Geração de Código
- Tradução direta para código C
- Mapeamento de estruturas Python para C
- Gerenciamento de tipos
- Tratamento de funções

## 3. Problemas e Soluções

### 3.1 Integração Flex/Bison
- **Problema**: Dificuldades na integração inicial entre analisador léxico e sintático
- **Solução**: Revisão da documentação e uso correto do arquivo parser.tab.h

### 3.2 Compatibilidade macOS
- **Problema**: Dificuldades específicas no ambiente macOS
- **Solução**: Ajustes na configuração e uso do arquivo de cabeçalho do Bison

### 3.3 Compilação GCC
- **Problema**: Erros de compilação com funções não definidas
- **Solução**: Inclusão da biblioteca -lfl e ajustes no comando de compilação

### 3.4 Parser e AST
- **Problema**: Complexidade na construção e vinculação dos nós da AST
- **Solução**: Refinamento das regras gramaticais e mecanismos de construção dinâmica

### 3.5 Gerenciamento de Escopo
- **Problema**: Conflitos entre variáveis em diferentes contextos
- **Solução**: Implementação de sistema de escopo hierárquico

## 4. Decisões Técnicas

### 4.1 Ferramentas
- Flex para análise léxica
- Bison para análise sintática
- GCC para compilação
- MkDocs para documentação

### 4.2 Estrutura do Projeto
- Organização modular em diretórios específicos
- Controle de versão com Git
- Branches organizados por funcionalidade

### 4.3 Padrões de Código
- Nomenclatura consistente
- Comentários explicativos
- Tratamento de erros robusto

## 5. Estado Atual do Projeto

### 5.1 Funcionalidades Completas
- Análise léxica
- Análise sintática básica
- Geração de código para estruturas fundamentais
- Tabela de símbolos
- Gerenciamento de escopo

### 5.2 Limitações Conhecidas
- Sem suporte a arrays/listas
- Sem suporte a strings em todas operações
- Funções sem parâmetros
- Sem suporte a módulos/imports

### 5.3 Próximos Passos
- Implementação de strings completa
- Suporte a parâmetros em funções
- Melhorias no tratamento de erros
- Otimizações no código gerado

## 6. Compilação e Uso

### 6.1 Requisitos
- Flex e Bison instalados
- GCC
- Make (opcional)

### 6.2 Comandos de Compilação
```bash
flex scanner.l
bison -d parser.y
gcc -o compilador parser.tab.c lex.yy.c ast.c tabela.c -lfl
```

### 6.3 Execução
```bash
./compilador < entrada.py > saida.c
gcc saida.c -o programa
./programa
```

## 7. Documentação

A documentação completa do projeto está organizada nos seguintes diretórios:
- `/docs/problemas_e_solucoes/`: Registro de problemas encontrados e soluções
- `/docs/decisoes/`: Documentação das decisões técnicas
- `/docs/Projeto_Final/`: Especificação final do projeto
