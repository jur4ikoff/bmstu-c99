#!/bin/bash

# Проверка наличия параметров
if [[ $# -lt 2 ]]; then
    echo "Need 2 files"
    exit 2
fi

# Определение имени входных файлов
file1=$1
file2=$2

# Проверка на существование файла
if ! [[ -e "$file1" ]] || ! [[ -e "$file2" ]]; then
    echo "No file"
    exit 3
fi

# Проверка на наличие флага
if [[ $3 == "-r" ]]; then
    # Если есть флаг "-r", то учитывается подстрока после вхождение подстроки "Result: "
    string1=$(grep -oP '(?<=Result: ).*' "$file1")
    string2=$(grep -oP '(?<=Result: ).*' "$file2")
else
    # Сравнение всех текстовых символов из файла
    string1=$(<"$file1")
    string2=$(<"$file2")
fi


# Если строки пустые, то выходим из программы
if [[ -z "$string1" ]] || [[ -z "$string2" ]]; then
    exit 1
fi

# Записываем "разность строк" в переменную
difference=$(diff <(echo "$string1") <(echo "$string2"))
# Если переменная не пустая, то выход с exitcode 1, иначе 0 (успех)
if [[ -z "$difference" ]]; then
    exit 0
else
    exit 1
fi

