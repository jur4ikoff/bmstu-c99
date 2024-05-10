#!/bin/bash

path_to_script=$(dirname "$(readlink -f "$0")")

clang -std=c99 -Wall -Werror -Wvla -Wpedantic -Wextra -fno-omit-frame-pointer -fsanitize=undefined -g -c "$path_to_script"/main.c -o "$path_to_script"/main.o
clang -fsanitize=undefined -o "$path_to_script"/app.exe "$path_to_script"/main.o -lm
