#!/bin/bash

path_to_script=$(dirname "$(readlink -f "$0")")

clang -std=c99 -Wall -Werror -Wpedantic -Wextra -g  -fPIE -fno-omit-frame-pointer -fsanitize=memory -c "$path_to_script"/main.c -o "$path_to_script"/main.o
clang -fsanitize=memory -pie -o "$path_to_script"/app.exe "$path_to_script"/main.o -lm

