#include "io.h"

int input_size(size_t *n, int max)
{
    if (scanf("%zu", n) != 1)
        return ERR_INPUT;

    if ((int)*n > max)
        return ERR_INPUT;

    return ERR_OK;
}

int input_matrix(uint16_t matrix[][MAX_M], size_t n, size_t m)
{
    int buffer;

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            if (scanf("%d", &buffer) != 1)
                return ERR_INPUT;

            if (buffer < 0 || buffer > pow(2, sizeof(uint16_t) * 8))
                return ERR_RANGE;

            matrix[i][j] = (uint16_t)buffer;
        }
    }

    return ERR_OK;
}

void print_matrix(uint16_t matrix[][MAX_M], size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            printf("%" PRIu16 " ", matrix[i][j]);
        }
    }
}

void output(int arg)
{
    if (arg == ERR_EMPTY)
        printf("Empty array\n");
    else if (arg == ERR_INPUT)
        printf("Input error\n");
    else if (arg == ERR_UNKNOWN)
        printf("Unknown error\n");
    else if (arg == ERR_RANGE)
        printf("ERR_RANGE\n");
}
