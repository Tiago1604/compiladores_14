# PyToC

## Introdução

Bem-vindo ao repositório da disciplina de **Compiladores**.

Nesta matéria, exploraremos os fundamentos e os mecanismos envolvidos na construção de compiladores — programas que traduzem código-fonte de uma linguagem de programação para outra, geralmente para linguagem de máquina.
O objetivo principal é compreender como linguagens de programação são interpretadas e executadas por computadores, além de desenvolver um compilador de `Python` para `C` como projeto prático, esse compilador será desenvolvido utilizando o Bison e Flex.

Link para o pages: [Link](https://tiago1604.github.io/compiladores_14/)

## Estrutura do Repositório

### Descrição dos Diretórios

- **`Compilador/`**: Contém os arquivos principais do compilador, incluindo os arquivos Flex e Bison, além do executável gerado.
- **`Estudo/`**: Diretório com materiais de estudo e resumos das semanas iniciais.
- **`docs/`**: Diretório com documentação detalhada, incluindo atas, planejamento e atividades semanais.
- **`semana 1/`, `semana2/`, `semana3/`**: Diretórios organizados por semana.
- **`mkdocs.yml`**: Arquivo de configuração para gerar documentação com o MkDocs.

Essa estrutura foi projetada para organizar o projeto de forma clara, separando o código-fonte, documentação, materiais de estudo e versões semanais do compilador.

## Como Executar
1. **Clonar o repositório**
   ```bash
   git clone https://github.com/Tiago1604/compiladores_14
   cd compiladores_14
   ```

2. **Instalar dependências**
   - É necessário ter **Flex** e **Bison** instalados no sistema.  
   - Em distribuições Linux baseadas em Debian/Ubuntu:
     ```
     sudo apt-get update
     ```
     ```
     sudo apt-get install flex bison
     ```
   - Em outras plataformas, consulte a documentação.

3. **Entre em Compilador**
    - Para compilar manualmente:
   ```
    cd Compilador
    ```
    ```
    bison -d parser.y
    ```
    ```
    flex scanner.l
    ```
    ```
    gcc -o compilador parser.tab.c lex.yy.c -lfl
    ```

    ```
    ./compilador
    ```
    ou
    ```
    ./compilador < entrada.txt
    ```

## Ajustes e Melhorias

- **AST (Árvore Sintática Abstrata):**
   - Refatoração das estruturas de dados para facilitar a manipulação e geração de código.
   - Implementação de novos tipos de nós para suportar mais construções da linguagem Python.

- **Parser:**
   - Correção de ambiguidades e conflitos de precedência nas regras gramaticais.
   - Adição de suporte a novas estruturas sintáticas do Python.
   - Melhoria nas mensagens de erro para facilitar o diagnóstico de problemas.

- **Léxico:**
   - Expansão do conjunto de tokens reconhecidos, incluindo operadores e palavras-chave adicionais.
   - Ajuste nas expressões regulares para maior precisão na identificação de identificadores e literais.

- **Tabela de Símbolos:**
   - Implementação de escopos aninhados para melhor controle de variáveis locais e globais.
   - Armazenamento de informações adicionais, como tipo e posição, para cada símbolo.

## Atividades Semanais

A cada semana, novas atividades e exercícios serão postados neste repositório, acompanhados de explicações e instruções para sua realização.

## Membros da Equipe
| [![](https://avatars.githubusercontent.com/fbressa)](https://github.com/fbressa) | [![](https://avatars.githubusercontent.com/Tiago1604)](https://github.com/Tiago1604) | [![](https://avatars.githubusercontent.com/isacostaf)](https://github.com/isacostaf) | [![](https://avatars.githubusercontent.com/johnaopedro)](https://github.com/johnaopedro) | [![](https://avatars.githubusercontent.com/JoaoPedro2206)](https://github.com/JoaoPedro2206) |
|:--:|:--:|:--:|:--:|:--:|
| [Filipe](https://github.com/fbressa) | [Tiago](https://github.com/Tiago1604) | [Isabelle da Costa](https://github.com/isacostaf) | [João Pedro](https://github.com/johnaopedro) | [João Pedro](https://github.com/JoaoPedro2206) |
