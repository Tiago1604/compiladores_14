CC = gcc                    # Compilador C
FLEX = flex                 # Analisador léxico
BISON = bison               # Analisador sintático

# Arquivos fonte
SRC = parser.y scanner.l ast.c tabela.c
OBJ = parser.tab.o lex.yy.o ast.o tabela.o  # Arquivos objeto
HDR = ast.h tabela.h tipos.h                # Arquivos de cabeçalho

# Alvo padrão
all: compilador

# Geração dos arquivos do Bison e Flex
parser.tab.c parser.tab.h: parser.y $(HDR)
	$(BISON) -d parser.y              # Gera arquivo C e cabeçalho

lex.yy.c: scanner.l parser.tab.h
	$(FLEX) scanner.l                 # Gera código-fonte do scanner

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

# Limpa arquivos temporários e compilados
clean:
	rm -f *.o *.tab.c *.tab.h lex.yy.c compilador

# Define alvos que não são arquivos
.PHONY: all clean test compilador