#ifndef IO_H
#define IO_H
#include "const.h"
#include "math.h"
int input_matrix(uint16_t matrix[][MAX_M], size_t n, size_t m);
int input_size(size_t *n, int max);
void print_matrix(uint16_t matrix[][MAX_M], size_t n, size_t m);

void output(int arg);
#endif
