#ifndef NUMBER_H__
#define NUMBER_H__
#include "list.h"
#include <stdio.h>

typedef struct number_t_
{
    int prime_number;
    int exponentiation;
} number_t;

typedef int (*comparator_t)(const void *a, const void *b);
int compare_by_prime(const void *l, const void *r);
void print_number(void *data);
number_t *create_data(int prime, int exp);
int convert_string_to_int(char *string, long long *number);
int convert_to_list(node_t **head, long long number);
node_t *mult_number(const node_t *a, const node_t *b, comparator_t comparator);
node_t *div_list(long long a, long long b);
node_t *sqrt_list(node_t *head);
#endif
