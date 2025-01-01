#!/bin/bash

# Настройка кодов цветов для наглядного вывода
RESET_COLOR='\033[0m'
RED='\033[31m'
GREEN='\033[32m'

verbose_flag=0
valgrind_flag=0

# Проверка параметра verbose и параметра valgrind (сделал флаг, чтобы запускать на macos)
if [[ "$1" == "-v" ]]; then
    verbose_flag=1
fi
if [[ "$2" == "-valgrind" ]]; then
    valgrind_flag=1
fi

# Определяем путь к скрипту
path_to_script=$(dirname "$(readlink -f "$0") || true")
# Задаем команду валгринда
valgrind_command="valgrind --leak-check=full --quiet --show-leak-kinds=all"
# Определяем файл логирования для валгринда
logfile="${path_to_script}/log.txt"

# Поиск всех .txt файлов
files=$(find "$path_to_script"/../data/ -name "*in.txt" | sort)

# Инициализируем переменные-счетчики
fail_count=0
pos_count=0
neg_count=0
pos_count_passed=0
neg_count_passed=0

# Иттерируемся по всем файлам
for file in $files; do
    # Проверка на положительный тест и запуск pos_case.sh
    if [[ "${file}" == *pos_* ]]; then
        # Запуск положительного теста
        ((pos_count++))

        # Парсим номер теста из названия файла
        number=$(echo "${file}" | grep -o "pos_[0-9]\+_in.txt" | grep -o "[0-9]\+")

        # Опрелеяем файл для вывода и файл с аргументами
        output_file="${path_to_script}"/../data/pos_"$number"_out.txt
        path_to_args="${path_to_script}"/../data/pos_"$number"_args.txt

        # Запускаем pos_case и проверяем exit_code
        # "${path_to_script}"/pos_case.sh "${file}" "$path_to_args" "${output_file}"
        "${path_to_script}"/pos_case.sh "$path_to_args" "$output_file"
        res=$?

        # Определяем команду запуска для приложения
        launch_app="${path_to_script}/../../app.exe ${path_to_args}"
        # Если проверка с валгриндом
        if [[ valgrind_flag -eq 1 ]]; then
            # Оределяем команду для запуска валгринда
            # В качестве файла логирования будет выступать заранее определенный файл
            valgrind_start="${valgrind_command} --log-file=${logfile} ${launch_app}"
            # Перенаправляем вывод программы в спец файл
            $valgrind_start >/dev/null
            # Проверяем пустой ли logfile
            if [[ -s "${logfile}" ]]; then
                # Если файл не пустой, выдается ошибка при работе памяти, и программа завершает работу
                echo -e "pos_case_$number memory ${RED}ERROR${RESET_COLOR}"
                cat "${logfile}"
                exit 2
            fi
        fi

        # Проверяем exitcode программы
        if [[ "$res" != 0 ]]; then
            # Увеличиваем счетчик фейл тестов
            ((fail_count++))
            # Вывод
            if [[ "$verbose_flag" == 1 ]]; then
                if [[ "$valgrind_flag" == 1 ]]; then
                    echo -e "pos_case_$number ${RED}FAILED${RESET_COLOR}  memory ${GREEN}PASS${RESET_COLOR}"
                else
                    echo -e "pos_case_$number ${RED}FAILED${RESET_COLOR}"
                fi
            fi
        else
            if [[ "$verbose_flag" == 1 ]]; then
                if [[ "$valgrind_flag" == 1 ]]; then
                    echo -e "pos_case_$number ${GREEN}PASSED${RESET_COLOR}  memory ${GREEN}PASS${RESET_COLOR}"
                else
                    echo -e "pos_case_$number ${GREEN}PASSED${RESET_COLOR}"
                fi
            fi
            # Увеличиваем счеткич прошедших тестов
            ((pos_count_passed++))
        fi

    # Проверка на негативный тест и запуск neg_case.sh
    elif [[ $file == *neg_* ]]; then
        ((neg_count++))

        # Получаем номер тестоа
        number=$(echo "$file" | grep -o "neg_[0-9]\+_in.txt" | grep -o "[0-9]\+")
        # Получаем путь до аргументов
        path_to_args="${path_to_script}"/../data/neg_"$number"_args.txt
        # Запуск neg_case.sh
        "$path_to_script"/neg_case.sh "$path_to_args"
        res=$? # Получение результата

        # Составление команды запуска
        launch_app="${path_to_script}/../../app.exe ${path_to_args}"
        # Если проверка с валгриндом
        if [[ valgrind_flag -eq 1 ]]; then
            # Оределяем команду для запуска валгринда
            # В качестве файла логирования будет выступать заранее определенный файл
            valgrind_start="${valgrind_command} --log-file=${logfile} ${launch_app}"
            $valgrind_start >/dev/null

            if [[ -s "${logfile}" ]]; then
                # Если logfile не пустой, выводим на экран и возвращаем ошибку
                echo -e "neg_case_$number ${RED}MEMORY ERROR${RESET_COLOR}"
                cat "${logfile}"
                exit 2
            fi
        fi

        # Обработка результатов
        if [[ "$res" == 0 ]]; then
            # Увеличиваем счетчик проваленных тестов
            ((neg_count_passed++))
            # Вывод если verbose true
            if [[ "$verbose_flag" == 1 ]]; then
                if [[ "$valgrind_flag" == 1 ]]; then
                    echo -e "neg_case_$number ${GREEN}PASSED${RESET_COLOR}  memory ${GREEN}PASS${RESET_COLOR}"
                else
                    echo -e "neg_case_$number ${GREEN}PASSED${RESET_COLOR}"
                fi
            else
                if [[ "$valgrind_flag" == 1 ]]; then
                    echo -e "neg_case_$number ${GREEN}PASSED${RESET_COLOR}  memory ${GREEN}PASS${RESET_COLOR}"
                fi
                # Увеличиваем счетчик прошедних негативных тестов
            fi
        else
            ((fail_count++))
            if [[ "$verbose_flag" == 1 ]]; then
                if [[ "$valgrind_flag" == 1 ]]; then
                    echo -e "neg_case_$number ${RED}FAIL${RESET_COLOR}  memory ${GREEN}PASS${RESET_COLOR}"
                else
                    echo -e "neg_case_$number ${RED}FAIL${RESET_COLOR}"
                fi
            else
                if [[ "$valgrind_flag" == 1 ]]; then
                    echo -e "neg_case_$number ${RED}FAIL${RESET_COLOR}  memory ${GREEN}PASS${RESET_COLOR}"
                fi
            fi
        fi
    fi
done

# Вывод окончательных результатов позитивного тестирования
if [[ $pos_count_passed -eq $pos_count ]]; then
    echo -e "Positive tests passed ${GREEN}$pos_count_passed / $pos_count${RESET_COLOR}"
else
    echo -e "Positive tests passed ${RED}$pos_count_passed / $pos_count${RESET_COLOR}"
fi

# Вывод результатов негативного тестирования
if [[ "$neg_count" == 0 ]]; then
    echo "No negative tests"
elif [[ $neg_count_passed -eq $neg_count ]]; then
    echo -e "Negative tests passed ${GREEN}$neg_count_passed / $neg_count${RESET_COLOR}"
else
    echo -e "Negative tests passed ${RED}$neg_count_passed / $neg_count${RESET_COLOR}"
fi

# Возврат значений
exit $fail_count
