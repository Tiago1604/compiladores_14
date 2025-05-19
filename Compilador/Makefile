CC = gcc
FLEX = flex
BISON = bison

SRC = parser.y scanner.l ast.c tabela.c
OBJ = parser.tab.o lex.yy.o ast.o tabela.o
HDR = ast.h tabela.h tipos.h

# Alvo padrão
all: compilador

# Geração dos arquivos do Bison e Flex
parser.tab.c parser.tab.h: parser.y $(HDR)
	$(BISON) -d parser.y

lex.yy.c: scanner.l parser.tab.h
	$(FLEX) scanner.l

# Compilação dos objetos
parser.tab.o: parser.tab.c $(HDR)
	$(CC) -c parser.tab.c

lex.yy.o: lex.yy.c $(HDR)
	$(CC) -c lex.yy.c

ast.o: ast.c ast.h tipos.h
	$(CC) -c ast.c

tabela.o: tabela.c tabela.h
	$(CC) -c tabela.c

# Linkagem final
compilador: $(OBJ)
	$(CC) -o compilador $(OBJ)

# Alvo para rodar todos os testes do diretório tests/
test: compilador
	@echo "Executando testes em ./tests/"
	@for t in tests/*.txt; do \
		echo "==== Teste: $$t ===="; \
		./compilador < $$t; \
		echo ""; \
	done

clean:
	rm -f *.o *.tab.c *.tab.h lex.yy.c compilador

.PHONY: all clean test compilador