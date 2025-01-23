#ifndef LIST_H__
#define LIST_H__

typedef struct _node_type_ node_t;

int append(node_t **head, int data);
void print_list(node_t *head);
void free_list(node_t *head);
node_t *create_node(int data);

#endif
