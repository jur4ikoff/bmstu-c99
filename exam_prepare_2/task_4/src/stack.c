#include "stack.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _node_type_
{
    char el;
    struct _node_type_ *next;
};

static node_t *create_node(char data)
{
    node_t *node = malloc(sizeof(*node));
    if (!node)
        return NULL;

    node->next = NULL;
    node->el = data;
    return node;
}

static void free_node(node_t *node)
{
    free(node);
}

int push_stack(node_t **top, char data)
{
    if (top == NULL)
        return ERR_ARG;

    node_t *new_node = create_node(data);
    if (!new_node)
        return ERR_MEMORY;

    if (*top == NULL)
    {
        *top = new_node;
        return ERR_OK;
    }

    new_node->next = (*top);
    *top = new_node;
    return ERR_OK;
}

void free_stack(node_t *top)
{
    node_t *temp = NULL;
    while (top)
    {
        temp = top;
        top = top->next;
        free_node(temp);
    }
}

void print_stack(node_t *stack)
{
    node_t *temp = stack;
    while (temp)
    {
        if (temp->next)
            printf("%c", temp->el);
        else
            printf("%c\n", temp->el);
        temp = temp->next;
    }
}

void pop_stack(node_t **top)
{
    if (*top == NULL)
        return;
    node_t *temp = *top;
    *top = (*top)->next;
    free_node(temp);
}

size_t stack_len(node_t *top)
{
    size_t len = 0;
    node_t *temp = top;
    while (temp)
    {
        len++;
        temp = temp->next;
    }
    return len;
}

void convert_to_stack(node_t **top, char *string)
{
    size_t len = strlen(string);
    for (size_t i = 0; i < len; i++)
    {
        if (string[i] == '#')
            pop_stack(top);
        else
            push_stack(top, string[i]);
    }
}

void convert_to_string_reverse(node_t *top, char *string, size_t len)
{
    string[0] = '\'';
    node_t *temp = top;
    int i = 0;
    while (temp)
    {
        string[len - 3 - i] = temp->el;
        i++;
        temp = temp->next;
    }

    string[len - 2] = '\'';
    string[len - 1] = 0;
}
