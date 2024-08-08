#include "io.h"

int input_len(int *size)
{
    if (!scanf("%d", size))
        return ERR_INPUT;

    if (*size <= 0 || *size > MAX_SIZE)
        return ERR_INPUT;

    return ERR_OK;
}

int input_matrix(int matrix[][MAX_SIZE], int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (!scanf("%d", &matrix[i][j]))
                return ERR_INPUT;
        }
    }
    return ERR_OK;
}

void print_matrix(int matrix[][MAX_SIZE], int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void output(int arg)
{
    switch (arg)
    {
    case ERR_INPUT:
        printf("ERR_INPUT\n");
        break;
    }
}
