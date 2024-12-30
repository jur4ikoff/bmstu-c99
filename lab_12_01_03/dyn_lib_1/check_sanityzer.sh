#!/bin/bash
# Скрипт прогоняет все санитайзеры

# Настройка цветов
RESET_COLOR='\033[0m'
RED='\033[31m'

# Определение местораспроложение скрипта
path_to_script=$(dirname "$(readlink -f "$0")")

# билд adress sanitizer
echo "Build adress sanitizer"
make -s -B asan
# Получение результатов билда и их проверка
res=$?
if [[ "$res" != 0 ]]; then
    echo -e "${RED}Error while compiling${RESET_COLOR}"
    exit 1
fi

# Запуск функциональных тестов с valgrind'ом
"$path_to_script"/func_tests/scripts/func_tests.sh -valgrnd
echo

# Билд memory sanitizer
echo "Build memory sanitizer"
make -s -B msan
# Проверка результатов и их обработка
res=$?
if [[ "$res" != 0 ]]; then
    echo -e "${RED}Error while compiling${RESET_COLOR}"
    exit 1
fi

# Запуск функциональных тестов с valgrind'ом
"$path_to_script"/func_tests/scripts/func_tests.sh -valgrnd
echo

# Билд undefined behaviour sanityzer
echo "Build undefined behaviour sanitizer"
make -s -B ubsan
# Получение результатов и их обработка
res=$?
if [[ "$res" != 0 ]]; then
    echo -e "${RED}Error while compiling${RESET_COLOR}"
    exit 1
fi

# Запуск функциональных тестов с valgrind'ом
"$path_to_script"/func_tests/scripts/func_tests.sh -valgrind
