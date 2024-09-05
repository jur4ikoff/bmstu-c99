#include "matrix_lib.h"

// меняет местами элементы матрицы
void swap(int matrix[][MAX_SIZE], size_t i1, size_t j1, size_t i2, size_t j2)
{
    int temp = matrix[i1][j1];
    matrix[i1][j1] = matrix[i2][j2];
    matrix[i2][j2] = temp;
}

// Поворот матрицы вправо
/*void turn_right_90(int matrix[][MAX_SIZE], size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        for (size_t j = 0; j < count; j++)
        {
            swap(matrix, j, i, count - i - 1, j);
        }
    }
}*/

void transposition(int matrix[][MAX_SIZE], size_t size)
{

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = i; j < size; j++)
        {
            swap(matrix, i, j, j, i);
        }
    }
}
