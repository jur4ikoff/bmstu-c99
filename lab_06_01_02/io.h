#ifndef IO_H
#define IO_H
#include "constants.h"

void print_error_message(int arg);
int input_name(char *name, FILE *file);
void print_products(product_struct products[], size_t count);
int read_structs_from_file(FILE *file, product_struct products[], size_t *count);

#endif
