#!/bin/bash

# 1 флаг - путь до файл с данными для ввода, 2 флаг - путь до файла с ожидаемым результат,
# 3 флаг - путь до файла с аргументами

path_to_script=$(dirname "$(readlink -f "$0")")
# Обработка первых двух параметров

if [[ $# -lt 3 ]]; then
    exit 1
else
    file_input=$1
    file_output_expect=$2
    path_to_args=$3
    if ! [[ -e "$file_input" ]] || ! [[ -e "$file_output_expect" ]] || ! [[ -e "$path_to_args" ]]; then
        exit 1
    fi
fi

"$path_to_script"/../../app.exe $(< "$path_to_args") < "$file_input" > "$path_to_script"/temp.txt
# Проверка что exitcode ненулевой
rc=$?

if [[ "$rc" != 0 ]]; then
    exit 1
fi

"$path_to_script"/comparator.sh "$path_to_script"/temp.txt "$file_output_expect"

rm "$path_to_script"/temp.txt
# Получение результата от компаратора

result=$?
if [[ "$result" == 0 ]]; then
    exit 0
fi
exit 1