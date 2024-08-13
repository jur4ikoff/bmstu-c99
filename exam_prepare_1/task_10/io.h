#ifndef IO_H
#define IO_H
#include "constants.h"

void output(int arg);
int input_size(size_t *size);
void print_matrix(int matrix[MAX_SIZE][MAX_SIZE], size_t size);
void fill_matrix(int matrix[MAX_SIZE][MAX_SIZE], size_t size);
#endif
