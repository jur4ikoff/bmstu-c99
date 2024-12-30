#!/bin/bash

# Скрипт запускает функциональные тесты и замеряет покрытие
# Настройка цветов

RESET_COLOR='\033[0m'
RED='\033[31m'

# Определение путя до скрипта
path_to_script=$(dirname "$(readlink -f "$0")")

# Компиляция цель coverage
echo ">> Compile"
make -s -B coverage
# Получение результата компиляции и обработка
res=$?
if [[ "$res" != 0 ]]; then
    echo -e "${RED}Compilation failed${RESET_COLOR}"
    make -s clean
    exit 1
fi

# Проверка существования юзер-тестов
if [[ ! -d "${path_to_script}"/func_tests/data ]]; then
    echo -e "${RED}No user tests${RESET_COLOR}"
    exit 1
fi

# Запуск юзер-тестов
echo ">> Run user tests"
echo
# запуск скрипта func_tests.sh
"${path_to_script}"/func_tests/scripts/func_tests.sh -v # - valgrind
echo
echo ">> Analyse coverage"

# Вывод информации о покрытии всех файлов
for file in out/*.gcda; do
    base=$(basename -s .gcda "$file")
    echo "info about \"$base\".c"
    gcov "$file" | tail -n +2 | head -n 1
    echo
done
