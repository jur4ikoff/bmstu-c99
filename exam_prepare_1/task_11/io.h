#ifndef IO_H
#define IO_H
#include "constants.h"

int input_string(char *string);
void output(int arg);
int input_size(size_t *size);
int input_to_struct(Point points[], size_t count);
void print_struct(Point points[], size_t count);
void find_max_square(Point points[], size_t count, size_t *index1, size_t *index2, size_t *index3);
#endif
