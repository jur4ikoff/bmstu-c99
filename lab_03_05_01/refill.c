#include "refill.h"
#include "io.h"

// Вычисление суммы цифр в числе
int sum_digits(int number)
{
    number = abs(number);
    int sum = 0;
    while (number > 0)
    {
        sum += (number % 10);
        number /= 10;
    }

    return sum;
}

// Создание массива, состоящего из элементов с суммой цифр больше 10
size_t create_new_array(int matx[N][M], int arr[], size_t n, size_t m)
{
    int index = 0;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            // Если сумма цифр большн 10, то записываю в массив
            int el = matx[i][j];
            if (sum_digits(el) > 10)
            {
                arr[index] = el;
                index++;
            }
        }
    }
    return index;
}

// Циклический сдвиг влево на 1 позицию  
void shift(int arr[], int n)
{
    // Сохранение первого элемента
    int temp = arr[0];
    for (int i = 1; i < n; i++)
    {
        arr[i - 1] = arr[i];
    }
    arr[n - 1] = temp;
}

// Запись нового массива в матрицу
void refill_matrix(int matx[N][M], int arr[], size_t n, size_t m)
{
    int el, index = 0;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            // Вставляем сдивнутые элементы на те же места
            el = matx[i][j];
            if (sum_digits(el) > 10)
            {
                matx[i][j] = arr[index];
                index++;
            }
        }
    }
}
