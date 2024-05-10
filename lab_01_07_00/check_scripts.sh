#!/bin/bash

# Проверка всех скриптов утилитой Shellcheck
# Проверка директории с основными скриптами
path_to_script=$(dirname "$(readlink -f "$0")")
files=$(find "$path_to_script" -name "*.sh" | sort)

for file in $files; do
    if [ -f "$file" ]; then
        shellcheck "$file"
    fi
done
# Проверка директории scripts
files=$(find "$path_to_script"/func_tests/scripts -name "*.sh" | sort)

for file in $files; do
    if [ -f "$file" ]; then
        shellcheck "$file"
    fi
done