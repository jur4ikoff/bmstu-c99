#ifndef LIST_H__
#define LIST_H__

#include <stdio.h>

typedef struct node_t_
{
    void *data;
    struct node_t_ *next;
} node_t;

typedef void (*list_apply_func)(void *);

node_t *create_list(void);
void apply_list(node_t *head, list_apply_func apply_func);
int read_list(node_t **head, FILE *file);
void remove_duplicates(node_t **head);
void free_list(node_t *head);
#endif
