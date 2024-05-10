#include "spiral_input.h"
#include "io.h"

void fill_matrix_anticlockwise(int matx[N][M], int n, int m)
{
    // Инициализация переменных
    int value = 1;
    int l = 0, r = m - 1, b = n - 1, u = 0;
    // Проверка выделяющегося случая
    if (n == 1)
        matx[0][0] = 1;

    // Пробегаемся в цикле, пока возможно
    while (l <= r && u <= b)
    {
        // Заполнение сверху вниз
        for (int i = u; i <= b; i++)
        {
            matx[i][l] = value;
            value++;
        }
        l++;

        // Заполнение слева направо
        for (int i = l; i <= r; i++)
        {
            matx[b][i] = value;
            value++;
        }
        b--;

        // Заполнение снизу вверх
        for (int i = b; i >= u; i--)
        {
            matx[i][r] = value;
            value++;
        }
        r--;

        // Заполнение справа налево
        for (int i = r; i >= l; i--)
        {
            matx[u][i] = value;
            value++;
        }
        u++;
    }
}
