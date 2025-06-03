# Plano de Sprints para Compilador Python-Lua
## Informações Gerais

**Disciplina:** FGA0003 - Compiladores 1  
**Semestre:** 2025/1  
**Professor:** Dr. Sergio Antônio Andrade de Freitas  
**Projeto:** Compilador de Python para Lua  
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
| 3 | 01/05 - 14/05 | Representação Interna | AST e Tabela de Símbolos | 🔄 Iniciada |
| 4 | 15/05 - 02/06 | Análise Semântica | Verificador Semântico e P2 | 🟡 Não iniciado |
| 5 | 05/06 - 18/06 | Geração de Código | Gerador de Código Lua | 🟡 Não iniciado |
| 6 | 19/06 - 27/06 | Refinamento e Testes | Compilador Completo | 🟡 Não iniciado |
| 7 | 28/06 - 09/07 | Apresentação e Fechamento | Documentação Final e Entrevista | 🟡 Não iniciado |

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
        - **Responsáveis:** Filipe, Tiago, Isabelle, João Pedro Costa (johnaopedro), João Pedro  
    2. [x] Configurar repositório e adicionar todos os membros.  
        - **Responsáveis:** Tiago  
    3. [x] Configurar ferramentas: Flex, Bison, compilador C/C++.  
        - **Responsáveis:** Filipe, Tiago, Isabelle, João Pedro Costa (johnaopedro), João Pedro
    4. [x] Criar gramática inicial no Bison e arquivo de regras léxicas no Flex.  
        - **Responsáveis:** Filipe, Tiago, Isabelle, João Pedro Costa (johnaopedro), João Pedro  
    5. [x] Revisar e atualizar a documentação do projeto.  
        - **Responsáveis:** João Pedro Costa (johnaopedro)  

---

### Sprint 2 (10/04 a 30/04)  
- **Objetivos Principais**  
    - [x] Concluir a análise léxica (Flex) e iniciar a análise sintática (Bison).  
        - **Responsáveis:** Filipe, Tiago, Isabelle, João Pedro Costa (johnaopedro), João Pedro 
    - [x] Implementar identificação de tokens e testar o reconhecimento básico da linguagem.  
        - **Responsáveis:** Filipe, Tiago, Isabelle, João Pedro Costa (johnaopedro), João Pedro 
    - [x] Preparar o material para o Ponto de Controle P1.  
        - **Responsáveis:** João Pedro Costa (johnaopedro)  

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
    - [ ] Evoluir o analisador sintático com novas produções gramaticais.  
        - **Responsáveis:** Tiago, Isabelle 
    - [ ] Iniciar a estrutura interna do compilador (árvore sintática, tabela de símbolos).  
        - **Responsáveis:** Filipe, João Pedro 
    - [ ] Dar os primeiros passos na análise semântica.  
        - **Responsáveis:** Tiago, João Pedro Costa (johnaopedro)  

- **Principais Entregas**  
    - [ ] Parser com cobertura mais ampla da gramática.  
        - **Responsáveis:** Tiago, Isabelle 
    - [ ] Estrutura de dados (AST e tabela de símbolos) definidas e parcialmente implementadas.  
        - **Responsáveis:** Filipe, João Pedro 
    - [ ] Analisador semântico inicial identificando erros básicos.  
        - **Responsáveis:** Tiago, João Pedro Costa (johnaopedro)  

- **Tarefas e Atividades**  
    1. [ ] Estender as regras gramaticais no Bison.  
        - **Responsáveis:** Tiago, Isabelle
    2. [ ] Criar e popular a tabela de símbolos.  
        - **Responsáveis:** Filipe, João Pedro, João Pedro Costa (johnaopedro) 
    3. [ ] Construir a AST.  
        - **Responsáveis:** Filipe, João Pedro, João Pedro Costa (johnaopedro) 
    4. [ ] Implementar verificação de tipos e escopo simples.  
        - **Responsáveis:** Tiago, João Pedro Costa (johnaopedro)  
    5. [ ] Revisar e atualizar a documentação do projeto.  
        - **Responsáveis:** João Pedro Costa (johnaopedro)