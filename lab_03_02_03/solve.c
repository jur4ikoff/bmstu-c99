#include <stdlib.h>
#include "solve.h"

// Проверка, содержится ли цифра в числе
int check_contains_digit(int digit, int number)
{
    int el;
    // обработка случая с отрицательным числом
    number = abs(number);
    // Если число одноразрядное
    if (digit == number)
        return 1;
    // выделение цифр из числа и сравнение их
    while (number > 0)
    {
        el = number % 10;
        if (el == digit)
            return 1;
        number /= 10;
    }

    return 0;
}

// обмен местами двух элементов массива
void swap(int arr[], int first, int second)
{
    int second_el = arr[second];
    arr[second] = arr[first];
    arr[first] = second_el;
}

// удаление столбца матрицы по индексу
// сдвигаем столбец для удаления в конец и изменяем длинну массива
void delete_column(int matx[N][M], size_t *n, size_t *m, int index)
{
    for (size_t i = 0; i < *n; i++)
    {
        size_t j = index;
        while (j < *m - 1)
        {
            swap(matx[i], j, j + 1);
            j++;
        }
    }
    (*m)--;
}

// функция с решением задачи
void solve(int matx[N][M], size_t *n, size_t *m, int digit)
{
    int el;
    // иттерация по матрицы
    for (size_t j = 0; j < *m; j++)
    {
        for (size_t i = 0; i < *n; i++)
        {
            el = matx[i][j];
            // Если содержит число, то удаляется столбец
            if (check_contains_digit(digit, el) == 1)
            {
                delete_column(matx, n, m, j);
                j--;
                break;
            }
        }
    }
}
