#include <stdio.h>
#include "io.h"

#ifndef SOLVE_H
#define SOLVE_H
int check_contains_digit(int digit, int number);
void swap(int arr[], int first, int second);
void delete_column(int matx[N][M], size_t *n, size_t *m, int index);
void solve(int matx[N][M], size_t *n, size_t *m, int digit);
#endif
