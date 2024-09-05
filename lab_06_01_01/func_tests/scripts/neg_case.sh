#!/bin/bash
path_to_script=$(dirname "$(readlink -f "$0")")

# Проверка на количество параметров и их обработка
if [[ $# -lt 2 ]]; then
    exit 1
else
    file_input="$1"
    args="$2"
    if ! [[ -e "$file_input" ]] || ! [[ -e "$args" ]]; then
        exit 1
    fi
fi
# Проверка основной программы
("$path_to_script"/../../app.exe $(< "$args")) >/dev/null  # Я не придумал, как исправить предупреждение ShellCheck'a, Если поставить кавычки, это ломает программу.

# Получения кода возврата и проверка, что вывод ненулевой
rc=$?
if [[ "$rc" == 0 ]]; then
    exit 1
fi
exit 0
