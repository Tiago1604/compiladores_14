# Guia Técnico do Compilador Python -> C

## 1. Visão Geral
Este compilador converte um subconjunto da linguagem Python para código C. Foi desenvolvido usando:
- Flex (para análise léxica)
- Bison (para análise sintática)
- Geração de código intermediário através de uma AST (Árvore Sintática Abstrata).

## 2. Estrutura do Projeto

Compilador/

├── scanner.l # Analisador léxico (Flex)

├── parser.y # Analisador sintático (Bison)

├── ast.h/c # Definição e manipulação da AST

├── tabela.h/c # Tabela de símbolos

├── main.c # Programa principal

├── entrada/ # Diretório para arquivos Python de entrada

├── saida/ # Diretório para arquivos C gerados

└── tests/ # Testes do compilador

## 3. Funcionalidades Suportadas

### 3.1. Tipos de Dados
- Inteiros (`int`)
- Ponto flutuante (`float`)
- Identificadores (nomes de variáveis)

### 3.2. Estruturas de Controle
- `if/else`
- `while`
- `for` com `range`

### 3.3. Funções
- Definição de funções (`def`)
- Chamadas de função
- `print()`

### 3.4. Operadores
- Aritméticos: `+`, `-`, `*`, `/`
- Comparação: `>`, `<`, `>=`, `<=`, `==`, `!=`
- Atribuição: `=`

## 4. Limitações e Restrições

### 4.1. Tipos
- Não suporta strings
- Não suporta listas, tuplas ou dicionários
- Não suporta tipos booleanos explícitos

### 4.2. Funções
- Não suporta funções aninhadas
- Não suporta argumentos com valor padrão
- Não suporta retorno de múltiplos valores

### 4.3. Estruturas de Controle
- Não suporta `elif`
- Não suporta `break` e `continue`
- `for` só funciona com `range`

### 4.4. Outras Limitações
- Não suporta comentários (#)
- Não suporta importação de módulos
- Não suporta classes e orientação a objetos

## 5. Casos que Geram Erro

### 5.1. Erros de Sintaxe
- Indentação incorreta
- Falta de dois pontos (`:`) após `if`, `else`, `for`, `while`, `def`
- Parênteses não fechados
- Operadores inválidos ou mal formados

### 5.2. Erros de Semântica
- Uso de variável não declarada
- Operações entre tipos incompatíveis
- Chamada de função com número incorreto de argumentos
- Redefinição de função
- Uso de função como variável

### 5.3. Exemplos de Código que Geram Erro
```python
# Erro: Comentários não são suportados
x = 10  # isso gerará erro

# Erro: Strings não são suportadas
nome = "João"

# Erro: Operação com tipos incompatíveis
x = 10 + "20"

# Erro: Função aninhada
def externa():
    def interna():
        pass

# Erro: elif não é suportado
if x > 0:
    print(x)
elif x < 0:
    print(-x)

# Erro: break não é suportado
while x > 0:
    if x == 5:
        break

# Erro: for sem range
for x in [1,2,3]:
    print(x)
```

## 6. Uso do Compilador

### 6.1. Comandos Make
- `make`: Compila o projeto
- `make clean`: Limpa arquivos gerados
- `make test`: Executa testes mostrando saída no terminal
- `make test-parser`: Testa validação sintática
- `make PyToC`: Converte entrada/entrada.py para saida/saida.c

### 6.2. Processo de Compilação
1. Análise Léxica (scanner.l)
   - Identifica tokens
   - Detecta caracteres inválidos
   - Conta linhas para mensagens de erro

2. Análise Sintática (parser.y)
   - Verifica estrutura do programa
   - Constrói AST
   - Gerencia erros sintáticos

3. Análise Semântica (ast.c, tabela.c)
   - Verifica tipos
   - Gerencia escopo
   - Valida operações

4. Geração de Código (ast.c)
   - Gera código C equivalente
   - Gerencia declarações de variáveis
   - Traduz estruturas de controle

## 7. Bibliotecas e Ferramentas

### 7.1. Flex (scanner.l)
- Usado para análise léxica
- Gera arquivo lex.yy.c
- Define padrões de tokens usando expressões regulares

### 7.2. Bison (parser.y)
- Usado para análise sintática
- Gera parser.tab.c e parser.tab.h
- Define gramática livre de contexto

### 7.3. Biblioteca Padrão C
- stdio.h: Entrada/saída
- stdlib.h: Alocação de memória
- string.h: Manipulação de strings

## 8. Exemplos de Código Válido

### 8.1. Estruturas de Controle
```python
# If-else simples
x = 10
if x > 0:
    print(x)
else:
    print(-x)

# While com contador
i = 0
while i < 5:
    print(i)
    i = i + 1

# For com range
for i in range(5):
    print(i)
```

### 8.2. Funções
```python
def soma(a, b):
    return a + b

x = 10
y = 20
resultado = soma(x, y)
print(resultado)
```

### 8.3. Operações Aritméticas
```python
a = 10
b = 20.5
soma = a + b
mult = a * b
div = b / a
sub = b - a
```

## 9. Dicas de Uso
1. Sempre verifique se o arquivo entrada.py está na pasta entrada/
2. Examine a saída do compilador para mensagens de erro detalhadas
3. Use `make test` para verificar se o compilador está funcionando corretamente
4. Mantenha o código Python dentro das limitações documentadas
5. Verifique a AST gerada para entender como o código está sendo interpretado

## 10. Escopo do Compilador Python -> C

### 1. Tipos de Variáveis Suportados
- Inteiros (int)
  - Exemplo: `x = 10`
  - Números inteiros positivos e negativos
- Ponto Flutuante (float)
  - Exemplo: `y = 2.5`
  - Números decimais

Não Suporta:
- Strings
- Booleanos (True/False), Listas, Dicionários, Tuplas
    - Seria em bibliotecas então fugia do escopo basico da linguagem

### 2. Operadores

#### 2.1 Operadores Aritméticos
- `+` (soma)
- `-` (subtração)
- `*` (multiplicação)
- `/` (divisão)

Não Suporta:
- `**` (potência)
- `//` (divisão inteira)
- `%` (módulo)

#### 2.2 Operadores de Comparação
- `>` (maior que)
- `<` (menor que)
- `>=` (maior ou igual)
- `<=` (menor ou igual)
- `==` (igual)
- `!=` (diferente)

Não Suporta:
- `is`
- `is not`
- `in`
- `not in`

#### 2.3 Operadores de Atribuição
- `=` (atribuição simples)

Não Suporta:
- `++`
- `--`
- `+=`
- `-=`
- `*=`
- `/=`

### 3. Estruturas de Controle

#### 3.1 If-Else
```python
if condição:
    # código
else:
    # código
```

Não Suporta:
- `elif`
- Operadores lógicos (`and`, `or`, `not`)

#### 3.2 While
```python
while condição:
    # código
```
Não Suporta:
- `break`
- `continue`

#### 3.3 For
```python
for i in range(valor):
    # código
```
- O `in` funciona apenas no metodo for.

Não Suporta:
- `for` com listas
- `for` com strings
- `range` com comparação
- `range` com início e fim
- `break`
- `continue`

### 4. Funções

#### 4.1 Definição de Funções
```python
def nome_funcao(param1, param2):
    # código
    return valor
```

Não Suporta:
- Parâmetros com valor padrão
- Parâmetros nomeados
- Retorno múltiplo
- Funções aninhadas
- Funções lambda
- Decoradores

#### 4.2 Funções Built-in
- `print()`
  - Aceita apenas uma expressão ou string
  - Exemplo: `print(x)`, `print(x + y)` ou `print("Hello, World!")`

Não Suporta:
- `input()`
- `len()`
- `range()` (exceto no for)
- E nem `print("oi")`

### 5. Escopo de Variáveis
Paricalamente Suporta:
- Variáveis globais
- Variáveis locais em funções
Obs: Não há mensagens de erro associadas.

Não Suporta:
- Variáveis nonlocal
- Variáveis em funções aninhadas
- Closure

### 6. Outros Recursos

#### 6.1 Indentação
- Reconhece indentação para blocos de código
- Deve ser consistente dentro do mesmo bloco (Parcialmente Suporta)

#### 6.2 Expressões
- Expressões aritméticas simples
- Expressões de comparação simples
- Chamadas de função

Não Suporta:
- Expressões com operadores lógicos
- Expressões condicionais (ternário)
- Expressões com múltiplos operadores lógicos

#### 6.3 Comentários
Não Suporta:
- Comentários com `#`
- Docstrings
- Comentários multilinha
