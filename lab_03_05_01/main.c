#include "io.h"
#include "refill.h"

int main(void)
{
    // Блок ввода
    size_t n, m;
    int matx[N][M];
    // Ввод размерности матрицы
    printf("Введите высоту матрицы: ");
    int res = input_len(&n);
    if (res != 0)
        return res;

    printf("Введите ширину матрицы: ");
    res = input_len(&m);
    if (res != 0)
        return res;

    // Ввод матрицы
    res = input_matx(matx, n, m);
    if (res != 0)
        return res;

    // Создание массива, состоящего из элементов с суммой цифр больше 10
    int arr[N * M];
    size_t len = create_new_array(matx, arr, n, m);
    // Проверка на наличие таких чисел 
    if (len <= 0)
    {
        printf("No elements for delete \n");
        return EMPTY_OUTPUT;
    }

    // сдиг 3 раза
    for (int i = 0; i < 3; i++)
    {
        shift(arr, len);
    }

    // запись сдвинутых чисел в матрицу
    refill_matrix(matx, arr, n, m);

    // Вывод результа
    print_matx(matx, n, m);
    return SUCCESS_OUTPUT;
}
