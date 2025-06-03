CC = gcc                    # Compilador C
FLEX = flex                 # Analisador léxico
BISON = bison               # Analisador sintático
CFLAGS = -Wall -Wextra      # Flags de compilação

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
	$(CC) $(CFLAGS) -c parser.tab.c

lex.yy.o: lex.yy.c $(HDR)
	$(CC) $(CFLAGS) -c lex.yy.c

ast.o: ast.c ast.h tipos.h
	$(CC) $(CFLAGS) -c ast.c

tabela.o: tabela.c tabela.h
	$(CC) $(CFLAGS) -c tabela.c

# Linkagem final
compilador: $(OBJ)
	$(CC) $(CFLAGS) -o compilador $(OBJ)

# Alvo para rodar todos os testes do diretório tests/
test: compilador
	@echo "Executando testes em ./tests/"
	@for t in tests/*.txt; do \
		echo "==== Teste: $$t ===="; \
		./compilador < $$t; \
		echo ""; \
	done

# Alvo para gerar bitcode
bitcode: compilador
	@echo "Gerando bitcode para testes em ./tests/"
	@mkdir -p output/bitcode
	@for t in tests/*.txt; do \
		base=$$(basename $$t .txt); \
		echo "==== Bitcode para: $$t ===="; \
		echo "#bitcode" | cat - $$t | ./compilador > output/bitcode/$$base.bitcode; \
		echo "Arquivo gerado: output/bitcode/$$base.bitcode"; \
	done

# Alvo para gerar código C
c: compilador
	@echo "Gerando código C para testes em ./tests/"
	@mkdir -p output/c
	@for t in tests/*.txt; do \
		base=$$(basename $$t .txt); \
		echo "==== Código C para: $$t ===="; \
		echo "#c" | cat - $$t | ./compilador > output/c/$$base.c; \
		echo "Arquivo gerado: output/c/$$base.c"; \
	done

# Limpa arquivos temporários e compilados
clean:
	rm -f *.o *.tab.c *.tab.h lex.yy.c compilador

# Define alvos que não são arquivos
.PHONY: all clean test compilador bitcode c