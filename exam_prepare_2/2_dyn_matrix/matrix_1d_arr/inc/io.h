#ifndef IO_H__
#define IO_H__
#define _GNU_SOURCE
#include "array_operations.h"
#include <stdio.h>

int count_structs_in_file(FILE *file, size_t *count);
void print_error_message(int arg);
void print_products(product_t products[], size_t count);
void free_products(product_t *products, const size_t count);
int read_structs_from_file(FILE *file, product_t *products, size_t *count);
void print_products_by_index(product_t *products, size_t *indexes, size_t count);

#endif
