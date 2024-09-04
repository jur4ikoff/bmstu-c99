#!/bin/bash

# 1 флаг - путь до файл с данными для ввода, 2 флаг - путь до файла с ожидаемым результат,
# 3 флаг - путь до файла с аргументами

path_to_script=$(dirname "$(readlink -f "$0")")
# Обработка первых двух параметров
if [[ $# -lt 2 ]]; then
    exit 1
else
    file_input=$1
    file_output_expect=$2
    if ! [[ -e "$file_input" ]] || ! [[ -e "$file_output_expect" ]]; then
        exit 1
    fi
fi

# Обработка 3-го параметра.
if [[ $# == 3 ]]; then
    if [[ -e "$3" ]]; then
        path_to_args=$3
    else
        exit 1
    fi 
else
    path_to_args=""
fi


bin_file_name="${file_input%.txt}.bin" # Получаем имя нового бинарного файла
"$path_to_script"/../../app.exe import "$file_input" "$bin_file_name"
rc=$? # Проверка на ошибку конвертации текстовика в бинарник
if [[ "$rc" != 0 ]]; then
    rm "$bin_file_name"
    exit 1
fi

#echo "$path_to_args"
#exit 0
"$path_to_script"/../../app.exe $(cat "$path_to_args") < "$file_input" > "$path_to_script"/temp.txt
# Проверка что exitcode ненулевой
rc=$?
if [[ "$rc" != 0 ]]; then
    exit 1
fi

# Получение результата от компаратора
"$path_to_script"/comparator.sh "$path_to_script"/temp.txt "$file_output_expect"
result=$?
if [[ "$result" == 0 ]]; then
    exit 0
fi
exit 1