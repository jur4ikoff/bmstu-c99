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
    // Указатель на данные для хранения пар ключ-значение
    data_t *data;
    // Следующий элемент
    assoc_array_t next;
};

/**
 * Создает объект ассоциативный массив.
 *
 * \return Созданный объект или NULL
 */
assoc_array_t assoc_array_create(void)
{
    assoc_array_t arr = malloc(sizeof(*arr));
    if (!arr)
        return NULL;

    arr->data = NULL;
    arr->next = NULL;
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
    assoc_array_t cur = *arr;
    while (cur)
    {
        assoc_array_t next = cur->next;
        free((cur)->data);
        free(cur);

        cur = next;
    }
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

    data_t *data = NULL;
    data = malloc(sizeof(data_t));
    if (data == NULL)
        return ASSOC_ARRAY_MEM;
    data->key = strdup(key);
    data->value = num;

    assoc_array_t cur = arr;
    while (cur->next)
    {
        cur = cur->next;
    }
    assoc_array_t new = malloc(sizeof(*new));
    if (new == NULL)
        return ASSOC_ARRAY_MEM;
    new->data = data;
    new->next = NULL;

    cur->next = new;
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

    for (assoc_array_t cur = arr; cur != NULL; cur->next)
    {
        printf("%s -> %d\n", cur->data->key, cur->data->value);
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
    /*
    const assoc_array_t current = arr; // Начинаем с первого элемента

    while (current != NULL) {
        if (current->data != NULL && strcmp(current->data->key, key) == 0) {
            *num = &current->data->value; // Возвращаем адрес значения
            return ASSOC_ARRAY_SUCCESS; // Успех, ключ найден
        }
        // Переходим к следующему элементу
        current = current->next;
    }

    return ASSOC_ARRAY_NOT_FOUND; // Ключ не найден
}
*/
    if (strlen(key) < 1 || arr == NULL || num == NULL || key == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;

    assoc_array_t cur = arr;
    while (cur != NULL)
    {
        if (cur->data && cur->data->key)
        {
            if (strcmp(cur->data->key, key) == 0)
            {
                *num = &(cur->data->value);
                return ASSOC_ARRAY_OK;
            }
        }
        cur = cur->next;
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
    return ASSOC_ARRAY_OK;
    /*if (!key || strlen(key) < 1 || arr == NULL)
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

    return ASSOC_ARRAY_NOT_FOUND;*/
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
    /*if (arr == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;

    int rc = ASSOC_ARRAY_OK;
    while (arr->size)
    {
        if ((rc = assoc_array_remove(arr, arr->data[0].key)) != ASSOC_ARRAY_OK)
            return rc;
    }

    return ASSOC_ARRAY_OK;*/
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
    return ASSOC_ARRAY_OK;
    /*if (arr == NULL || action == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (size_t i = 0; i < arr->size; i++)
    {
        action(arr->data[i].key, &arr->data[i].value, param);
    }

    return ASSOC_ARRAY_OK;*/
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
    return ASSOC_ARRAY_OK;
    /*if (arr == NULL || num == NULL)
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

    return ASSOC_ARRAY_OK;*/
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
    return ASSOC_ARRAY_OK;
    /*if (arr == NULL || num == NULL)
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

    return ASSOC_ARRAY_OK;*/
}

/*
int main(void)
{
    assoc_array_t arr = assoc_array_create();
    int rc = ASSOC_ARRAY_OK;
    rc = assoc_array_insert(arr, "test", 1);
    if (rc != 0)
        return rc;

    int *el_1 = NULL;
    rc = assoc_array_find(arr, "test", &el_1);

    if (rc != 0)
        return rc;
    rc = 1;
    if (el_1 && *el_1 == 1)
        rc = ASSOC_ARRAY_OK;
    assoc_array_clear(arr);
    assoc_array_destroy(&arr);
    return rc;
}*/