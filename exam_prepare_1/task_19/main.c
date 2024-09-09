/*
Матрица, максимальный размер которой равен 5x7, содержит беззнаковые целые числа длиной 2 байта. Переписать в массив числа, у которых установлен 3 и/или 4 бит в 1. Массив вывести на экран.
Элементы из матрицы помещаются в массив в порядке обхода матрицы по строкам.
При выводе элементы массива разделяются пробелом.
Приглашения к вводу НЕ нужны.
Если происходит ошибка ввода (например, ввод буквы вместо числа), выдать на экран «Input error».
Если указано числи из неверного диапазона (например, 12 в качестве одного из размеров), выдать на экран «Range error».
Если в результате работы программы получен пустой массив, выдать на экран «Empty array». В случае любой другой ошибки выдать на экран «Unknown error».
*/
#include "const.h"
#include "io.h"
#include "solve.h"

int main(void)
{
    int rc = ERR_OK;
    uint16_t matrix[MAX_N][MAX_M], array[MAX_SIZE];
    size_t n = 0, m = 0, count = 0;

    if ((rc = input_size(&n, MAX_N)) != ERR_OK)
    {
        output(rc);
        return rc;
    }

    if ((rc = input_size(&m, MAX_M)) != ERR_OK)
    {
        output(rc);
        return rc;
    }

    if ((rc = input_matrix(matrix, n, m)) != ERR_OK)
    {
        output(rc);
        return rc;
    }

    if ((rc = solve(array, matrix, n, m, &count)) != ERR_OK)
    {
        output(rc);
        return rc;
    }
    for (size_t i = 0; i < count; i++)
    {
        printf("%" PRIu16 " ", array[i]);
    }
    printf("\n");
    return rc;
}
