#include "queue.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>

struct _node_type_
{
    char el;
    struct _node_type_ *next;
};

static node_t *create_node(char data)
{
    node_t *new = malloc(sizeof(*new));
    if (new == NULL)
        return NULL;

    new->next = NULL;
    new->el = data;

    return new;
}

static void free_node(node_t *node)
{
    free(node);
}

int add_queue(node_t **head, char data)
{
    if (head == NULL)
        return ERR_ARG;

    node_t *new_node = create_node(data);
    if (new_node == NULL)
        return ERR_MEM;

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

char pop_queue(node_t **head, char symb_to_del)
{
    if (head == NULL)
        return ERR_ARG;

    node_t *temp = *head;
    *head = (*head)->next;
    char res = temp->el;
    free_node(temp);
    return res;
}

void print_queue(node_t *head)
{
    if (head == NULL)
        return;

    node_t *temp = head;
    while (temp)
    {
        if (temp->next)
            printf("%c", temp->el);
        else
            printf("%c\n", temp->el);
        temp = temp->next;
    }
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

void convert_int_to_list(node_t **head, int number)
{
    while (number > 0)
    {
        add_queue(head, (number % 10) + '0');
        number /= 10;
    }
}
