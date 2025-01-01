#!/bin/bash

# 1 флаг - путь до файл с данными для ввода, 2 флаг - путь до файла с ожидаемым результат,
# 3 флаг - путь до файла с аргументами
path_to_script=$(dirname "$(readlink -f "$0")")

# Обработка первых двух параметров
# Обработка первых двух параметров

if [[ $# != 2 ]]; then
    exit 1
else
    path_to_args=$1
    file_output_expect=$2
fi


args=$(<"$path_to_args")
# Проверка основной программы
echo "$args" | xargs "$path_to_script/../../app.exe" > "$path_to_script"/temp.txt

# Проверка что exitcode ненулевой
rc=$?
if [[ "$rc" != 0 ]]; then
    exit 1
fi

"$path_to_script"/comparator.sh "$path_to_script"/temp.txt "$file_output_expect"

# Получение результата от компаратора
result=$?
# rm "$path_to_script"/temp.txt
if [[ "$result" == 0 ]]; then
    exit 0
fi
exit 1
