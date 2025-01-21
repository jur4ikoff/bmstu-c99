#ifndef LIST_H__
#define LIST_H__

#include "constants.h"
#include <stdio.h>
typedef struct _node_type_ node_t;


err_t push_list(node_t **head, int data);
void print_list(node_t *head);
void free_list(node_t *head);
void convert_arr_to_list(node_t **head, int *arr, size_t count);
void delete_by_task(node_t *head);
#endif