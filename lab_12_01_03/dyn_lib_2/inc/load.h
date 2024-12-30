#ifndef LOAD_H__
#define LOAD_H__

#include <stdio.h>

// Определение указателей на функции
typedef int (*file_elements_count_fn)(char *filename, size_t *size);
typedef int (*file_write_int_fn)(char *filename, int *start, int *end);
typedef int (*copy_array_fn)(int *start_src, int *end_src, int *start_dst, int **end_dst);
typedef void (*print_array_fn)(int *start, int *end);
typedef int (*create_array_from_file_fn)(char *filename, int **arr, size_t size);
typedef void (*mysort_fn)(void *arr, size_t number, size_t width, int (*compare)(const void *, const void *));
typedef const int *(*find_last_neg_el_fn)(const int *pbegin, const int *pend);
typedef int (*key_fn)(const int *pbegin_source, const int *pend_source, int *pbegin_filter, int **pend_filter);

// Структура с указателями на функции
typedef struct load_lib_type_
{
    file_elements_count_fn file_elements_count;
    file_write_int_fn file_write_int;
    copy_array_fn copy_array;
    print_array_fn print_array;
    create_array_from_file_fn create_array_from_file;
    mysort_fn mysort;
    find_last_neg_el_fn find_last_neg_el;
    key_fn key;
} load_lib_t;

/**
 * @brief Функция загружает функции из динамической библиотеки
 * @param handle Указатель на переменную для работы с dl. Должна быть после dlopen
 * @param[in] load Структура указателей на функцию
 * @return код возврата
 */
int load_all_funtions_from_dyn_lib(void *handle, load_lib_t *load);
#endif
