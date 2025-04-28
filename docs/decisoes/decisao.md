# Decisões Técnicas

Este documento descreve as principais decisões técnicas tomadas durante o desenvolvimento do compilador de Python para C, utilizando Flex e Bison.

---

## Linguagens e Ferramentas Utilizadas

- **Flex**: Ferramenta escolhida para a análise léxica, responsável por identificar tokens no código Python.
- **Bison**: Ferramenta utilizada para a análise sintática, responsável por validar a gramática e gerar a árvore sintática.
- **MkDocs**: Ferramenta para documentação do projeto, com o tema Material Design para uma interface moderna e organizada.

---

## Estrutura do Projeto

- **Organização Modular**: O projeto foi dividido em diretórios específicos para código-fonte, documentação, materiais de estudo e versões semanais.
- **Repositório Git**: Utilizado para controle de versão, com branches organizados para cada funcionalidade ou sprint.

---

## Configuração do Ambiente

- **Dependências**:
  - Flex e Bison devem estar instalados no sistema.
  - Em distribuições Linux baseadas em Debian/Ubuntu:
    ```bash
    sudo apt-get install flex bison
    ```
- **Compilação**:
  - O compilador é gerado utilizando o GCC:
    ```bash
    gcc -o compilador parser.tab.c lex.yy.c -lfl
    ```

---

## Decisões de Design

- **Subconjunto de Python**: O compilador suporta um subconjunto de Python, incluindo:
  - Estruturas condicionais (`if`, `else`).
  - Operações aritméticas e lógicas.
  - Declarações de variáveis simples.
- **Geração de Código C**: Durante a análise sintática, o código Python é traduzido diretamente para C, com suporte a estruturas equivalentes.

---

## Documentação

- **Estrutura da Documentação**:
  - Planejamento: Inclui cronograma, metodologia e planejamento das sprints.
  - Atas de Reunião: Registro das decisões tomadas em cada sprint.
  - Atividades Semanais: Relatórios de progresso semanais.
  - Ponto de Controle: Relatórios de marcos importantes no projeto.
- **Tema do MkDocs**:
  - Tema Material Design com suporte a modo claro e escuro.
  - Ícones personalizados para navegação.

---

## Fluxo de Trabalho

- **Branches no Git**:
  - `main`: Branch principal com as versões estáveis.
  - `feat/<nome>`: Branches específicas para cada funcionalidade ou tarefa.
- **Commits**:
  - Mensagens de commit seguem o padrão: `[Tipo]: Descrição breve`.

---

## Justificativas

- **Flex e Bison**: Escolhidos por serem ferramentas amplamente utilizadas para construção de compiladores, com boa integração e suporte à linguagem C.
- **MkDocs**: Escolhido para documentação devido à sua simplicidade e suporte a temas modernos.

---

Essas decisões técnicas foram tomadas para garantir que o projeto seja modular, eficiente e bem documentado, atendendo aos requisitos da disciplina e do compilador.