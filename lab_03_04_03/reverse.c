#include "reverse.h"


// Функция меняет местами столбцы, между главными диагоналями  
void swap_columns(int matx[N][M], size_t index1, size_t index2, size_t n, size_t indent)
{
    int temp[N];
    for (size_t i = indent; i < n - indent; i++)
    {
        temp[i] = matx[i][index1];
        matx[i][index1] = matx[i][index2];
        matx[i][index2] = temp[i];
    }
}

// Функция запуска 
void run_swap(int matx[N][M], size_t n)
{
    int indent = 0;
    for (size_t i = 0; i < n; i++)
    {
        swap_columns(matx, i, n - i - 1, n, indent);
        indent++;
    }
}
