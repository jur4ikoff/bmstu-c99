#include "matrix.h"
#include "constants.h"
#include <stdlib.h>
#include <time.h>

err_t create_matrix(matrix_t *matrix, int n, int m)
{
    int *data;
    if (n < 1 || m < 1)
    {
        return ERR_SIZE;
    }
    if (matrix == NULL)
        return ERR_ARGS;

    matrix->matrix = calloc((size_t)n * (size_t)m, sizeof(int *)); // Юзаю calloc(), чтобы можно было спокойно сделать free(matrix->matrix[i])
    if (matrix->matrix == NULL)
        return ERR_MEM_ALLOC;

    data = calloc((size_t)n, sizeof(int));
    if (data == NULL)
        return ERR_MEM_ALLOC;
    for (size_t i = 0; i < (size_t)n; i++)
    {
        matrix->matrix[i] = data + i * m;
        if (matrix->matrix[i] == NULL)
        {
            free_matrix(*matrix);
            return ERR_MEM_ALLOC;
        }
    }

    matrix->n = (size_t)n;
    matrix->m = (size_t)m;
    return ERR_OK;
}

void free_matrix(matrix_t matrix)
{
    // Освобождаем все строки, потом освобождаем массив указателей
    if (matrix.matrix)
    {
        for (size_t i = 0; i < matrix.n; i++)
        {
            free(matrix.matrix[i]);
        }
        free(matrix.matrix);
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
            printf("%d ", matrix.matrix[i][j]);
        }
        printf("\n");
    }
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
            matrix->matrix[i][j] = rand() % 256;
        }
    }
    return ERR_OK;
}
