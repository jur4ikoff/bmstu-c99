/*
Дана целочисленная прямоугольная матрица.
Поменять местами строки, в которых находятся максимальный четный и минимальный нечетный элементы.
Если эти элемент находятся в одной строке, то поменять местами соответствующие столбцы.
Если один из искомых элементов отсутствует, вывести соответствующее сообщение и завершить программу с ненулевым кодом.
*/
#include "io.h"
#include "constants.h"
#include "matrix_solve.h"

int main(void)
{
    int n, m, rc = ERR_OK;
    int matrix[MAX_SIZE][MAX_SIZE];
    if ((rc = input_len(&n)) != ERR_OK)
    {
        output(rc);
        return rc;
    }

    if ((rc = input_len(&m)) != ERR_OK)
    {
        output(rc);
        return rc;
    }

    if ((rc = input_matrix(matrix, n, m)) != ERR_OK)
    {
        output(rc);
        return rc;
    }

    int even_column, even_string, odd_column, odd_string;
    find_max_even(matrix, n, m, &even_column, &even_string);
    find_min_odd(matrix, n, m, &odd_column, &odd_string);

    if (even_string != odd_string)
        swap_strings(matrix, m, even_string, odd_string);
    else
        swap_columns(matrix, n, even_column, odd_column);

    print_matrix(matrix, n, m);
    return rc;
}
