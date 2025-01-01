#include "myarrlib.h"
#include "errors.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ABS(x) ((x >= 0) ? (x) : (-x))
#define ARR_MAX_SIZE 10000

/**
 * @brief Функция реализует цикличный сдвиг массива влево на величину shift
 * @param[in] arr Массив
 * @param[in] count Количество элементов. Максимальный размер 10000 элементов
 * @param[in] shift Сдвиг
 */
int shift_arr(int *arr, size_t count, int shift)
{
    // Валидация указателя на массив
    if (arr == NULL)
        return ERR_POINTER;

    // Валидация размера
    if (count > ARR_MAX_SIZE || count == 0)
        return ERR_SIZE;

    // Проверка идеальной ситуации
    if (count == 1 || shift == 0)
        return ERR_OK;

    int *temp = NULL;
    if (shift > 0)
    {
        // Нормализация сдвига
        shift %= count;

        // Выделение памяти под временный массив
        temp = malloc(sizeof(int) * shift);
        if (temp == NULL)
            return ERR_MEMORY_ALLOCATION;

        for (size_t i = 0; i < (size_t)shift; i++)
        {
            temp[i] = arr[i];
        }

        memmove(arr, arr + shift, (count - shift) * sizeof(int));
        for (size_t i = 0; i < (size_t)shift; i++)
        {
            arr[count - shift + i] = temp[i];
        }
    }
    else
    {
        // Цикличный сдвиг вправо
        shift = (ABS(shift) % count);
        temp = malloc(sizeof(int) * shift);
        if (!temp)
            return ERR_MEMORY_ALLOCATION;
        for (size_t i = 0; i < (size_t)shift; i++)
        {
            temp[i] = arr[count - shift + i];
        }

        memmove(arr + shift, arr, sizeof(int) * (count - shift));
        for (size_t i = 0; i < (size_t)shift; i++)
        {
            arr[i] = temp[i];
        }
    }

    // Освобождение памяти из-под временного массива и выход из функции
    free(temp);
    return ERR_OK;
}

// Возвращает количество чисел полных квадратов до n
static int sqrt_number_before_n(int **num, size_t n)
{
    if (num == 0)
        return 0;

    *num = malloc(sizeof(int) * ((int)sqrt(n) + 3));
    size_t index = 0;
    for (size_t i = 0; i < (size_t)sqrt(n) + 1; i++)
    {
        if (i * i <= n)
        {
            (*num)[index] = i * i;
            index++;
        }
    }

    return index;
}

static int max(int *arr, size_t n)
{
    int max = -100000;
    for (size_t i = 0; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }

    return max;
}

static int is_contain(int *arr, size_t count, int el)
{
    for (size_t i = 0; i < count; i++)
    {
        if (arr[i] == el)
        {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Функция из одного массива помещает в другой элементы первого, которые являются полными квадратами.
 * Примечание: сначала вызвать функцию библиотеки, чтобы узнать требуемый размер массива, затем выделить память и повторно вызвать функцию.
 * @param[in] dst Массив в который будет происходить копирование
 * @param[in] src Массив из которого будут копироваться элементы
 * @param[in] src_len Длина исходного массива
 * @param[in] dst_len Указатель на длинну результирующего массива
 */
int filter(int *dst, int *src, size_t src_len, int *dst_len)
{
    if (src == NULL)
        return ERR_POINTER;

    if (src_len == 0 || src_len > ARR_MAX_SIZE)
        return ERR_SIZE;

    int *sqrt_num = NULL;
    int sqrt_count = sqrt_number_before_n(&sqrt_num, max(src, src_len));
    // print_arr(sqrt_num, sqrt_count);

    if (dst == NULL)
    {
        *dst_len = 0;
        for (size_t i = 0; i < src_len; i++)
        {
            if (is_contain(sqrt_num, sqrt_count, src[i]))
            {
                (*dst_len)++;
            }
        }
        free(sqrt_num);
        if (*dst_len == 0)
            return ERR_EMPTY_OUT;
        return ERR_OK;
    }

    // Копирование должно проводиться только при инициализированных переменных
    if (dst == NULL || dst_len == NULL)
    {
        free(sqrt_num);
        return ERR_POINTER;
    }

    size_t index = 0;
    for (size_t i = 0; i < src_len; i++)
    {
        if (is_contain(sqrt_num, sqrt_count, src[i]))
        {
            dst[index++] = src[i];
        }
    }

    free(sqrt_num);
    return ERR_OK;
}
