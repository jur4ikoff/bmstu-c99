#include "io.h"

// Функция принимает размер матрицы
int input_size(size_t *size)
{
    if (scanf("%zu", size) != 1)
        return ERR_INVALID_SIZE;

    if (*size <= 1 || *size > MAX_SIZE)
        return ERR_INVALID_SIZE;

    return ERR_OK;
}

// Функция выводит матрицу построчно с помощью вложенного цикла
void print_matrix(int matrix[][MAX_SIZE], size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        for (size_t j = 0; j < count; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Функция заполняет матрицу построчно
int fill_matrix_consistently(int matrix[][MAX_SIZE], size_t count)
{
    int cur = 1;
    if (count < 1)
        return ERR_EMPYTY_INPUT;

    for (size_t i = 0; i < count; i++)
    {
        for (size_t j = 0; j < count; j++)
        {
            matrix[i][j] = cur;
            cur++;
        }
    }

    return ERR_OK;
}

void output(int arg)
{
    switch (arg)
    {
    case ERR_INVALID_SIZE:
        printf("Invalid size\n");
        break;
    case ERR_EMPYTY_INPUT:
        printf("Empty input\n");
        break;
    case ERR_OUTPUT:
        printf("Error in output\n");
        break;
    case ERR_INPUT:
        printf("Input Error\n");
        break;
        /*case ERR_INVALID_SIZE:
            printf("Invalid size\n");
            break;*/
    }
}
