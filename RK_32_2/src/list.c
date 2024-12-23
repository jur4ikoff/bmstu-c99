#define _GNU_SOURCE

#include "list.h"
#include "errors.h"
#include <stdlib.h>
#include <stdio.h>
#include "students.h"
#include "constants.h"
#include <string.h>

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

/*int push(node_t **headd, void *data)
{
    node_t *head = *headd;
    node_t *node = malloc(sizeof(node_t));
    if (node == NULL)
    {
        return ERR_MEMORY_ALLOCATION;
    }

    if (!head)
    {
        *headd = node;
    }
    else
    {
        node_t *cur = head;
        while (cur->next != NULL)
        {
            cur = cur->next;
        }

        node->data = data;
        node->next = NULL;
        cur->next = node;
    }
    return ERR_OK;
}
*/

void apply_list(node_t *head, list_apply_func apply_func)
{
    node_t *src = head;
    while (src)
    {
        apply_func(src->data);
        src = src->next;
    }
}

// Считывание одной структуры из файла
static int read_student(node_t **node, FILE *file)
{
    int year, rc;
    char *name = NULL, *group = NULL;
    if ((rc = input_string(&name, file)) != ERR_OK)
    {
        free(name);
        return rc;
    }
    if (strlen(name) > MAX_NAME)
    {
        free(name);
        return ERR_INPUT;
    }

    if (fscanf(file, "%d", &year) != 1)
    {
        free(name);
        return ERR_INPUT;
    }
    fgetc(file);
    if (year < 0)
    {
        free(name);
        return ERR_INPUT;
    }

    if ((rc = input_string(&group, file)) != ERR_OK)
    {
        free(name);
        free(group);
        return rc;
    }

    if (strlen(group) > MAX_GROUP)
    {
        free(name);
        free(group);
        return ERR_INPUT;
    }

    student_t *student = malloc(sizeof(student_t));
    if (student == NULL)
    {
        free(name);
        free(group);
        rc = ERR_MEMORY_ALLOCATION;
    }
    student->second_name = name;
    student->year = year;
    student->group = group;

    // Создание нового узла
    *node = malloc(sizeof(node_t));
    if (*node == NULL)
    {
        free(student->second_name);
        free(student->group);
        free(student);
        return ERR_MEMORY_ALLOCATION;
    }

    (*node)->data = student;
    (*node)->next = NULL;

    return rc;
}

int read_list(node_t **head, FILE *file)
{
    int rc = ERR_OK;
    node_t *tail = NULL;

    do
    {
        node_t *new_node = NULL;
        if ((rc = read_student(&new_node, file)) != ERR_OK)
        {
            free(new_node);
            break;
        }
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

    if (feof(file))
        rc = ERR_OK;
    return rc;
}

void remove_duplicates(node_t **head)
{
    if (head == NULL || *head == NULL)
        return;

    node_t *current = *head;
    node_t *prev = NULL;
    node_t *temp;
    char seen[MAX_STRUCTS][MAX_NAME];
    int count = 0;

    while (current != NULL)
    {
        student_t *student = (student_t *)current->data;
        int is_duplicate = 0;

        // Проверяем, была ли фамилия уже сохранена
        for (int i = 0; i < count; i++)
        {
            if (strcmp(seen[i], student->second_name) == 0)
            {
                is_duplicate = 1;
                break;
            }
        }

        if (is_duplicate)
        {
            temp = current;
            if (prev)
            {
                prev->next = current->next;
            }
            else
            {
                *head = current->next;
            }
            current = current->next;

            student_t *data = temp->data;
            free(data->second_name);
            free(data->group);
            free(data);
            free(temp);
        }
        else
        {
            // Сохраняем фамилию и продолжаем
            if (count == MAX_STRUCTS)
                return;
            strcpy(seen[count++], student->second_name);
            prev = current;
            current = current->next;
        }
    }
}

void free_list(node_t *head)
{
    node_t *cur = head;

    while (cur)
    {
        node_t *next = cur->next;
        student_t *data = (student_t *)cur->data;
        free(data->group);
        free(data->second_name);
        free(data);
        free(cur);
        cur = next;
    }
}