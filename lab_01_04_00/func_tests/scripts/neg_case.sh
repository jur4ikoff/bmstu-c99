#!/bin/bash
path_to_script=$(dirname "$(readlink -f "$0")")

# Проверка параметров
if [[ $# -lt 1 ]]; then
    exit 1
fi

file_input=$1

# Проверка существования файла
if ! [[ -e "$file_input" ]]; then
    exit 1
fi


("$path_to_script"/../../app.exe < "$file_input") > /dev/null
prog_res=$?
# Проверка, что вывод ненулевой
if [[ "$prog_res" == 0 ]]; then
    exit 1
fi
exit 0