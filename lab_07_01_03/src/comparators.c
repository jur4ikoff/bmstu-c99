#include "comparators.h"
#include <stdio.h>
#include "errors.h"

// Функция компаратор для двух целых чисел
int int_compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

// Функция компаратор для двух вещественных чисел
int double_compare(const void *a, const void *b)
{
    return (int)(*(double *)a - *(double *)b);
}

// Функция компаратор чаров
int char_compare(const void *a, const void *b)
{
    return *(char *)a - *(char *)b;
}

// Функция компаратор для массива чисел
int int_arr_compare(int first_arr[], int second_arr[], size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        if (first_arr[i] != second_arr[i])
            return ERR_NOT_EQ;
    }
    return ERR_OK;
}
