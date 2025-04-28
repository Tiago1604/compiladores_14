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
    - [ ] Apresentação no dia 30/04.  

- **Tarefas e Atividades**  
    1. [x] Finalizar as expressões regulares no Flex.  
    2. [x] Iniciar o parser no Bison.  
    3. [x] Testar analisador léxico e parser inicial.  
    4. [ ] Preparar slides/demonstrativo para o P1.  
    5. [x] Preencher o formulário do P1.  

---

### Sprint 3 (01/05 a 14/05)  
- **Objetivos Principais**  
    - [ ] Evoluir o analisador sintático com novas produções gramaticais.  
    - [ ] Iniciar a estrutura interna do compilador (árvore sintática, tabela de símbolos).  
    - [ ] Dar os primeiros passos na análise semântica.  

- **Principais Entregas**  
    - [ ] Parser com cobertura mais ampla da gramática.  
    - [ ] Estrutura de dados (AST e tabela de símbolos) definidas e parcialmente implementadas.  
    - [ ] Analisador semântico inicial identificando erros básicos.  

- **Tarefas e Atividades**  
    1. [ ] Estender as regras gramaticais no Bison.  
    2. [ ] Criar e popular a tabela de símbolos.  
    3. [ ] Construir a AST.  
    4. [ ] Implementar verificação de tipos e escopo simples.  

---

### Sprint 4 (15/05 a 04/06)  
- **Objetivos Principais**  
    - [ ] Concluir análise semântica principal.  
    - [ ] Implementar a geração de código intermediário.  
    - [ ] Preparar o ponto de controle P2.  

- **Principais Entregas**  
    - [ ] Analisador semântico robusto.  
    - [ ] Módulo de geração de código intermediário.  
    - [ ] Formulário do P2 preenchido até 02/06.  
    - [ ] Apresentação do ponto de controle P2 em 04/06.  

- **Tarefas e Atividades**  
    1. [ ] Refinar a análise semântica.  
    2. [ ] Criar gerador de código intermediário.  
    3. [ ] Configurar testes para instruções intermediárias.  
    4. [ ] Preparar apresentação P2.  

---

### Sprint 5 (05/06 a 25/06)  
- **Objetivos Principais**  
    - [ ] Introduzir e testar otimizações no código intermediário.  
    - [ ] Implementar a geração de código final.  
    - [ ] Realizar testes integrados e correções de bugs.  
    - [ ] Entregar o compilador final até 27/06.  

- **Principais Entregas**  
    - [ ] Módulo de otimização básico.  
    - [ ] Módulo de geração de código final.  
    - [ ] Compilador “rodando de ponta a ponta”.  

- **Tarefas e Atividades**  
    1. [ ] Projetar e implementar otimizações simples.  
    2. [ ] Criar tradutor final.  
    3. [ ] Testar em múltiplos programas de exemplo.  
    4. [ ] Entregar o compilador até 27/06.  

---

### Sprint 6 (26/06 a 09/07)  
- **Objetivos Principais**  
    - [ ] Realizar as entrevistas finais.  
    - [ ] Ajustar eventuais pendências do compilador.  
    - [ ] Concluir a documentação e finalizar a disciplina.  

- **Principais Entregas**  
    - [ ] Apresentação do compilador nas entrevistas.  
    - [ ] Correções finais e documentação completa.  

- **Tarefas e Atividades**  
    1. [ ] Entrevistas de entrega.  
    2. [ ] Corrigir issues identificadas.  
    3. [ ] Documentar o projeto.  