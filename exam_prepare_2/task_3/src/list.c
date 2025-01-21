#include "list.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>

struct _node_type_
{
    int el;
    struct _node_type_ *next;
};

static node_t *create_node(int data)
{
    node_t *new_node = malloc(sizeof(*new_node));
    if (new_node == NULL)
        return NULL;

    new_node->el = data;
    new_node->next = NULL;
    return new_node;
}

static void free_node(node_t *node)
{
    free(node);
}

void free_list(node_t *head)
{
    node_t *temp = NULL;
    while (head)
    {
        temp = head;
        head = head->next;
        free_node(temp);
    }
}

err_t push_list(node_t **head, int data)
{
    if (head == NULL)
        return ERR_ARGS;

    node_t *new_node = create_node(data);
    if (!new_node)
        return ERR_MEMORY;

    if (*head == NULL)
    {
        *head = new_node;
        return ERR_OK;
    }

    node_t *temp = *head;
    while (temp->next)
    {
        temp = temp->next;
    }

    temp->next = new_node;
    return ERR_OK;
}

void print_list(node_t *head)
{
    node_t *temp = head;
    while (temp)
    {
        if (temp->next)
            printf("%d ", temp->el);
        else
            printf("%d\n", temp->el);
        temp = temp->next;
    }
}

void convert_arr_to_list(node_t **head, int *arr, size_t count)
{
    if (head == NULL || arr == NULL)
        return;

    for (size_t i = 0; i < count; i++)
    {
        push_list(head, arr[i]);
    }
}

void delete_by_task(node_t *head)
{
    node_t *prev = head;
    if (head->next == NULL)
        return;
    node_t *cur = head->next;

    while (cur->next)
    {
        if (cur->el > cur->next->el && cur->el > prev->el)
        {
            node_t *temp = cur;
            prev->next = cur->next;
            free_node(temp);
            cur = prev->next;
        }
        else
        {
            prev = cur;
            cur = cur->next;
        }
    }
}