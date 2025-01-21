#ifndef STACK_H__
#define STACK_H__

#include <stdio.h>
typedef struct _node_type_ node_t;

int push_stack(node_t **top, char data);
void print_stack(node_t *stack);
void free_stack(node_t *top);
void pop_stack(node_t **);

void convert_to_stack(node_t **top, char *string);
size_t stack_len(node_t *top);
void convert_to_string_reverse(node_t *top, char *string, size_t len);
#endif