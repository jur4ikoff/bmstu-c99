#include "io.h"
#include "reverse.h"
#define DIFF_LEN 4

// Главная функция
int main(void)
{
    // Блок ввода
    size_t n, m;
    int matx[N][M];

    // Ввод размерности матрицы
    printf("Введите длину матрицы: ");
    int res = input_len(&n);
    if (res != 0)
        return res;

    printf("Введите ширину матрицы: ");
    res = input_len(&m);
    if (res != 0)
        return res;

    // Проверка на то что матрица квадратная
    if (n != m)
    {
        printf("matrix must be square\n");
        return DIFF_LEN;
    }

    // Ввод матрицы
    res = input_matx(matx, n, n);
    if (res != 0)
        return res;

    // print_matx(matx, n);
    // Решение
    run_swap(matx, n);

    // Вывод результата
    print_matx(matx, n, n);
    return SUCCESS_OUTPUT;
}
