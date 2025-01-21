#ifndef QUEUE_H__
#define QUEUE_H__

typedef struct _node_type_ node_t;

int add_queue(node_t **head, char data);
char pop_queue(node_t **head, char symb_to_del);
void free_list(node_t *head);
void print_queue(node_t *head);

void convert_int_to_list(node_t **head, int number);
#endif