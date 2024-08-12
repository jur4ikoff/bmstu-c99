#include "solve.h"

int find_max_in_first(int matrix[][MAX_SIZE], size_t size)
{
    int shift = 1;
    int max = -10e6;
    for (size_t i = 0; i < size / 2; i++)
    {
        for (size_t j = shift; j < size - shift; j++)
        {
            if (matrix[i][j] > max)
                max = matrix[i][j];
        }
        shift++;
    }

    return max;
}

int find_min_in_two(int matrix[][MAX_SIZE], size_t size)
{
    size_t shift = 1;
    int min = 10e6;

    for (size_t j = size - 1; j > (size / 2); j--)
    {
        for (size_t i = shift; i < (size - shift); i++)
        {
            if (matrix[i][j] < min)
                min = matrix[i][j];
        }
        shift++;
    }

    return min;
}

int sum_even_in_three(int matrix[][MAX_SIZE], size_t size)
{
    int sum = 0;
    size_t shift = 1;
    for (size_t i = size - 1; i > size / 2; i--)
    {
        for (size_t j = shift; j < size - shift; j++)
        {
            if (matrix[i][j] % 2 == 0)
                sum += matrix[i][j];
        }
        shift++;
    }

    return sum;
}

int mltp_odd_four(int matrix[][MAX_SIZE], size_t size)
{
    size_t shift = 1;
    int mult = 1;

    matrix[0][0] = 1;
    for (size_t j = 0; j < (size / 2); j++)
    {
        for (size_t i = shift; i < (size - shift); i++)
        {
            if (matrix[i][j] % 2 == 1)
                mult *= matrix[i][j];
        }
        shift++;
    }
    return mult;
}

int count_inverse(int matrix[][MAX_SIZE], size_t size)
{
    int count = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (matrix[i][i] < 0)
            count += 1;

        if (matrix[i][size - i - 1] < 0)
            count += 1;
    }

    if (size % 2 == 1)
    {
        if (matrix[size / 2][size / 2] < 0)
            count -= 1;
    }

    return count;
}