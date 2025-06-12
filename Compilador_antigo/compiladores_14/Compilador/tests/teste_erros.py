# Teste de erros para o compilador
# Este arquivo contém vários erros para testar as mensagens de erro

# Erro 1: Variável não declarada
print(x);

# Erro 2: Divisão por zero
int a = 10;
int b = 0;
a = a / b;

# Erro 3: Erro de sintaxe no print
print(;

# Erro 4: Erro de sintaxe no if
if (a > 5) {
    print(a);
} else print(b);

# Erro 5: Variável utilizada antes de inicialização
int c;
print(c);

# Erro 6: Caracteres inválidos
int $ = 5;

# Erro 7: Expressão mal formada
a = + * 5;

# Erro 8: Atribuição mal formatada
= 10;

# Erro 9: if mal formatado
if a > 5: print(a);

# Erro 10: Parênteses não balanceados
a = (5 + 3 * 2; 