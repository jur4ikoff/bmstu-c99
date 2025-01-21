#ifndef LIST_H__
#define LIST_H__

#include "constants.h"
#include <stdio.h>

typedef struct _node_type_ node_t;

node_t *create_node(char *string);
void free_node(node_t *node);
int add_list(node_t **head, char *string);
void print_list(node_t *head);
void free_list(node_t *head);
size_t len_string_in_list(node_t *head);
int merge_list(node_t *head, char *string);
#endif
