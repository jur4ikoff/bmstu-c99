#!/bin/bash

# Проверка параметра verbose 
if [[ "$1" == "-v" ]]; then
    flag=1
    echo "Verbose=true"
else
    flag=0
fi


path_to_script=$(dirname "$(readlink -f "$0") || true")
# Поиск всех .txt файлов
files=$(find "$path_to_script"/../data/ -name "*in.txt" | sort)
fail_count=0
pos_count=0
neg_count=0
pos_count_passed=0
neg_count_passed=0

# Иттерирование по всем файлам
for file in $files
do  
    # Проверка на положительный тест и запуск pos_case.sh
    if [[ "${file}" == *pos_* ]]; then
        (( pos_count++ )) 
        number=$(echo "${file}" | grep -o "pos_[0-9]\+_in.txt" | grep -o "[0-9]\+")
        output_file="${path_to_script}"/../data/pos_"$number"_out.txt
        "${path_to_script}"/pos_case.sh "${file}" "${output_file}"
        res=$?
        if [[ "$res" != 0 ]]; then
            fail_count=$((fail_count + 1))
            if [[ "$flag" == 1 ]]; then
                echo "pos_case_$number failed"
            fi
        else
            (( pos_count_passed++ ))
            if [[ "$flag" == 1 ]]; then
                echo "pos_case_$number pass"
            fi
        fi
    # Проверка на негативный тест и запуск neg_case.sh
    elif [[ $file == *neg_*  ]]; then
        (( neg_count++ )) 
        number=$(echo "$file" | grep -o "neg_[0-9]\+_in.txt" | grep -o "[0-9]\+")
        "$path_to_script"/neg_case.sh "$file"
        res=$?
        if [[ "$res" != 0 ]]; then
            fail_count=$((fail_count + 1))
            if [[ "$flag" == 1 ]]; then
                echo "neg_case_$number failed"
            fi
        else
            (( neg_count_passed++ ))
            if [[ "$flag" == 1 ]]; then
                echo "neg_case_$number pass"
            fi
        fi
    fi 
done

# Вывод
echo "Positive tests passed $pos_count_passed / $pos_count"


if [[ "$neg_count" == 0 ]]; then
    echo "No negative tests"
else
    echo "Negative tests passed $neg_count_passed / $neg_count"
fi
exit $fail_count