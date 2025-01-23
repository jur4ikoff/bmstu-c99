#include "list.h"
#include "constants.h"
#include <stdlib.h>
#include <stdio.h>

struct _node_type_
{
    int value;
    struct _node_type_ *next; 
};

node_t *create_node(int data)
{
    node_t *node = malloc(sizeof(*node));
    if (!node)
        return NULL;

    node->next = NULL;
    node->value = data;
    return node;
}

void free_list(node_t *head)
{
    node_t *temp = NULL;
    while (head)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void print_list(node_t *head)
{
    node_t *temp = head;
    while (temp)
    {
        printf("%d ", temp->value);
        temp = temp->next;
    }
    printf("\n");
}

int append(node_t **head, int data)
{
    if (head == NULL)
        return ERR_ARG;

    node_t *new_node = create_node(data);
    if (!new_node)
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
