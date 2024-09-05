/* Небольшая учебная библиотека по матрицам, для подготовки к экзамену*/

#include "constants.h"
#include "io.h"
#include "matrix_lib.h"

int main(void)
{
    int rc = ERR_OK;
    size_t size;
    int matrix[MAX_SIZE][MAX_SIZE];
    if ((rc = input_size(&size)) != ERR_OK)
    {
        output(rc);
        return rc;
    }

    fill_matrix_consistently(matrix, size);
    print_matrix(matrix, size);
    transposition(matrix, size);
    print_matrix(matrix, size);
    return rc;
}
