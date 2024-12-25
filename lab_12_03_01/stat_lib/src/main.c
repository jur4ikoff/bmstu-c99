#define _CRT_SECURE_NO_WARNINGS
#include "array_operations.h"
#include "constants.h"
#include "errors.h"
#include "file_operations.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Сортировка 5 вариант, фильтр - 3

int main(int argc, char **argv)
{
    // Инициализация переменных
    char file_input[MAX_STRING_LEN], file_output[MAX_STRING_LEN];
    int rc = ERR_OK, *arr = NULL;
    size_t size = 0;
    bool is_filter = false;

    // Проверка на количество элементов
    if (argc < 3)
    {
        print_err_msg(ERR_ARGS);
        return ERR_ARGS;
    }

    strcpy(file_input, argv[1]);
    strcpy(file_output, argv[2]);

    // Проверка на наличие флага, если 3 аргумент есть, но он не равен f, тогда выдается ошибка
    if (argc == 4)
    {
        if (strcmp(argv[3], "f") == 0)
            is_filter = true;
        else
        {
            print_err_msg(ERR_ARGS);
            return ERR_ARGS;
        }
    }
    // Проверка на то что аргументов слишком много
    else if (argc > 4)
    {
        print_err_msg(ERR_ARGS);
        return ERR_ARGS;
    }

    // Ищем количество чисел
    if ((rc = file_elements_count(file_input, &size)) != ERR_OK)
    {
        print_err_msg(rc);
        return rc;
    }

    // Обрабатываем негативный случай
    if (size == 0 || size > MAX_COUNT)
    {
        print_err_msg(ERR_EMPTY_INPUT);
        return ERR_EMPTY_INPUT;
    }

    //  Создание массива из файла
    if ((rc = create_array_from_file(file_input, &arr, size)) != ERR_OK)
    {
        free(arr);
        print_err_msg(rc);
        return rc;
    }

    // Инициализация указателя на конец массива и указателей на массивы после фильтрации
    int *arr_end = arr + (int)size, *start_filter_arr = NULL, *end_filter_arr = NULL;

    // print_array(arr, arr_end);
    // Поиск последнего отрицательного
    const int *p_last_neg = find_last_neg_el(arr, arr_end);

    // Проверка на то что вывод не пустой
    if (p_last_neg - arr < 1)
        return ERR_EMPTY_OUTPUT;

    // Выделение памяти под новый массив
    start_filter_arr = malloc((p_last_neg - arr) * sizeof(int));
    if (start_filter_arr == NULL)
    {
        free(arr);
        free(start_filter_arr);
        print_err_msg(ERR_ALLOCATION);
        return ERR_ALLOCATION;
    }

    // Если фильтр, то запускаем функцию фильтрации
    if (is_filter) 
    {
        if ((rc = key(arr, arr_end, start_filter_arr, &end_filter_arr)) != ERR_OK)
        {
            free(arr);
            free(start_filter_arr);
            print_err_msg(rc);
            return rc;
        }
    }
    else
    {
        // Иначе просто копируем массив
        if ((rc = copy_array(arr, arr_end, &start_filter_arr, &end_filter_arr)) != ERR_OK)
        {
            free(arr);
            free(start_filter_arr);
            print_err_msg(rc);
            return rc;
        }
    }

    // Сравниваем указатели на начало и конец
    if (start_filter_arr == end_filter_arr)
    {
        free(arr);
        free(start_filter_arr);
        print_err_msg(ERR_EMPTY_OUTPUT);
        return ERR_EMPTY_OUTPUT;
    }

    // СОРТИРОВКА
    // print_array(filter_arr, end_filter_arr);
    // qsort(filter_arr, end_filter_arr - filter_arr, sizeof(int), compare);
    mysort(start_filter_arr, end_filter_arr - start_filter_arr, sizeof(int), int_compare);
    // print_array(filter_arr, end_filter_arr);

    // Запись измененного массива в файл вывода
    if ((rc = file_write_int(file_output, start_filter_arr, end_filter_arr)) != ERR_OK)
    {
        free(arr);
        free(start_filter_arr);
        print_err_msg(rc);
        return rc;
    }

    // Освобождение памяти
    free(arr);
    free(start_filter_arr);
    // Вывод
    return rc;
}
