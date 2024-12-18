#!/bin/bash
path_to_script=$(dirname "$(readlink -f "$0")")
# Проверка на количество параметров и их обработка
if [[ $# != 1 ]]; then
    exit 1
else
    path_to_args="$1"
    if ! [[ -e "$path_to_args" ]]; then
        exit 1
    fi
fi

args=$(<"$path_to_args")
# Проверка основной программы
echo "$args" | xargs "$path_to_script/../../app.exe" >/dev/null

# Получения кода возврата и проверка, что вывод ненулевой
rc=$?

if [[ "$rc" == 0 ]]; then
    exit 1
fi
exit 0
