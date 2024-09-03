#!/bin/bash
path_to_script=$(dirname "$(readlink -f "$0")")

# Проверка на количество параметров
if [[ $# -lt 1 ]]; then
    exit 1
fi

# Получение первого параметра, отвечающего за
file_input=$1
if ! [[ -e "$file_input" ]]; then
    exit 1
fi

# Получение второго параметра, отвечающего за аргументы командной строки
if [[ -n "$2" ]]; then
    if [[ -e "$2" ]]; then
        args="$2"
    else
        exit 1
    fi
else
    args=""
fi

bin_file_name="${file_input%.txt}.bin" # Получаем имя нового бинарного файла
"$path_to_script"/../../app.exe import "$file_input" "$bin_file_name"
rc=$? # Проверка на ошибку конвертации текстовика в бинарник
if [[ "$rc" != 0 ]]; then
    exit 0
fi

("$path_to_script"/../../app.exe "$(< "$args")") >/dev/null

# Получения кода возврата и проверка, что вывод ненулевой
rc=$?
rm "$bin_file_name"
if [[ "$rc" == 0 ]]; then
    exit 1
fi
exit 0
