#include "list.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _node_type_
{
    char *data;
    struct _node_type_ *next;
};

node_t *create_node(char *string)
{
    if (string == NULL)
        return NULL;

    node_t *node = malloc(sizeof(*node));
    if (node == NULL)
        return NULL;

    node->next = NULL;
    node->data = string;
    return node;
}

void free_node(node_t *node)
{
    free(node->data);
    free(node);
}

int add_list(node_t **head, char *string)
{
    if (head == NULL || string == NULL)
        return ERR_ARG;

    node_t *new = create_node(string);
    if (new == NULL)
    {
        return ERR_MEMORY_AlLOCATION;
    }

    if (*head == NULL)
    {
        *head = new;
        return ERR_OK;
    }
    node_t *cur = *head;
    while (cur->next)
    {
        cur = cur->next;
    }

    cur->next = new;
    return ERR_OK;
}

void print_list(node_t *head)
{
    if (head == NULL)
        return;

    node_t *cur = head;
    while (cur)
    {
        printf("%s\n", cur->data);
        cur = cur->next;
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

size_t len_string_in_list(node_t *head)
{
    size_t len = 0;
    node_t *cur = head;

    while (cur)
    {
        len += (strlen(cur->data) + 1);
        cur = cur->next;
    }

    return len;
}

int merge_list(node_t *head, char *string)
{
    if (head == NULL || string == NULL)
        return ERR_ARG;
    node_t *cur = head;
    string[0] = 0;
    while (cur)
    {
        strcat(string, cur->data);
        size_t len = strlen(string);
        string[len] = ' ';    
        string[len + 1] = 0;   
        cur = cur->next;
    }

    string[strlen(string)] = 0;

    return ERR_OK;
}
