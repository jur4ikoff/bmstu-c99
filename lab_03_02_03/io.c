#include "io.h"

// Ввод длины массива
int input_len(size_t *array_len)
{
    if (scanf("%zu", array_len) != 1)
    {
        printf("len must be integer number\n");
        return WRONG_INPUT;
    }

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

// Ввод цифры
int input_digit(int *digit)
{
    if (scanf("%d", digit) != 1)
    {
        printf("Digit must be integer");
        return WRONG_INPUT;
    }

    // Проверка, является ли число цифрой
    if (*digit < 0)
    {
        printf("Not digit. Digit must be positive\n");
        return WRONG_DIGIT_INPUT;
    }
    else if (*digit > 9)
    {
        printf("Not digit. Digit must be less ten\n");
        return WRONG_DIGIT_INPUT;
    }

    return SUCCESS_OUTPUT;
}

// Ввод матрицы
int input_matx(int matx[N][M], size_t n, size_t m)
{
    int el;
    printf("Введите числа матрицы:\n");
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            if (scanf("%d", &el) != 1)
            {
                printf("Wrong Input\n");
                return WRONG_INPUT;
            }
            matx[i][j] = el;
        }
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
