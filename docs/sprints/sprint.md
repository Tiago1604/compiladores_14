# Plano de Sprints para Compilador Python-C
## Informações Gerais

**Disciplina:** FGA0003 - Compiladores 1  
**Semestre:** 2025/1  
**Professor:** Dr. Sergio Antônio Andrade de Freitas  
**Projeto:** Compilador de Python para C  
**Entregas Principais:**
- Ponto de Controle P1: 30/04/2025
- Ponto de Controle P2: 04/06/2025
- Entrega Final: 27/06/2025
- Entrevistas Finais: 30/06/2025 e 02/07/2025

## Membros da Equipe
| [![](https://avatars.githubusercontent.com/fbressa)](https://github.com/fbressa) | [![](https://avatars.githubusercontent.com/Tiago1604)](https://github.com/Tiago1604) | [![](https://avatars.githubusercontent.com/isacostaf)](https://github.com/isacostaf) | [![](https://avatars.githubusercontent.com/johnaopedro)](https://github.com/johnaopedro) | [![](https://avatars.githubusercontent.com/JoaoPedro2206)](https://github.com/JoaoPedro2206) |
|:--:|:--:|:--:|:--:|:--:|
| [Filipe](https://github.com/fbressa) | [Tiago](https://github.com/Tiago1604) | [Isabelle da Costa](https://github.com/isacostaf) | [João Pedro](https://github.com/johnaopedro) | [João Pedro](https://github.com/JoaoPedro2206) |

## Visão Geral das Sprints

| Sprint | Período | Foco | Entregas | Status |
|--------|---------|------|----------|--------|
| 1 | 24/03 - 09/04 | Preparação e Análise Léxica | Analisador Léxico Funcional | ✅ Finalizada |
| 2 | 10/04 - 28/04 | Análise Sintática | Parser e P1 | ✅ Finalizada |
| 3 | 01/05 - 14/05 | Representação Interna | AST e Tabela de Símbolos | ✅ Finalizada  |
| 4 | 15/05 - 02/06 | Análise Semântica | Verificador Semântico e P2 | ✅ Finalizada  |
| 5 | 05/06 - 18/06 | Geração de Código | Gerador de Código C | ✅ Finalizada  |
| 6 | 19/06 - 27/06 | Refinamento e Testes | Compilador Completo | ✅ Finalizada  |
| 7 | 28/06 - 09/07 | Apresentação e Fechamento | Documentação Final e Entrevista | ✅ Finalizada  |

## Detalhamento das Sprints

### Sprint 1 (24/03 a 09/04)  
- **Objetivos Principais**  
    - [x] Formar as equipes e organizar o ambiente de trabalho (configurar repositórios, ferramentas, Flex, Bison etc.).  
        - **Responsáveis:** Filipe, Tiago, Isabelle, João Pedro Costa (johnaopedro), João Pedro  
    - [x] Definir a linguagem-fonte do compilador (sintaxe e semântica básica).  
        - **Responsáveis:** Filipe, Tiago, Isabelle, João Pedro Costa (johnaopedro), João Pedro  
    - [x] Elaborar a primeira versão da gramática formal (livre de contexto).  
        - **Responsáveis:** Filipe, Tiago, Isabelle, João Pedro Costa (johnaopedro), João Pedro  

- **Principais Entregas**  
    - [x] Documento inicial descrevendo a linguagem (tokens, estruturas, exemplos de código).  
        - **Responsáveis:** João Pedro Costa (johnaopedro) 
    - [x] Protótipo de gramática reconhecida pelo Bison (ainda não funcional, mas já planejada).  
        - **Responsáveis:** Filipe, Tiago, Isabelle, João Pedro Costa (johnaopedro), João Pedro 
    - [x] Ambiente configurado e testado (cada membro deve conseguir compilar e rodar um “hello world” do Flex/Bison).  
        - **Responsáveis:** Filipe, Tiago, Isabelle, João Pedro Costa (johnaopedro), João Pedro 

- **Tarefas e Atividades**  
    1. [x] Definir o escopo do compilador.  
        - **Responsáveis:** todos  
    2. [x] Configurar repositório e adicionar todos os membros.  
        - **Responsáveis:** todos  
    3. [x] Configurar ferramentas: Flex, Bison, compilador C/C++.  
        - **Responsáveis:** todos
    4. [x] Criar gramática inicial no Bison e arquivo de regras léxicas no Flex.  
        - **Responsáveis:** todos  
    5. [x] Revisar e atualizar a documentação do projeto.  
        - **Responsáveis:** todos  

---

### Sprint 2 (10/04 a 30/04)  
- **Objetivos Principais**  
    - [x] Concluir a análise léxica (Flex) e iniciar a análise sintática (Bison).  
        - **Responsáveis:** todos 
    - [x] Implementar identificação de tokens e testar o reconhecimento básico da linguagem.  
        - **Responsáveis:** todos
    - [x] Preparar o material para o Ponto de Controle P1.  
        - **Responsáveis:** todos  

- **Principais Entregas**  
    - [x] Analisador léxico funcional (arquivo .l completo).  
        - **Responsáveis:** Filipe, Tiago, Isabelle, João Pedro Costa (johnaopedro), João Pedro
    - [x] Primeiras regras sintáticas implementadas no arquivo .y.  
        - **Responsáveis:** João Pedro Costa (johnaopedro)  
    - [x] Formulário de apresentação do P1 preenchido até 28/04.  
        - **Responsáveis:** João Pedro Costa (johnaopedro)  
    - [ ] Apresentação no dia 30/04.  
        - **Responsáveis:** Filipe, Tiago, Isabelle, João Pedro Costa (johnaopedro), João Pedro

- **Tarefas e Atividades**  
    1. [x] Finalizar as expressões regulares no Flex.  
        - **Responsáveis:** João Pedro Costa (johnaopedro)  
    2. [x] Iniciar o parser no Bison.  
        - **Responsáveis:** João Pedro Costa (johnaopedro)  
    3. [x] Testar analisador léxico e parser inicial.  
        - **Responsáveis:** João Pedro Costa (johnaopedro)  
    4. [ ] Preparar slides/demonstrativo para o P1.  
        - **Responsáveis:** Professor providenciou.
    5. [x] Preencher o formulário do P1.  
        - **Responsáveis:** João Pedro Costa (johnaopedro)  

---

### Sprint 3 (01/05 a 14/05)  
- **Objetivos Principais**  
    - [x] Evoluir o analisador sintático com novas produções gramaticais.  
        - **Responsáveis:** Tiago, Isabelle 
    - [x] Iniciar a estrutura interna do compilador (árvore sintática, tabela de símbolos).  
        - **Responsáveis:** Filipe, João Pedro 
    - [x] Dar os primeiros passos na análise semântica.  
        - **Responsáveis:** Tiago, João Pedro Costa (johnaopedro)  

- **Principais Entregas**  
    - [x] Parser com cobertura mais ampla da gramática.  
        - **Responsáveis:** Tiago, Isabelle 
    - [x] Estrutura de dados (AST e tabela de símbolos) definidas e parcialmente implementadas.  
        - **Responsáveis:** Filipe, João Pedro 
    - [x] Analisador semântico inicial identificando erros básicos.  
        - **Responsáveis:** Tiago, João Pedro Costa (johnaopedro)  

- **Tarefas e Atividades**  
    1. [x] Estender as regras gramaticais no Bison.  
        - **Responsáveis:** Tiago, Isabelle
    2. [x] Criar e popular a tabela de símbolos.  
        - **Responsáveis:** Filipe, João Pedro, João Pedro Costa (johnaopedro) 
    3. [x] Construir a AST.  
        - **Responsáveis:** Filipe, João Pedro, João Pedro Costa (johnaopedro) 
    4. [x] Implementar verificação de tipos e escopo simples.  
        - **Responsáveis:** Tiago, João Pedro Costa (johnaopedro)  
    5. [x] Revisar e atualizar a documentação do projeto.  
        - **Responsáveis:** todos

---

### Sprint 4 (15/05 a 04/06)  
- **Objetivos Principais**  
    - [x] Concluir análise semântica principal.  
        - **Responsáveis:** todos  
    - [x] Implementar a geração de código intermediário.  
        - **Responsáveis:** todos  
    - [x] Preparar o ponto de controle P2.  
        - **Responsáveis:** todos  

- **Principais Entregas**  
    - [x] Analisador semântico robusto.  
        - **Responsáveis:** todos  
    - [x] Módulo de geração de código intermediário.  
        - **Responsáveis:** todos  
    - [x] Formulário do P2 preenchido até 02/06.  
        - **Responsáveis:** todos  
    - [x] Apresentação do ponto de controle P2 em 04/06.  
        - **Responsáveis:** todos  

- **Tarefas e Atividades**  
    1. [x] Refinar a análise semântica.  
        - **Responsáveis:** todos  
    2. [x] Criar gerador de código intermediário.  
        - **Responsáveis:** todos  
    3. [x] Configurar testes para instruções intermediárias.  
        - **Responsáveis:** todos  
    4. [x] Preparar apresentação P2.  
        - **Responsáveis:** todos  

---

### Sprint 5 (05/06 a 25/06)  
- **Objetivos Principais**  
    - [x] Introduzir e testar otimizações no código intermediário.  
        - **Responsáveis:** todos  
    - [x] Implementar a geração de código final.  
        - **Responsáveis:** todos  
    - [x] Realizar testes integrados e correções de bugs.  
        - **Responsáveis:** todos  
    - [x] Entregar o compilador final até 27/06.  
        - **Responsáveis:** todos  

- **Principais Entregas**  
    - [x] Módulo de otimização básico.  
        - **Responsáveis:** todos  
    - [x] Módulo de geração de código final.  
        - **Responsáveis:** todos  
    - [x] Compilador “rodando de ponta a ponta”.  
        - **Responsáveis:** todos  

- **Tarefas e Atividades**  
    1. [x] Projetar e implementar otimizações simples.  
        - **Responsáveis:** todos  
    2. [x] Criar tradutor final.  
        - **Responsáveis:** todos  
    3. [x] Testar em múltiplos programas de exemplo.  
        - **Responsáveis:** todos  
    4. [x] Entregar o compilador até 27/06.  
        - **Responsáveis:** todos  

---

### Sprint 6 (26/06 a 09/07)  
- **Objetivos Principais**  
    - [ ] Realizar as entrevistas finais.  
        - **Responsáveis:** todos  
    - [x] Ajustar eventuais pendências do compilador.  
        - **Responsáveis:** todos  
    - [x] Concluir a documentação e finalizar a disciplina.  
        - **Responsáveis:** todos  

- **Principais Entregas**  
    - [ ] Apresentação do compilador nas entrevistas.  
        - **Responsáveis:** todos  
    - [ ] Correções finais e documentação completa.  
        - **Responsáveis:** todos  

- **Tarefas e Atividades**  
    1. [ ] Entrevistas de entrega.  
        - **Responsáveis:** todos  
    2. [ ] Corrigir issues identificadas.  
        - **Responsáveis:** todos  
    3. [ ] Documentar o projeto.  
        - **Responsáveis:** todos  