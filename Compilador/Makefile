CC=gcc
CFLAGS=-Wall -I.
DEPS=ast.h
OBJ=build/parser.tab.o build/lex.yy.o build/ast.o build/main.o build/tabela.o

build/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

build/compiler: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

build/lex.yy.c: scanner.l
	@mkdir -p build
	flex -o build/lex.yy.c scanner.l

build/parser.tab.c build/parser.tab.h: parser.y
	@mkdir -p build
	bison -d -b build/parser parser.y

build/tabela.o: tabela.c tabela.h
	$(CC) -c -o build/tabela.o tabela.c -Wall -I.

clean:
	rm -f build/*.o build/parser.tab.c build/parser.tab.h build/lex.yy.c build/compiler

# Testes automáticos

test: build/compiler
	@bash test_runner.sh

.PHONY: clean test 