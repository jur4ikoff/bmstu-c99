#include "io.h"
#include "sort_row.h"


// Главная функция
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

    // Сортировка строк
    string_sort(matx, &n, &m);
    
    // Блок вывода
    print_matx(matx, n, m);
    return SUCCESS_OUTPUT;
}
