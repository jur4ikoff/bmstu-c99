#define _GNU_SOURCE

#include "linked_list.h"
#include "auto.h"
#include "constants.h"
#include "errors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1 - Если пустой, иначе 0
/*static int is_empty(const node_t *head)
{
    return head == NULL;
}*/

/**
 * @brief Функция для инициализации односвязного списка
 * @return Указатель на односвязный список
 */
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

// Считывание одной структуры из файла
static int read_auto_info(node_t **node, FILE *file)
{
    int year, rc;
    long long price;
    // *is_string_read = 0;
    char *model_name = NULL;
    if ((rc = input_string(&model_name, file)) != ERR_OK)
    {
        free(model_name);
        return rc;
    }

    if (fscanf(file, "%d %lld", &year, &price) != 2)
    {
        free(model_name);
        return ERR_NUMBER;
    }
    fgetc(file);

    if (year < 0)
    {
        free(model_name);
        return ERR_NUMBER;
    }

    // Выделение паумяти под новую
    auto_t *new_auto = malloc(sizeof(auto_t));
    if (new_auto == NULL)
    {
        free(model_name);
        rc = ERR_MEMORY_ALLOCATION;
    }

    new_auto->model_name = model_name;
    new_auto->year = year;
    new_auto->price = price;

    // Создание нового узла
    *node = malloc(sizeof(node_t));
    if (*node == NULL)
    {
        free(new_auto->model_name);
        free(new_auto);
        return ERR_MEMORY_ALLOCATION;
    }

    (*node)->data = new_auto;
    (*node)->next = NULL;

    return rc;
}

/**
 * @brief Функция читает лист из файла
 * @param head "Голова" листа
 * @param file Файловый указательно
 * @return Код возврта
 */
int read_list(node_t **head, FILE *file)
{
    int rc = ERR_OK;
    node_t *tail = NULL;

    do
    {
        node_t *new_node = NULL;
        if ((rc = read_auto_info(&new_node, file)) != ERR_OK)
        {
            free(new_node);
            break;
        }
        // printf("%s\n", ((auto_t *)(new_node->data))->model_name);
        if (*head == NULL)
        {
            *head = new_node;
            tail = new_node;
        }
        else
        {
            tail->next = new_node;
            tail = new_node;
        }
    } while (!feof(file));

    return rc;
}

// Функция для вывода на экран односвязного списка
void print_list(const node_t *head)
{
    const node_t *ptr = head;
    while (ptr != NULL)
    {
        auto_t *auto_data = (auto_t *)ptr->data;
        print_auto(auto_data);
        ptr = ptr->next;
    }
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
 * @brief Запись односвязного списка в файл
 * @param head Указатель на начало списка
 * @param file Файловый указатель
 */
void write_list(const node_t *head, FILE *file)
{
    const node_t *temp = head;
    while (temp)
    {
        auto_t *auto_data = (auto_t *)temp->data;
        fprintf(file, "%s\n%d\n%lld\n", auto_data->model_name, auto_data->year, auto_data->price);
        temp = temp->next;
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
        auto_t *auto_info = (auto_t *)current->data;
        free(auto_info->model_name);
        free(auto_info);
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

// Вывод на экран данных об элементе
void print_node(node_t *node)
{
    print_auto(node->data);
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
