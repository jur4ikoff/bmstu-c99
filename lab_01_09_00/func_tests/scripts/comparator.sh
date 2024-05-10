#!/bin/bash

# Проверка наличия параметров
if [[ $# -lt 2 ]]; then
    echo "Need 2 files"
    exit 2
fi

file1=$1
file2=$2
if ! [[ -e "${file1}" ]] || ! [[ -e "${file2}" ]]; then
    echo "No file"
    exit 3
fi


# Извлечение результата после подстроки "Result: "
extract_result() {
    cat < "$2" | grep -oP "(?<=$1).*$"
}


# Вызов функции, извлечение ЧПТ
string1=$(extract_result "Result: " "${file1}")
string2=$(extract_result "Result: " "${file2}")
    
if [[ -z "${string1}" ]] || [[ -z "${string2}" ]]; then
    exit 1
fi
if [[ "${string1}" == "${string2}" ]]; then
    exit 0
else
    exit 1
fi
