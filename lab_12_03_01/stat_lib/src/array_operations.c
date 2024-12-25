#define _CRT_SECURE_NO_WARNINGS
#include "array_operations.h"
#include "errors.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Функция компаратор для двух целых чисел
int int_compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

// Вывод массива на экран
void print_array(int *start, int *end)
{
    for (int *cur = start; cur < end; cur++)
    {
        printf("%d ", *cur);
    }
    printf("\n");
}

// Функция реализует копиравание массива
int copy_array(int *start_src, int *end_src, int **start_dst, int **end_dst)
{
    if (start_src == NULL || end_src == NULL)
        return ERR_POINTER;
    if (end_src <= start_src)
        return ERR_POINTER;

    *start_dst = malloc((end_src - start_src) * sizeof(int));
    if (*start_dst == NULL)
        return ERR_ALLOCATION;

    *end_dst = *start_dst;
    for (int *cur = start_src; cur < end_src; cur++)
    {
        **end_dst = *cur;
        if (cur < end_src)
            (*end_dst)++;
    }

    return ERR_OK;
}

// Считывание массива чисел из файла
int create_array_from_file(char *filename, int **arr, size_t size)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return ERR_FILENAME;

    *arr = malloc(size * sizeof(int));
    if (arr == NULL)
    {
        fclose(file);
        return ERR_ALLOCATION;
    }

    for (size_t i = 0; i < size; i++)
    {
        if (fscanf(file, "%d", &(*arr)[i]) != 1)
        {
            free(arr);
            fclose(file);
            return ERR_READ;
        }
    }
    fclose(file);
    return ERR_OK;
}

/**
 * @brief Модифицированная сортировка пузырьком: Запоминайте, где произошёл последний обмен элементов,
 * и при следующем проходе алгоритм не заходит за это место.
 * Если последними поменялись i-ый и i+1-ый элементы, то при следующем проходе алгоритм не сравнивает элементы за i-м.
 * Заголовок аналогичен функции qsort
 * @param arr Массив типа войд
 * @param number Количество элементов массива
 * @param width Размер одного жлемента
 * @param compare Указатель на функцию компаратор
 */

void mysort(void *arr, size_t number, size_t width, int (*compare)(const void *, const void *))
{
    if (number < 2)
        return; // Если массив пуст или содержит один элемент, ничего не делаем

    char *array = (char *)arr;
    bool swapped;
    size_t last_swap_index;

    do
    {
        swapped = false;
        last_swap_index = 0; // Сброс последнего индекса обмена

        for (size_t i = 0; i < number - 1; i++)
        {
            // Сравниваем элементы с учётом их ширины
            if (compare(array + i * width, array + (i + 1) * width) > 0)
            {
                // Обмен элементов
                for (size_t j = 0; j < width; j++)
                {
                    char temp = array[i * width + j];
                    array[i * width + j] = array[(i + 1) * width + j];
                    array[(i + 1) * width + j] = temp;
                }
                swapped = true;
                last_swap_index = i + 1; // Обновляем последний индекс обмена
            }
        }

        // Уменьшаем число сравнений в следующем проходе
        number = last_swap_index;
    } while (swapped);
}

/**
 * @brief Функция ищет указатель на последний отрицательный элемент
 * @param pbegin Указатель на начало
 * @param pend Указатель на конец массива
 * @returns Указатель на последний отрицательный элемент
 */
const int *find_last_neg_el(const int *pbegin, const int *pend)
{
    const int *index = pend;

    for (int *cur = (int *)pbegin; cur < pend; cur++)
    {
        if (*cur < 0)
            index = cur;
    }
    return index;
}

/**
 * @brief В массиве остаются элементы от нулевого до р-го, где р - индекс последнего отрицательного элемента
 * этого массива либо число п, если такого элемента в массиве нет.
 * @param pbegin_source Указатель на начало исходного массива
 * @param pend_source Указатель на конец исходного массива
 * @param pbegin_filtered_arr Указатель на указатель на начало второго фильтрованного массива
 * @param pend_filtered_arr Указатель на указатель на конец второго фильтрованного массива
 * @returns Код ошибки
 */
int key(const int *pbegin_source, const int *pend_source, int *pbegin_filter, int **pend_filter)
{
    // Проверки
    if (pbegin_source == NULL || pend_source == NULL || pbegin_filter == NULL)
        return ERR_POINTER;
    if (pend_source <= pbegin_source)
        return ERR_POINTER;

    // Поиск последнего отрицательного
    const int *index = find_last_neg_el(pbegin_source, pend_source);

    // Проверка на то что вывод не пустой
    if (index - pbegin_source < 1)
        return ERR_EMPTY_OUTPUT;


    int *end = pbegin_filter;
    // Заполняем новый массив элементами старого
    while (pbegin_source < index)
    {
        *end = *pbegin_source;
        pbegin_source++;
        end++;
    }

    *pend_filter = end;
    return ERR_OK;
}
