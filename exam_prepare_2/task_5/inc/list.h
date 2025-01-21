#ifndef LIST_H__
#define LIST_H__

#include <stdio.h>

typedef struct _node_type_ node_t;

int add_to_list(node_t **head, float x, float y);
void print_list(node_t *head);
void free_list(node_t *head);

void reverse_list(node_t **head);
void input_to_list(node_t **head, size_t *count);
void copy_squares(node_t **dest, node_t *src);
void print_only_rect(node_t *head);
#endif