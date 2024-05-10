#include <stdio.h>
#include "io.h"
#include <stdlib.h>

#ifndef REFIL_H
#define REFIL_H
size_t create_new_array(int matx[N][M], int arr[], size_t n, size_t m);
void shift(int arr[], int n);
int sum_digits(int number);
void refill_matrix(int matx[N][M], int arr[], size_t n, size_t m);
#endif
