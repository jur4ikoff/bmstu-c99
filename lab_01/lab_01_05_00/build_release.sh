#!/bin/bash

path_to_script=$(dirname "$(readlink -f "$0")")

gcc -std=c99 -Wall -Wvla -Werror -c "$path_to_script"/main.c -o "$path_to_script"/main.o
gcc -o "$path_to_script"/app.exe "$path_to_script"/main.o -lm