#!/bin/bash

path_to_script=$(dirname "$(readlink -f "$0")")

gcc -std=c99 -Wall -Werror -Wvla  -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -c "$path_to_script"/main.c -o "$path_to_script"/main.o -g
gcc -o "$path_to_script"/app.exe "$path_to_script"/main.o -lm
