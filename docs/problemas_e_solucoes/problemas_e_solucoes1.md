# Problemas Encontrados e Soluções Adotadas

Este documento descreve os principais problemas enfrentados durante o desenvolvimento do compilador de Python para C e as soluções adotadas para resolvê-los.

---

## Problemas e Soluções

### 1. Dificuldade na Integração entre Flex e Bison
- **Problema**: Inicialmente, houve dificuldades para integrar o analisador léxico (Flex) com o analisador sintático (Bison), especialmente na definição e uso dos tokens.
- **Solução**: Foi realizada uma revisão detalhada da documentação de Flex e Bison. Além disso, utilizamos o arquivo de cabeçalho gerado pelo Bison (`parser.tab.h`) para garantir que os tokens definidos no Flex fossem reconhecidos corretamente pelo Bison.

---
### 2. Dificuldade na Integração entre Flex e Bison no MAC
- **Problema**: Inicialmente, houve dificuldades para integrar o analisador léxico (Flex) com o analisador sintático (Bison), especialmente no sistema operacional macOS.
- **Solução**: Foi realizada uma revisão detalhada da documentação de Flex e Bison. Além disso, utilizamos o arquivo de cabeçalho gerado pelo Bison para garantir o funcionamento.

---
### 3. Erro ao Gerar o Código com GCC
- **Problema**: Durante a compilação do projeto com GCC, surgiram erros relacionados a funções não definidas ou conflitos de tipos.
- **Solução**: Verificamos as dependências e incluímos a biblioteca `-lfl` no comando de compilação para resolver os erros relacionados ao Flex. O comando final ficou assim:
  ```bash
  gcc -o compilador parser.tab.c lex.yy.c -lfl

---
### 4. Organização do Repositório
- **Problema**: A estrutura inicial do repositório estava desorganizada, dificultando a localização de arquivos e o controle de versões.
- **Solução**: Reestruturamos o repositório, separando os arquivos em diretórios específicos, como Compilador/, docs/, e Estudo/. Também adotamos o uso de branches no Git para organizar o fluxo de trabalho.

---
### 5. Configurar os Condicionais no Léxico e Bison
- **Problema**: Houve dificuldades para implementar condicionais no analisador léxico e no analisador sintático, especialmente na definição de regras que dependem de estados específicos.
- **Solução**: Foram utilizados ferramentas para auxílio.

---