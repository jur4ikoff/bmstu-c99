#define _CRT_SECURE_NO_WARNINGS
#include "array_operations.h"
#include <stdlib.h>
#include <stdbool.h>
#include "errors.h"
#include <stdio.h>

void print_array(int *begin_arr, int *end_arr)
{
    while (begin_arr != end_arr)
    {
        printf("%d ", *begin_arr);
        begin_arr++;
    }
    printf("\n");
}

int copy_array(int *begin_src, int *end_src, int **begin_dst, int **end_dst)
{
    if (begin_src == NULL || end_src == NULL)
        return ERR_POINTER;
    if (end_src <= begin_src)
        return ERR_POINTER;
    *begin_dst = malloc((end_src - begin_src) * sizeof(int));
    if (*begin_dst == NULL)
        return ERR_ALLOCATION;

    *end_dst = *begin_dst;
    while (begin_src != end_src)
    {
        **end_dst = *begin_src;
        begin_src++;
        (*end_dst)++;
    }

    return ERR_OK;
}

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
 */
void my_sort(void *arr, size_t number, size_t width, int (*compare)(const void *, const void *))
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
 * @brief Модифицированная сортировка пузырьком: Запоминайте, где произошёл последний обмен элементов,
 * и при следующем проходе алгоритм не заходит за это место.
 * Если последними поменялись i-ый и i+1-ый элементы, то при следующем проходе алгоритм не сравнивает элементы за i-м.
 */
void my_sort_test(void *arr, size_t number, size_t width, int (*compare)(const void *, const void *))
{
    if (number < 2)
        return;

    char *array = (char *)arr;

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
        }
    }
}

int compare(const void *elem1, const void *elem2)
{
    return (*(int *)elem1 - *(int *)elem2);
}

static const int *find_last_neg_el(const int *pbegin, const int *pend, size_t *last_count)
{
    *last_count = 0;
    const int *index = pend;
    while (pbegin != pend)
    {
        if (*pbegin < 0)
        {
            index = pbegin;
            *last_count = pend - pbegin;
        }
        pbegin++;
    }

    return index;
}

/**
 * @brief В массиве остаются элементы от нулевого до р-го, где р - индекс последнего отрицательного элемента этого массива либо число п, если такого элемента в массиве нет.
 */
int key(const int *pbegin_source, const int *pend_source, int **pbegin_filtered_arr, int **pend_filtered_arr)
{
    if (pbegin_source == NULL || pend_source == NULL)
        return ERR_POINTER;
    if (pend_source <= pbegin_source)
        return ERR_POINTER;
    size_t count = 0;
    const int *index = find_last_neg_el(pbegin_source, pend_source, &count);
    // printf("%ld\n", count);

    *pbegin_filtered_arr = malloc(count * sizeof(int));
    *pend_filtered_arr = *pbegin_filtered_arr;
    if (*pbegin_filtered_arr == NULL)
    {
        return ERR_ALLOCATION;
    }

    while (pbegin_source < index)
    {
        **pend_filtered_arr = *pbegin_source;
        pbegin_source++;
        (*pend_filtered_arr)++;
    }
    if (*pbegin_source >= 0)
    {
        **pend_filtered_arr = *pbegin_source;
        (*pend_filtered_arr)++;
    }

    return ERR_OK;
}
