#include "io.h"

int input_size(size_t *size)
{
    if (scanf("%zu", size) != 1)
        return ERR_INPUT;

    if (*size == 0 || *size > MAX_SIZE)
        return ERR_INPUT;

    return ERR_OK;
}

int input_matrix(int matrix[MAX_SIZE][MAX_SIZE], size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            if (scanf("%d", &matrix[i][j]) != 1)
                return ERR_INPUT;
        }
    }
    return ERR_OK;
}

void print_matrix(int matrix[MAX_SIZE][MAX_SIZE], size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            printf("%d  ", matrix[i][j]);
        }
        printf("\n");
    }
}

void output(int arg)
{
    switch (arg)
    {
    case ERR_EMPTY:
        printf("ERR_EMPTY\n");
        break;
    case ERR_INPUT:
        printf("ERR_INPUT\n");
        break;
    }
}
