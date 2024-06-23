#!/bin/bash

path_to_script=$(dirname "$(readlink -f "$0")")

clang -std=c99 -Wall -Werror -Wvla -Wpedantic -Wextra -g -fno-omit-frame-pointer -fsanitize=address -c "$path_to_script"/main.c -o "$path_to_script"/main.o
clang -fsanitize=address -o "$path_to_script"/app.exe "$path_to_script"/main.o -lm

