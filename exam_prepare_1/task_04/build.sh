#!/bin/bash

for file in *.c; do 
    base=$(basename -s .c "$file")
    gcc -std=c99 -Wall -Werror -Wvla -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -g -c ./"$file" -o ./"$base".o
done

gcc -o ./app.exe ./*.o -lm
