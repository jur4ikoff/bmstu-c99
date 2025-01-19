#ifndef MATRIX_H__
#define MATRIX_H__
#include "constants.h"
#include <stdio.h>

typedef struct _matrix_t__
{
    size_t n;
    size_t m;
    int **matrix; // Массив указателей (Двумерный массив)
} matrix_t;

err_t create_matrix(matrix_t *matrix, int n, int m);
void free_matrix(matrix_t matrix);
err_t random_fill(matrix_t *matrix);
void print_matrix(matrix_t matrix);
#endif
