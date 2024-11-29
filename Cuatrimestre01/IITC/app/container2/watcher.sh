#!/bin/sh

TOTAL_ARCHIVOS=31  # Cambiar según lo necesites
archivos_procesados=0

while true; do
    for file in /shared_memory/datos_*.txt; do
        if [ -f "$file" ]; then
            echo "Archivo encontrado: $file"
            /app/promedio "$file"
            rm "$file"
            archivos_procesados=$((archivos_procesados + 1))
        fi
    done

    # Si se han procesado todos los archivos esperados, detener el proceso
    if [ "$archivos_procesados" -ge "$TOTAL_ARCHIVOS" ]; then
        echo "Se han procesado los $TOTAL_ARCHIVOS archivos esperados. Terminando el proceso."
        exit 0
    fi

    sleep 1
done
