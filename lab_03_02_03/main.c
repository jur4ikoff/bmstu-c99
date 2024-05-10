#include "io.h"
#include "solve.h"

// Главная функция
int main(void)
{
    // Блок ввода
    size_t n, m;
    int matx[N][M];
    // Ввод длины измерений матрицы
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

    // Ввод цифры 
    printf("Введите цифру: ");
    int digit;
    res = input_digit(&digit);
    if (res != 0)
        return res;

    // print_matx(matx, n, m);
    // решение задачи
    solve(matx, &n, &m, digit);
    // Проверка на пустой вывод
    if (m == 0)
    {
        printf("Empty Output\n");
        return EMPTY_OUTPUT;
    }

    // Вывод ответа
    print_matx(matx, n, m);
    return SUCCESS_OUTPUT;
}
