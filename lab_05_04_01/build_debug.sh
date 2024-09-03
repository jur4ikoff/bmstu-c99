#!/bin/bash

path_to_script=$(dirname "$(readlink -f "$0")")

for file in *.c; do
    base=$(basename -s .c "$file")
    # Поменял на gnu, чтобы работал unistd.h
    gcc -std=gnu99 -Wall -Werror -Wvla  -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -g -c "$path_to_script"/"$file" -o "$path_to_script"/"$base".o
done

gcc -o "$path_to_script"/app.exe "$path_to_script"/*.o -lm