#!/bin/bash

path_to_script=$(dirname "$(readlink -f "$0")")
# Проверка параметров
if [[ $# -lt 2 ]]; then
    exit 1
fi

file_input=$1
file_output_expect=$2

# Проверка существования файлов
if ! [[ -e "$file_input" ]] || ! [[ -e "$file_output_expect" ]]; then
    exit 1
fi


("$path_to_script"/../../app.exe < "$file_input") > "$path_to_script"/temp.txt
# Проверка что exitcode ненулевой
prog_res=$?
if [[ "$prog_res" != 0 ]]; then
    exit 1
fi

# Получение результата от компаратора
"$path_to_script"/comparator.sh "$path_to_script"/temp.txt "$file_output_expect" -r
result=$?
if [[ "$result" == 0 ]]; then
    exit 0
fi
exit 1