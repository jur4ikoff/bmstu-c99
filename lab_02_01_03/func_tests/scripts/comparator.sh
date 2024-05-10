#!/bin/bash

# Проверка наличия параметров
if [[ $# -lt 2 ]]; then
    echo "Need 2 files"
    exit 2
fi

file1=$1
file2=$2
if ! [[ -e "$file1" ]] || ! [[ -e "$file2" ]]; then
    echo "No file"
    exit 3
fi

# Извлечение ЧПТ
string1=$(grep -oE "\b[0-9]+(\.[0-9]+)?\b" "$file1")
string2=$(grep -oE "\b[0-9]+(\.[0-9]+)?\b" "$file2")
if [[ -z "$string1" ]] || [[ -z "$string2" ]]; then
    exit 1
fi
# Получение разницы
difference=$(diff <(echo "$string1") <(echo "$string2"))
if [[ -z "$difference"  ]]; then
    exit 0
else
    exit 1
fi

