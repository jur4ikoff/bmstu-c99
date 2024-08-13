#include "constants.h"
#include "io.h"
#include "stdlib.h"

int input_size(size_t *size)
{
    if (scanf("%zu", size) != 1)
        return ERR_INPUT;

    if (*size < 1 || *size > MAX_SIZE)
        return ERR_INPUT;
    return ERR_OK;
}

void output(int arg)
{
    switch (arg)
    {
    case ERR_INPUT:
        printf("ERR INPUT\n");
        break;
    }
}

void print_matrix(int matrix[MAX_SIZE][MAX_SIZE], size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void fill_matrix(int matrix[MAX_SIZE][MAX_SIZE], size_t size)
{
    // This пиздец was stollen from habr
    for (int i = 0; i < (int)size; i++)
    {
        for (int j = 0; j < (int)size; j++)
        {
            int ik = i + 1;
            int jk = j + 1;
            int d = ik + jk - 1;
            int ma = (d * d + d) / 2;
            int mb = (size * size + size) / 2 + ((3 * size - d - 1) * (d - size)) / 2;
            int ca = abs(d / ((int)size + 1) - 1);
            int cb = d / (size + 1);
            int co = d % 2;
            int ce = (d + 1) % 2;
            matrix[i][j] = ca * ((ma - jk + 1) * ce + (ma - ik + 1) * co) + cb * ((mb - (size - ik)) * ce + (mb - (size - jk)) * co);
        }
    }
}
