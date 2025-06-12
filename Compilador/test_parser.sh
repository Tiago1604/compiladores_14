#!/bin/bash

COMPILADOR="./build/compiler"
TEST_DIR="tests"
SAIDA_DIR="saida"
mkdir -p "$SAIDA_DIR"

echo "==== Testes VÁLIDOS ===="
for entrada in "$TEST_DIR"/valid*.txt; do
    [ -f "$entrada" ] || continue
    saida="$SAIDA_DIR/$(basename "$entrada" .txt).c"
    $COMPILADOR "$entrada" "$saida" > /dev/null 2>&1
    if [ $? -eq 0 ]; then
        echo "✅ Aceitou corretamente: $(basename "$entrada")"
    else
        echo "❌ Rejeitou incorretamente: $(basename "$entrada")"
    fi
done

echo
echo "==== Testes INVÁLIDOS ===="
for entrada in "$TEST_DIR"/invalid*.txt; do
    [ -f "$entrada" ] || continue
    saida="$SAIDA_DIR/$(basename "$entrada" .txt).c"
    $COMPILADOR "$entrada" "$saida" > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        echo "✅ Rejeitou corretamente: $(basename "$entrada")"
    else
        echo "❌ Aceitou incorretamente: $(basename "$entrada")"
    fi
done
