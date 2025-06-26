#!/bin/bash

# Caminhos dos testes e saídas
TEST_DIR="tests"
SAIDA_DIR="saida"
COMPILADOR="build/compilador"

# Garante que o diretório de saída existe
mkdir -p "$SAIDA_DIR"

# Para cada arquivo de entrada .txt ou .py
encontrou=0
for entrada in "$TEST_DIR"/*.txt "$TEST_DIR"/*.py; do
    [ -f "$entrada" ] || continue
    encontrou=1
    nome=$(basename "$entrada" | sed 's/\.[^.]*$//')
    saida="$SAIDA_DIR/$nome.c"
    echo "Rodando teste: $nome"
    "$COMPILADOR" "$entrada" "$saida"
    if [ $? -ne 0 ]; then
        echo "❌ Erro no teste $nome"
    else
        echo "✅ Sucesso no teste $nome"
    fi
    echo "-----------------------------"
done

if [ $encontrou -eq 0 ]; then
    echo "Nenhum teste encontrado em $TEST_DIR."
fi
