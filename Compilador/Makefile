# Makefile para o Compilador

# Definição de variáveis
CC=gcc
CFLAGS=-Wall -I.
DEPS=ast.h
OBJ=build/parser.tab.o build/lex.yy.o build/ast.o build/main.o build/tabela.o

# Regra padrão
all: build/compilador

# Regra padrão para compilação de arquivos .c
build/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Regra para gerar o executável final
build/compilador: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# Regra para gerar o analisador léxico com flex
build/lex.yy.c: scanner.l
	@mkdir -p build
	flex -o build/lex.yy.c scanner.l

# Regra para gerar o analisador sintático com bison
build/parser.tab.c build/parser.tab.h: parser.y
	@mkdir -p build
	bison -d -b build/parser parser.y

# Regra específica para compilar a tabela de símbolos
build/tabela.o: tabela.c tabela.h
	$(CC) -c -o build/tabela.o tabela.c -Wall -I.

# Regra para limpar arquivos gerados
clean:
	rm -rf build/
	rm -f saida/saida.c
	rm -rf tests/saida_tests/

# Testes do parser (válidos/inválidos)
test-parser: build/compilador
	@echo "=== Testando Parser ==="
	@bash test_parser.sh

# Executa todos os testes mostrando saídas
test: build/compilador
	@echo "=== Executando Testes ==="
	@bash test_runner.sh

# Regra para compilar código Python para C
PyToC: build/compilador create_dirs
	@echo "=== Convertendo Python para C ==="
	@echo "Arquivo de entrada: entrada/entrada.py"
	@echo "Arquivo de saída: saida/saida.c"
	@echo "=== Iniciando Compilação ==="
	./build/compilador entrada/entrada.py saida/saida.c
	@echo "=== Compilação Finalizada ==="

# Regra para criar os diretórios necessários
create_dirs:
	@mkdir -p entrada saida build

.PHONY: all clean test test-parser PyToC create_dirs