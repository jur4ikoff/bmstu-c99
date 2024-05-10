#include "io.h"

// Ввод размерности матрицы 
int input_len(size_t *array_len)
{
    if (scanf("%zu", array_len) != 1)
    {
        printf("len must be integer number\n");
        return WRONG_INPUT;
    }
    // Проверка на выход за пределы допустимых размеров
    if (*array_len > 10)
    {
        printf("len must be less then ten\n");
        return WRONG_ARRAY_LEN;
    }

    if (*array_len < 1)
    {
        printf("len must be more one\n");
        return WRONG_ARRAY_LEN;
    }

    return SUCCESS_OUTPUT;
}

// Вывод матрицы 
int print_matx(int matx[N][M], size_t n, size_t m)
{
    printf("Вывод матрицы \n");
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
            printf("%d  ", matx[i][j]);
        printf("\n");
    }
    return SUCCESS_OUTPUT;
}

