#ifndef LINKED_LIST__H
#define LINKED_LIST__H
#include <stdio.h>

typedef void (*list_apply_func)(void *);
typedef struct node_t_ node_t;

node_t *create_node(void *data);
node_t *create_list(void);
void free_list(node_t *head);
void free_full(node_t *head);
void apply_list(node_t *head, list_apply_func apply_func);
node_t *find(node_t *head, const void *data, int (*comparator)(const void *, const void *));
node_t *sort(node_t *head, int (*comparator)(const void *, const void *));
int add_to_list(node_t **head, void *data);
void *pop_front(node_t **head);
int copy(node_t *head, node_t **new_head);
void *get_data(node_t *node);
#endif
