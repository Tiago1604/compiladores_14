# Relatório do Compilador **PYtoC**

## Pontos Positivos

- Integração entre **Flex** e **Bison** funcionando corretamente.
- O compilador detecta erros de sintaxe.
- Emite mensagens de erro com tratamento mínimo de falhas (demonstra a existência de uma estrutura de parsing).
- Reconhece palavras-chave do Python (indicando que o analisador léxico está mapeando tokens corretamente).
- Existem tokens definidos, regras gramaticais e lógica de conversão (ainda que incompleta).

---

## Dificuldades e Soluções

- **Parser, AST e Tabela de Símbolos:** Refinamos as regras gramaticais, incorporando mecanismos para construção e vinculação dinâmica dos nós, além de integrar a geração da tabela de símbolos durante a análise sintática. Isso permitiu maior flexibilidade e precisão na representação da estrutura do código-fonte.
- **Escopo:** Reestruturamos o planejamento do projeto, priorizando a implementação das funções críticas relacionadas ao controle de escopo, o que facilitou a identificação e resolução de conflitos entre variáveis e funções em diferentes contextos.

---

## Próximas Entregas

- Implementar a **AST** (Árvore Sintática Abstrata) e a **Tabela de Símbolos**.
- Aprimorar as mensagens de erro para maior clareza e precisão.
- Desenvolver testes automatizados para garantir a robustez do compilador.
- Adicionar verificação de **tipos** e **escopos**.
- Ampliar e refinar as regras gramaticais no **Bison**.
- Melhorar a análise semântica para maior fidelidade ao Python.

---

## Entregas Implementadas

- Implementação da **AST** (Árvore Sintática Abstrata) e da **Tabela de Símbolos**.
- Aprimoramento das mensagens de erro para maior clareza.
- Criação de testes automatizados para validação do compilador.
- Implementação da verificação de **tipos** e **escopos**.
- Expansão e refinamento das regras gramaticais no **Bison**.
- Melhoria da análise semântica para maior aderência ao Python.
- Parcial de **otimização** implementada.
- Parcial de **geração de código** implementada.