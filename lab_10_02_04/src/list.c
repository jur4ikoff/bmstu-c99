#define _GNU_SOURCE

#include "list.h"
#include "constants.h"
#include "errors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Функция для инициализации односвязного списка
 * @return Указатель на односвязный список
 */
struct node_t_
{
    void *data;
    struct node_t_ *next;
};

// Создать лист
node_t *create_list(void)
{
    node_t *head = malloc(sizeof(node_t));
    if (head)
    {
        head->next = NULL;
        head->data = NULL;
    }
    return head;
}

/**
 * @brief Функция иттерируется по всему списку и применяет к ним apply_func
 * @param head Указатель на начало списка
 * @param apply_func Указатель на функцию
 * @param arg Аргумент, передаваемый в apply_func
 */
void apply_list(node_t *head, list_apply_func apply_func)
{
    node_t *cur = head;
    while (cur)
    {
        apply_func(cur->data);
        cur = cur->next;
    }
}

/**
 * @brief Освобождение памяти из-под списка и его данные
 * @param head Указатель на начало списка
 */
void free_full(node_t *head)
{
    node_t *current = head;
    while (current)
    {
        node_t *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

/**
 * @brief Освобождение памяти из-под листа
 * @param head Указатель на начало списка
 */
void free_list(node_t *head)
{
    node_t *current = head;
    while (current != NULL)
    {
        node_t *next = current->next;
        free(current);
        current = next;
    }
}

/**
 * @brief Функция ищет такую структуру, которая подходит под компаратор
 * @param head Указатель на начало списка
 * @param data Указатель на данные с для поиска
 * @param comparator Указатель на функцию компауратор
 * @return Возвращает элемент, соответствующий описанию
 */
node_t *find(node_t *head, const void *data, int (*comparator)(const void *, const void *))
{
    if (head == NULL)
        return NULL;

    if (comparator == NULL)
        return NULL;

    if (data == NULL)
        return NULL;

    node_t *cur = head;

    while (cur)
    {
        if (comparator(cur->data, data) == 0)
            return cur;
        cur = cur->next;
    }
    return NULL;
}

// Добавление в лист
int add_to_list(node_t **head, void *data)
{
    if (!*head)
    {
        node_t *node = malloc(sizeof(node_t));
        node->data = data;
        node->next = NULL;
        *head = node;
    }
    else
    {
        node_t *cur = (*head);
        while (cur->next)
        {
            cur = cur->next;
        }

        node_t *node = malloc(sizeof(node_t));
        if (node == NULL)
        {
            return ERR_MEMORY_ALLOCATION;
        }
        node->data = data;
        node->next = NULL;
        cur->next = node;
    }
    return ERR_OK;
}

// Удаление из начала списка
void *pop_front(node_t **head)
{
    if (head == NULL || *head == NULL)
    {
        return NULL;
    }
    node_t *temp = *head;
    *head = (*head)->next;
    void *data = temp->data;

    temp->next = NULL;
    temp->data = NULL;
    free(temp);
    return data;
}

/**
 * @brief Поверхностное копирование списка
 */
int copy(node_t *head, node_t **new_head)
{
    if (!head)
        return ERR_HEAD;

    int rc = ERR_OK;
    node_t *cur = head;
    while (cur)
    {
        if ((rc = add_to_list(new_head, cur->data)) != ERR_OK)
            return rc;
        cur = cur->next;
    }

    return ERR_OK;
}

// Сортировка вставками
void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void *, const void *))
{
    if (element == NULL || comparator == NULL)
        return;

    if (*head == NULL || head == NULL)
    {
        *head = element;
        return;
    }

    node_t *cur = *head;
    node_t *prev = NULL;

    while (cur && comparator(cur->data, element->data) < 0)
    {
        prev = cur;
        cur = cur->next;
    }
    if (prev)
    {
        prev->next = element;
    }
    else
        *head = element;

    element->next = cur;
}

// Создание ноды
node_t *create_node(void *data)
{
    node_t *node = malloc(sizeof(node_t));
    if (node == NULL)
    {
        return NULL;
    }

    node->data = data;
    node->next = NULL;

    return node;
}

// Сортировка списка
node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
    if (comparator == NULL)
        return NULL;

    node_t *sorted_head = NULL;
    while (head)
    {
        void *value = pop_front(&head);
        node_t *new_node = create_node(value);
        sorted_insert(&sorted_head, new_node, comparator);
    }
    return sorted_head;
}

void *get_data(node_t *node)
{
    if (node == NULL)
        return NULL;

    return node->data;
}
