/*
Дана целочисленная квадратная матрица. Двумя диагоналями матрица разбита на четыре треугольника. Элементы диагоналей в треугольники не включаются.
Найти:
    • максимальный элемент в первом треугольнике;
    • минимальный элемент во втором треугольнике;
    • сумму четных элементов в третьем треугольнике;
    • произведение нечетных элементов в четвертом треугольнике;
    • количество отрицательных элементов на обеих диагоналях.

Если какой-то из искомых элементов отсутствует, вывести соответствующее сообщение и завершить программу с ненулевым кодом.
*/

#include "constants.h"
#include "io.h"
#include "solve.h"

int main(void)
{
    int rc = ERR_OK, matrix[MAX_SIZE][MAX_SIZE];
    size_t size;
    if ((rc = input_size(&size) != ERR_OK))
    {
        output(rc);
        return rc;
    }

    if (size < 2)
    {
        output(ERR_EMPTY);
        return ERR_EMPTY;
    }

    if ((rc = input_matrix(matrix, size) != ERR_OK))
    {
        output(rc);
        return rc;
    }

    int max_first = find_max_in_first(matrix, size);
    printf("%d\n", max_first);

    int min_two = find_min_in_two(matrix, size);
    printf("%d\n", min_two);

    int sum_three = sum_even_in_three(matrix, size);
    printf("%d\n", sum_three);

    int mltp_odd = mltp_odd_four(matrix, size);
    printf("%d\n", mltp_odd);

    int neg_count = count_inverse(matrix, size);
    printf("%d\n", neg_count);
    return rc;
}
