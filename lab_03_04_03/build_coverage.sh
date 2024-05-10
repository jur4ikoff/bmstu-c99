#!/bin/bash

# Компиляция
path_to_script=$(dirname "$(readlink -f "$0")")

# Компиляция 
for file in *.c; do
    base=$(basename -s .c "$file")
    gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -Wvla -g --coverage -c "$path_to_script"/"$file" -o "$path_to_script"/"$base".o 
    compile_status=$?
    if [[ "$compile_status" != 0 ]]; then
        echo "Error while compiling"
        exit 1
    fi
done

# Линковка
gcc -o "$path_to_script"/app.exe "$path_to_script"/*.o -lm --coverage
link_status=$?

# Проверка успешности выполнения
if [[ "$link_status" != 0 ]]; then
    echo "Error while linking"
    exit 1
fi
echo "Compiling success"
