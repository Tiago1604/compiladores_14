CC=gcc
CFLAGS=-Wall -I.
DEPS=ast.h
OBJ=build/parser.tab.o build/lex.yy.o build/ast.o build/main.o build/tabela.o

build/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

build/compilador: $(OBJ)
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
	rm -f build/*.o build/parser.tab.c build/parser.tab.h build/lex.yy.c build/compilador

# Testes automáticos

test: build/compilador
	@bash test_runner.sh

# Compilação de Python para C
PyToC: build/compilador
	./build/compilador $(word 2,$(MAKECMDGOALS)) $(word 3,$(MAKECMDGOALS))

# Regra para ignorar argumentos desconhecidos
%:
	@:

.PHONY: clean test PyToC 