#include "list.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>

#define ABS(x) ((x) > 0 ? (x) : ((x) * -1))
struct _node_type_
{
    float x;
    float y;
    struct _node_type_ *next;
};

static node_t *create_node(float x, float y)
{
    node_t *node = malloc(sizeof(*node));
    if (!node)
        return NULL;

    node->x = x, node->y = y;
    node->next = NULL;
    return node;
}

static void free_node(node_t *node)
{
    free(node);
}

int add_to_list(node_t **head, float x, float y)
{
    if (head == NULL)
    {
        return ERR_ARGS;
    }

    node_t *new_node = create_node(x, y);
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
        printf("%f %f\n", temp->x, temp->y);
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

void input_to_list(node_t **head, size_t *count)
{
    *count = 0;
    float x, y;
    while (scanf("%f %f", &x, &y) == 2)
    {
        (*count)++;
        add_to_list(head, x, y);
    }
}

void copy_squares(node_t **dest, node_t *src)
{
    node_t *temp = src;
    while (temp)
    {
        if (ABS(temp->x - temp->y) < EPS)
        {
            add_to_list(dest, temp->x, temp->y);
        }
        temp = temp->next;
    }
}

void print_only_rect(node_t *head)
{
    node_t *temp = head;
    while (temp)
    {
        if (ABS(temp->x - temp->y) > EPS)
        {
            printf("%f %f\n", temp->x, temp->y);
        }
        temp = temp->next;
    }
}

void reverse_list(node_t **head)
{
    node_t *prev = NULL;
    node_t *cur = *head;
    node_t *next = NULL;

    while (cur)
    {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    *head = prev;
}
