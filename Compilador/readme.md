
# Passo 1: Use o Bison para gerar o parser.tab.c e parser.tab.h
```
bison -d parser.y
```

# Passo 2: Use o Flex para gerar o lex.yy.c
```
flex lex.l
```

# Passo 3: Compile cada arquivo fonte para um arquivo objeto
```
gcc -c ast.c -o ast.o

gcc -c tabela.c -o tabela.o

gcc -c main.c -o main.o

gcc -c parser.tab.c -o parser.tab.o

gcc -c lex.yy.c -o lex.yy.o
```

# Passo 4: Vincule todos os arquivos objeto para criar o executável final
``` 
gcc ast.o tabela.o main.o parser.tab.o lex.yy.o -o compilador -lfl
```

# Para executar com o arquivo de exemplo
```
./compilador exemplo.txt
```

# Para executar no modo interativo
 ```
./compilador
```
