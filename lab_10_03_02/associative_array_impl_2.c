#define _GNU_SOURCE

#include "associative_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Реализация ассоциативного массива на связном списке
*/

typedef struct data_t_
{
    char *key;
    int value;
} data_t;

typedef struct node_type_
{
    data_t data;
    struct node_type_ *next;
} node_t;

struct assoc_array_type
{
    // Указатель на данные для хранения пар ключ-значение
    node_t *head;
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

    arr->head = NULL;
    return arr;
}

static void free_list(node_t *head)
{
    node_t *cur = head;
    while (cur)
    {
        node_t *next = cur->next;
        free(cur->data.key);
        free(cur);

        cur = next;
    }
    head = NULL;
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

    free_list((*arr)->head);
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

    data_t data = {0};
    data.key = strdup(key);
    data.value = num;

    node_t *new = malloc(sizeof(*new));
    if (new == NULL)
        return ASSOC_ARRAY_MEM;
    new->data = data;
    new->next = NULL;

    node_t *cur = arr->head;
    if (cur == NULL)
    {
        arr->head = new;
        return ASSOC_ARRAY_OK;
    }
    while (cur->next)
    {
        cur = cur->next;
    }
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

    for (node_t *cur = arr->head; cur != NULL; cur->next)
    {
        printf("%s -> %d\n", cur->data.key, cur->data.value);
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
    if (strlen(key) < 1 || arr == NULL || num == NULL || key == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *cur = arr->head;
    while (cur != NULL)
    {
        if (cur->data.key)
        {
            if (strcmp(cur->data.key, key) == 0)
            {
                *num = &(cur->data.value);
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
    if (arr == NULL || key == NULL || strlen(key) < 1)
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *cur = arr->head;
    node_t *prev = NULL;
    if (cur == NULL)
        return ASSOC_ARRAY_NOT_FOUND;

    while (cur)
    {
        if (strcmp(cur->data.key, key) == 0)
        {
            if (prev == NULL)
            {
                arr->head = cur->next;
                free(cur->data.key);
                free(cur);
            }
            else
            {
                prev->next = cur->next;
                free(cur->data.key);
                free(cur);
            }
            return ASSOC_ARRAY_OK;
        }
        prev = cur;
        cur = cur->next;
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
    node_t *cur = arr->head;
    node_t *next = NULL;
    if (cur == NULL)
        return ASSOC_ARRAY_OK;
    while (cur)
    {
        next = cur->next;
        if ((rc = assoc_array_remove(arr, cur->data.key)) != ASSOC_ARRAY_OK)
            return rc;
        cur = next;
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

    node_t *cur = arr->head;
    while (cur)
    {
        action(cur->data.key, &(cur->data.value), param);
        cur = cur->next;
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

    node_t *cur = arr->head;
    if (cur == NULL)
        return ASSOC_ARRAY_NOT_FOUND;

    char *min_key = cur->data.key;
    *num = &(cur->data.value);

    while (cur)
    {
        if (strcmp(cur->data.key, min_key) < 0)
        {
            min_key = cur->data.key;
            *num = &(cur->data.value);
        }
        cur = cur->next;
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

    node_t *cur = arr->head;
    if (cur == NULL)
        return ASSOC_ARRAY_NOT_FOUND;

    char *min_key = cur->data.key;
    *num = &(cur->data.value);

    while (cur)
    {
        if (strcmp(cur->data.key, min_key) > 0)
        {
            min_key = cur->data.key;
            *num = &(cur->data.value);
        }
        cur = cur->next;
    }

    return ASSOC_ARRAY_OK;
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
