// Заполнить матрицу змейкой

#include "constants.h"
#include "io.h"

int main(void)
{
    int rc = ERR_OK, matrix[MAX_SIZE][MAX_SIZE];
    size_t size;
    if ((rc = input_size(&size)) != ERR_OK)
    {
        output(rc);
        return rc;
    }

    fill_matrix(matrix, size);
    print_matrix(matrix, size);
    return rc;
}
