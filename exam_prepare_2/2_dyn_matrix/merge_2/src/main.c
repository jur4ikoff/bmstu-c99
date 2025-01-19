#include "constants.h"
#include "matrix.h"
#include <stdio.h>

int main(void)
{
    int rc = ERR_OK;
    matrix_t matrix = {0};
    int n = 4, m = 2;
    if ((rc = create_matrix(&matrix, n, m)) != ERR_OK)
    {
        free_matrix(matrix);
        return rc;
    }
    random_fill(&matrix);
    print_matrix(matrix);
    free_matrix(matrix);
    return rc;
}
