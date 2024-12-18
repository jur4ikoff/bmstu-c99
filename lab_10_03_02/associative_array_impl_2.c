#define _GNU_SOURCE

#include "associative_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Реализация ассоциативного массива на динамическом массиве
*/

// Размер по умолчанию
#define CAPACITY_INIT 10

typedef struct data_t_
{
    char *key;
    int value;
} data_t;

struct assoc_array_type
{
    size_t size;
    size_t capacity;

    // Массив для хранения пар ключ-значение
    data_t *data;
};

/**
 * Создает объект ассоциативный массив.
 *
 * \return Созданный объект или NULL
 */
assoc_array_t assoc_array_create(void)
{
    assoc_array_t arr = malloc(sizeof(assoc_array_t) * CAPACITY_INIT);
    if (!arr)
        return NULL;

    arr->size = 0;
    arr->capacity = CAPACITY_INIT;
    arr->data = malloc(sizeof(data_t) * arr->capacity);
    if (!arr->data)
    {
        free(arr);
        return NULL;
    }

    return arr;
}

/**
 * Удаляет объект ассоциативный массив.
 *
 * \param[in,out] arr - описатель массив
 *
 * После вызова этой функции переменная, переданная в качестве параметра, имеет
 * значение NULL.
 */
void assoc_array_destroy(assoc_array_t *arr)
{
    // free((*arr)->data->key);
    free((*arr)->data);
    free(*arr);
    *arr = NULL;
}

/**
 * Добавляе пару "ключ-значение" в ассоциативный массив.
 *
 * \param[in,out] arr - описатель массива
 * \param[in] key - ключ
 * \param[in] num - значение
 *
 * \note Ключ не может быть пустой строкой.
 *
 * \return ASSOC_ARRAY_OK или код ошибки (ASSOC_ARRAY_INVALID_PARAM, ASSOC_ARRAY_MEM, ASSOC_ARRAY_KEY_EXISTS)
 */
assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    if (arr == NULL || strlen(key) < 1)
        return ASSOC_ARRAY_INVALID_PARAM;

    int *el = NULL;
    if (assoc_array_find(arr, key, &el) == ASSOC_ARRAY_OK)
        return ASSOC_ARRAY_KEY_EXISTS;
    (void)el;

    data_t data = { 0 };
    data.key = strdup(key);
    data.value = num;

    if (arr->size < arr->capacity)
        arr->data[arr->size] = data;
    else
    {
        arr->capacity *= 2;
        data_t *res = realloc(arr->data, sizeof(data_t) * arr->capacity);
        if (!res)
            return ASSOC_ARRAY_MEM;

        arr->data = res;
        arr->data[arr->size] = data;
    }
    arr->size++;
    return ASSOC_ARRAY_OK;
}

/**
 * Возвращает значение по ключу.
 *
 * \param[in] arr - описатель массива
 * \param[in] key - ключ
 * \param[out] num - указатель на значение, соответствующее ключу (в случае успеха)
 *
 * \note Ключ не может быть пустой строкой.
 *
 * \return ASSOC_ARRAY_OK или код ошибки (ASSOC_ARRAY_INVALID_PARAM, ASSOC_ARRAY_NOT_FOUND)
 */
void assoc_array_print(assoc_array_t arr)
{
    if (arr == NULL)
        return;

    for (size_t i = 0; i < arr->size; i++)
    {
        printf("%s -> %d\n", arr->data[i].key, arr->data[i].value);
    }
}

/**
 * Возвращает значение по ключу.
 *
 * \param[in] arr - описатель массива
 * \param[in] key - ключ
 * \param[out] num - указатель на значение, соответствующее ключу (в случае успеха)
 *
 * \note Ключ не может быть пустой строкой.
 *
 * \return ASSOC_ARRAY_OK или код ошибки (ASSOC_ARRAY_INVALID_PARAM, ASSOC_ARRAY_NOT_FOUND)
 */
assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if (strlen(key) < 1 || arr == NULL || num == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (arr->size == 0)
        return ASSOC_ARRAY_NOT_FOUND;

    for (size_t i = 0; i < arr->size; i++)
    {
        if (strcmp(arr->data[i].key, key) == 0)
        {
            *num = &arr->data[i].value;
            return ASSOC_ARRAY_OK;
        }
    }

    return ASSOC_ARRAY_NOT_FOUND;
}

/**
 * Удаляет значение по ключу.
 *
 * \param[in,out] arr - описатель массива
 * \param[in] key - ключ
 *
 * \return ASSOC_ARRAY_OK или код ошибки (ASSOC_ARRAY_INVALID_PARAM, ASSOC_ARRAY_MEM, ASSOC_ARRAY_NOT_FOUND)
 */
assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    if (!key || strlen(key) < 1 || arr == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    
    if (arr->size == 0)
        return ASSOC_ARRAY_NOT_FOUND;

    for (size_t i = 0; i < arr->size; i++)
    {
        if (strcmp(arr->data[i].key, key) == 0)
        {
            // Освобождаем память под ключ, если он был выделен динамически
            free(arr->data[i].key);
            // Сдвигаем элементы массива влево
            memmove(&arr->data[i], &arr->data[i + 1], sizeof(data_t) * (arr->size - i - 1));

            // Уменьшаем размер массива
            arr->size--;
            // Уменьшаем размер массива вдвое, если он стал пустым
            if (arr->size < arr->capacity / DECR_COEF)
                arr->capacity /= INCR_COEF;
            arr->data = realloc(arr->data, sizeof(data_t) * arr->capacity);
            if (!arr->data)
                return ASSOC_ARRAY_MEM;

            return ASSOC_ARRAY_OK;
        }
    }

    return ASSOC_ARRAY_NOT_FOUND;
}

/**
 * Очищает ассоциативный массив (т.е. массив становится пустым).
 *
 * \param[in,out] arr - описатель массива
 *
 * \return ASSOC_ARRAY_OK или код ошибки (ASSOC_ARRAY_INVALID_PARAM)
 */
assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (arr == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;

    int rc = ASSOC_ARRAY_OK;
    while (arr->size)
    {
        if ((rc = assoc_array_remove(arr, arr->data[0].key)) != ASSOC_ARRAY_OK)
            return rc;
    }

    return ASSOC_ARRAY_OK;
}

/**
 * Применяет к значениям указанное действие.
 *
 * \param[in] arr - описатель массива
 * \param[in] action - указатель на функцию обратного вызова для обработки очередного значения
 * \param[in] param - параметр функции обратного вызова (может быть NULL)
 *
 * \return ASSOC_ARRAY_OK или код ошибки (ASSOC_ARRAY_INVALID_PARAM)
 */
assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (arr == NULL || action == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (size_t i = 0; i < arr->size; i++)
    {
        action(arr->data[i].key, &arr->data[i].value, param);
    }

    return ASSOC_ARRAY_OK;
}

/**
 * Возвращает значение соответствующее минимальному ключу.
 *
 * \param[in] arr - описатель массива
 * \param[out] num - указатель на значение, соответствующее минимальному ключу (в случае успеха)
 *
 * \return ASSOC_ARRAY_OK или код ошибки (ASSOC_ARRAY_INVALID_PARAM, ASSOC_ARRAY_NOT_FOUND - т.е. массив пустой)
 */
assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (arr == NULL || num == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (arr->size == 0)
        return ASSOC_ARRAY_NOT_FOUND;

    char *min_key = arr->data[0].key;
    *num = &arr->data[0].value;
    for (size_t i = 1; i < arr->size; i++)
    {
        if (strcmp(arr->data[i].key, min_key) < 0)
        {
            min_key = arr->data[i].key;
            *num = &arr->data[i].value;
        }
    }

    return ASSOC_ARRAY_OK;
}

/**
 * Возвращает значение соответствующее максимальному ключу.
 *
 * \param[in] arr - описатель массива
 * \param[out] num - указатель на значение, соответствующее максимальному ключу (в случае успеха)
 *
 * \return ASSOC_ARRAY_OK или код ошибки (ASSOC_ARRAY_INVALID_PARAM, ASSOC_ARRAY_NOT_FOUND - т.е. массив пустой)
 */
assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (arr == NULL || num == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (arr->size == 0)
        return ASSOC_ARRAY_NOT_FOUND;

    char *min_key = arr->data[0].key;
    *num = &arr->data[0].value;
    for (size_t i = 1; i < arr->size; i++)
    {
        if (strcmp(arr->data[i].key, min_key) > 0)
        {
            min_key = arr->data[i].key;
            *num = &arr->data[i].value;
        }
    }

    return ASSOC_ARRAY_OK;
}
