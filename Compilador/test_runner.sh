#!/bin/bash

# Caminho dos testes
TEST_DIR="tests"
COMPILADOR="build/compilador"

# Para cada arquivo de entrada .txt ou .py
encontrou=0
for entrada in "$TEST_DIR"/*.txt "$TEST_DIR"/*.py; do
    [ -f "$entrada" ] || continue
    encontrou=1
    nome=$(basename "$entrada" | sed 's/\.[^.]*$//')
    echo "Rodando teste: $nome"
    "$COMPILADOR" "$entrada" /dev/stdout
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
