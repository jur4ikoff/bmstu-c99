#ifndef IO_H
#define IO_H

#include "constants.h"
int input_len(int *size);
void output(int arg);
int input_matrix(int matrix[][MAX_SIZE], int n, int m);
void print_matrix(int matrix[][MAX_SIZE], int n, int m);

#endif
