#!/bin/bash

path_to_script=$(dirname "$(readlink -f "$0")")

# Компилирование сборки для замера покрытия
echo ">> Compile"
"${path_to_script}"/build_coverage.sh
res=$?
if [[ "$res" != 0 ]]; then
    exit 1
fi
echo

# Проверка существования юзер-тестов
if [[ ! -d "${path_to_script}"/func_tests/data ]]; then
    echo "No User Tests"
    exit 1
fi

# Запуск юзер-тестов
echo ">> Run user tests"
echo
"${path_to_script}"/func_tests/scripts/func_tests.sh -v
echo 
echo ">> Analyse coverage"
gcov -n -a "$path_to_script"/app.exe | tail -n 1
