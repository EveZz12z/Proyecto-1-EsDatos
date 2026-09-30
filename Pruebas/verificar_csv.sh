#!/bin/bash
# Autor: Pablo Serón
# Verifica el archivo CSV y muestra los resultados.
# Para usarlo: ./verificar_csv.sh prueba.csv

ARCHIVO=${1:-prueba.csv}

echo "--- Primeras lineas ---"
head -4 "$ARCHIVO"

echo "--- Total de lineas (esperado: canciones + 1 del encabezado) ---"
wc -l < "$ARCHIVO"

echo "--- Ids repetidos (vacio = correcto) ---"
cut -d, -f1 "$ARCHIVO" | tail -n +2 | sort -n | uniq -d

echo "--- Canciones por genero ---"
cut -d, -f5 "$ARCHIVO" | tail -n +2 | sort | uniq -c