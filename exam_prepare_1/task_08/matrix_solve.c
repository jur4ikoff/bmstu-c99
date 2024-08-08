#include "constants.h"
#include "matrix_solve.h"

void find_max_even(int matrix[][MAX_SIZE], int n, int m, int *column, int *string)
{
    int max = -10e6;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (matrix[i][j] % 2 == 0 && matrix[i][j] > max)
            {
                max = matrix[i][j];
                *string = i;
                *column = j;
            }
        }
    }
}

void find_min_odd(int matrix[][MAX_SIZE], int n, int m, int *column, int *string)
{
    int min = 10e6;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (matrix[i][j] % 2 == 1 && matrix[i][j] < min)
            {
                min = matrix[i][j];
                *string = i;
                *column = j;
            }
        }
    }
}

void swap_strings(int matrix[][MAX_SIZE], int m, int index1, int index2)
{
    for (int i = 0; i < m; i++)
    {
        int temp = matrix[index1][i];
        matrix[index1][i] = matrix[index2][i];
        matrix[index2][i] = temp;
    }
}

void swap_columns(int matrix[][MAX_SIZE], int n, int index1, int index2)
{
    for (int i = 0; i < n; i++)
    {
        int temp = matrix[i][index1];
        matrix[i][index1] = matrix[i][index2];
        matrix[i][index2] = temp;
    }
}