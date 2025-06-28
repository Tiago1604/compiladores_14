# Planejamento das Sprints

Este documento apresenta o planejamento detalhado das sprints para o desenvolvimento de um compilador como parte da disciplina de Compiladores. O objetivo é organizar as atividades, definir entregas e acompanhar o progresso do projeto ao longo do semestre. Cada sprint possui objetivos claros, entregas específicas e tarefas distribuídas para garantir o cumprimento dos prazos e a qualidade do trabalho.

O planejamento está dividido em seis sprints, cobrindo desde a formação das equipes e configuração do ambiente até a entrega final do compilador e sua documentação. A seguir, são descritas as metas e atividades de cada sprint.

### Sprint 1 (24/03 a 09/04)  
- **Objetivos Principais**  
    - [x] Formar as equipes e organizar o ambiente de trabalho (configurar repositórios, ferramentas, Flex, Bison etc.).  
    - [x] Definir a linguagem-fonte do compilador (sintaxe e semântica básica).  
    - [x] Elaborar a primeira versão da gramática formal (livre de contexto).  

- **Principais Entregas**  
    - [x] Documento inicial descrevendo a linguagem (tokens, estruturas, exemplos de código).  
    - [x] Protótipo de gramática reconhecida pelo Bison (ainda não funcional, mas já planejada).  
    - [x] Ambiente configurado e testado (cada membro deve conseguir compilar e rodar um “hello world” do Flex/Bison).  

- **Tarefas e Atividades**  
    1. [x] Definir o escopo do compilador.  
    2. [x] Configurar repositório e adicionar todos os membros.  
    3. [x] Configurar ferramentas: Flex, Bison, compilador C/C++.  
    4. [x] Criar gramática inicial no Bison e arquivo de regras léxicas no Flex.  
    5. [x] Revisar e atualizar a documentação do projeto.  

---

### Sprint 2 (10/04 a 30/04)  
- **Objetivos Principais**  
    - [x] Concluir a análise léxica (Flex) e iniciar a análise sintática (Bison).  
    - [x] Implementar identificação de tokens e testar o reconhecimento básico da linguagem.  
    - [x] Preparar o material para o Ponto de Controle P1.  

- **Principais Entregas**  
    - [x] Analisador léxico funcional (arquivo .l completo).  
    - [x] Primeiras regras sintáticas implementadas no arquivo .y.  
    - [x] Formulário de apresentação do P1 preenchido até 28/04.  
    - [x] Apresentação no dia 30/04.  

- **Tarefas e Atividades**  
    1. [x] Finalizar as expressões regulares no Flex.  
    2. [x] Iniciar o parser no Bison.  
    3. [x] Testar analisador léxico e parser inicial.  
    4. [x] Preparar slides/demonstrativo para o P1.  
    5. [x] Preencher o formulário do P1.  

---

### Sprint 3 (01/05 a 14/05)  
- **Objetivos Principais**  
    - [x] Evoluir o analisador sintático com novas produções gramaticais.  
    - [x] Iniciar a estrutura interna do compilador (árvore sintática, tabela de símbolos).  
    - [x] Dar os primeiros passos na análise semântica.  

- **Principais Entregas**  
    - [x] Parser com cobertura mais ampla da gramática.  
    - [x] Estrutura de dados (AST e tabela de símbolos) definidas e parcialmente implementadas.  
    - [x] Analisador semântico inicial identificando erros básicos.  

- **Tarefas e Atividades**  
    1. [x] Estender as regras gramaticais no Bison.  
    2. [x] Criar e popular a tabela de símbolos.  
    3. [x] Construir a AST.  
    4. [x] Implementar verificação de tipos e escopo simples.  

---

### Sprint 4 (15/05 a 04/06)  
- **Objetivos Principais**  
    - [x] Concluir análise semântica principal.  
    - [x] Implementar a geração de código intermediário.  
    - [x] Preparar o ponto de controle P2.  

- **Principais Entregas**  
    - [x] Analisador semântico robusto.  
    - [x] Módulo de geração de código intermediário.  
    - [x] Formulário do P2 preenchido até 02/06.  
    - [x] Apresentação do ponto de controle P2 em 04/06.  

- **Tarefas e Atividades**  
    1. [x] Refinar a análise semântica.  
    2. [x] Criar gerador de código intermediário.  
    3. [x] Configurar testes para instruções intermediárias.  
    4. [x] Preparar apresentação P2.  

---

### Sprint 5 (05/06 a 25/06)  
- **Objetivos Principais**  
    - [ ] Introduzir e testar otimizações no código intermediário.  
    - [x] Implementar a geração de código final.  
    - [x] Realizar testes integrados e correções de bugs.  
    - [x] Entregar o compilador final até 27/06.  

- **Principais Entregas**  
    - [ ] Módulo de otimização básico.  
    - [x] Módulo de geração de código final.  
    - [x] Compilador “rodando de ponta a ponta”.  

- **Tarefas e Atividades**  
    1. [x] Projetar e implementar otimizações simples.  
    2. [x] Criar tradutor final.  
    3. [x] Testar em múltiplos programas de exemplo.  
    4. [x] Entregar o compilador até 27/06.  

---

### Sprint 6 (26/06 a 09/07)  
- **Objetivos Principais**  
    - [ ] Realizar as entrevistas finais.  
    - [x] Ajustar eventuais pendências do compilador.  
    - [x] Concluir a documentação e finalizar a disciplina.  

- **Principais Entregas**  
    - [ ] Apresentação do compilador nas entrevistas.  
    - [ ] Correções finais e documentação completa.  

- **Tarefas e Atividades**  
    1. [ ] Entrevistas de entrega.  
    2. [ ] Corrigir issues identificadas.  
    3. [ ] Documentar o projeto.