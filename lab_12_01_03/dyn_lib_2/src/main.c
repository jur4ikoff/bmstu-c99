#define _CRT_SECURE_NO_WARNINGS

#include "constants.h"
#include "dlfcn.h"
#include "errors.h"
#include "load.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Функция компаратор для двух целых чисел
static int int_compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

// Сортировка 5 вариант, фильтр - 3

int main(int argc, char **argv)
{
    // Инициализация переменных
    load_lib_t load_struct = { 0 };
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

    //  Загрузка библиотеки
    void *lib = dlopen("./out/libfilter.so", RTLD_LAZY);
    if (lib == NULL)
    {
        print_err_msg(ERR_LOAD_LIB);
        dlclose(lib);
        return ERR_LOAD_LIB;
    }

    // Чтение всех функций из библиотеки
    if ((rc = load_all_funtions_from_dyn_lib(lib, &load_struct)) != ERR_OK)
    {
        print_err_msg(ERR_LOAD_LIB);
        dlclose(lib);
        return ERR_LOAD_LIB;
    }

    // Ищем количество чисел
    if ((rc = load_struct.file_elements_count(file_input, &size)) != ERR_OK)
    {
        print_err_msg(rc);
        dlclose(lib);
        return rc;
    }

    // Обрабатываем негативный случай
    if (size == 0 || size > MAX_COUNT)
    {
        print_err_msg(ERR_EMPTY_INPUT);
        dlclose(lib);
        return ERR_EMPTY_INPUT;
    }

    //  Создание массива из файла
    if ((rc = load_struct.create_array_from_file(file_input, &arr, size)) != ERR_OK)
    {
        free(arr);
        print_err_msg(rc);
        dlclose(lib);
        return rc;
    }

    // Инициализация указателя на конец массива и указателей на массивы после фильтрации
    int *arr_end = arr + (int)size, *start_filter_arr = NULL, *end_filter_arr = NULL;

    // print_array(arr, arr_end);
    // Поиск последнего отрицательного
    const int *p_last_neg = load_struct.find_last_neg_el(arr, arr_end);

    // Проверка на то что вывод не пустой
    if (p_last_neg - arr < 1)
    {
        dlclose(lib);
        free(arr);
        free(start_filter_arr);
        print_err_msg(ERR_EMPTY_OUTPUT);
        return ERR_EMPTY_OUTPUT;
    }

    // Если фильтр, то запускаем функцию фильтрации
    if (is_filter)
    {
        // Выделение памяти под новый массив
        start_filter_arr = malloc((p_last_neg - arr) * sizeof(int));
        if (start_filter_arr == NULL)
        {
            free(arr);
            dlclose(lib);
            free(start_filter_arr);
            print_err_msg(ERR_ALLOCATION);
            return ERR_ALLOCATION;
        }

        if ((rc = load_struct.key(arr, arr_end, start_filter_arr, &end_filter_arr)) != ERR_OK)
        {
            free(arr);
            free(start_filter_arr);
            dlclose(lib);
            print_err_msg(rc);
            return rc;
        }
    }
    else
    {
        start_filter_arr = malloc((arr_end - arr) * sizeof(int));
        if (start_filter_arr == NULL)
        {
            free(arr);
            free(start_filter_arr);
            dlclose(lib);
            print_err_msg(ERR_ALLOCATION);
            return ERR_ALLOCATION;
        }

        // Иначе просто копируем массив
        if ((rc = load_struct.copy_array(arr, arr_end, start_filter_arr, &end_filter_arr)) != ERR_OK)
        {
            free(arr);
            free(start_filter_arr);
            dlclose(lib);
            print_err_msg(rc);
            return rc;
        }
    }

    // Сравниваем указатели на начало и конец
    if (start_filter_arr == end_filter_arr)
    {
        free(arr);
        free(start_filter_arr);
        dlclose(lib);
        print_err_msg(ERR_EMPTY_OUTPUT);
        return ERR_EMPTY_OUTPUT;
    }

    // СОРТИРОВКА
    load_struct.print_array(start_filter_arr, end_filter_arr);
    // qsort(filter_arr, end_filter_arr - filter_arr, sizeof(int), compare);
    load_struct.mysort(start_filter_arr, end_filter_arr - start_filter_arr, sizeof(int), int_compare);
    load_struct.print_array(start_filter_arr, end_filter_arr);

    // Запись измененного массива в файл вывода
    if ((rc = load_struct.file_write_int(file_output, start_filter_arr, end_filter_arr)) != ERR_OK)
    {
        free(arr);
        free(start_filter_arr);
        dlclose(lib);
        print_err_msg(rc);
        return rc;
    }

    // Освобождение памяти и выход из программы
    free(arr);
    free(start_filter_arr);
    dlclose(lib);
    return rc;
}
