#ifndef MATRIX_H__
#define MATRIX_H__
#include <stdio.h>

typedef struct
{
    double **ptrs;
    double *data;
    size_t row_count;
    size_t column_count;
} matrix_t;

int allocate_matrix(matrix_t *matrix);
void free_matrix(matrix_t matrix);
int read_matrix(const char *filename, matrix_t *matrix);
void print_matrix(matrix_t matrix);
int add_matrix(const matrix_t matrix_1, const matrix_t matrix_2, matrix_t *output);
int write_matrix(const char *filename, const matrix_t matrix);
int mult_matrix(const matrix_t matrix_1, const matrix_t matrix_2, matrix_t *result);
int find_determinant(matrix_t matrix, double *det);
#endif
