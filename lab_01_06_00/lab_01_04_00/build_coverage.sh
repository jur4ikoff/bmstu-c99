#!/bin/bash

# Компиляция
path_to_script=$(dirname "$(readlink -f "$0")")
gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -Wvla -g --coverage -c "$path_to_script"/main.c -o "$path_to_script"/app.o 
compile_status=$?
# Линкование
gcc -o "$path_to_script"/app.exe "$path_to_script"/app.o -lm --coverage
link_status=$?

# Проверка успешности выполнения
if [[ "$compile_status" != 0 ]] || [[ "$link_status" != 0 ]]; then
    echo "Error while compiling 1"
    exit 1
else
    echo "Compiling success"
fi