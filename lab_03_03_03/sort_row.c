#include "sort_row.h"
#include "io.h"

// Смена местами двух массивов внутри матрицы по индексу
void swap_arrays(int matrix[N][M], size_t index1, size_t index2, size_t m)
{
    int temp[M];
    for (size_t i = 0; i < m; i++)
    {
        temp[i] = matrix[index1][i];
        matrix[index1][i] = matrix[index2][i];
        matrix[index2][i] = temp[i];
    }
}

// Нахождение минимального элемента в строке
int min(int arr[], size_t n)
{
    int minn = (int)(pow(2, 31) - 1);

    for (size_t i = 0; i < n; i++)
    {
        if (arr[i] < minn)
            minn = arr[i];
    }
    return minn;
}

// функция запуска, сортировка строк массива
void string_sort(int matx[N][M], size_t *n, size_t *m)
{
    // Сортировка пузырьком
    for (size_t i = 0; i < *n - 1; i++)
    {
        for (size_t j = 0; j < *n - i - 1; j++)
        {
            if (min(matx[j], *m) < min(matx[j + 1], *m))
                swap_arrays(matx, j, j + 1, *m);
        }
    }
}
