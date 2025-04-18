#include "matrix.h"
#include "constants.h"
#include <stdlib.h>
#include <time.h>

err_t create_matrix(matrix_t *matrix, int n, int m)
{
    if (n < 1 || m < 1)
    {
        return ERR_SIZE;
    }
    if (matrix == NULL)
        return ERR_ARGS;

    matrix->matrix = malloc(sizeof(int) * n * m);
    if (matrix->matrix == NULL)
        return ERR_MEM_ALLOC;

    matrix->n = (size_t)n;
    matrix->m = (size_t)m;
    return ERR_OK;
}

void free_matrix(matrix_t *matrix)
{
    if (matrix->matrix)
    {
        free(matrix->matrix);
    }
}

void print_matrix(matrix_t matrix)
{
    if (matrix.n < 1 || matrix.m < 1)
        return;

    for (size_t i = 0; i < matrix.n; i++)
    {
        for (size_t j = 0; j < matrix.m; j++)
        {
            printf("%d ", matrix.matrix[i * matrix.n + j]);
        }
    }

    printf("\n");
}

err_t random_fill(matrix_t *matrix)
{
    srand(time(NULL));
    if (matrix->n < 1 || matrix->m < 1)
        return ERR_ARGS;

    for (size_t i = 0; i < matrix->n; i++)
    {
        for (size_t j = 0; j < matrix->m; j++)
        {
            matrix->matrix[i * matrix->n + j] = rand() % 256;
        }
    }
    return ERR_OK;
}
