#include "solve.h"
#define BIT(n) (1 << (n))

int solve(uint16_t array[], uint16_t matrix[][MAX_M], size_t n, size_t m, size_t *count)
{
    *count = 0;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            if (matrix[i][j] & (BIT(3) | BIT(4)))
            {
                array[*count] = matrix[i][j];
                (*count)++;
            }
        }
    }

    if (*count == 0)
        return ERR_EMPTY;
    return ERR_OK;
}
