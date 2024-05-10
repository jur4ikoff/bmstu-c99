#include "io.h"
#include "spiral_input.h"
#define MATRIX_NOT_SQUARE 3

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
    
    // Проверка на то что матрица квадратная
    if (n != m)
    {
        printf("Matrix must be square\n");
        return MATRIX_NOT_SQUARE;
    }

    // заполнение матрицы против часовой стрелки по спирали
    fill_matrix_anticlockwise(matx, n, m);

    // Вывод ответа
    print_matx(matx, n, m);
    return SUCCESS_OUTPUT;
}
