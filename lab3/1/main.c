#include "io.h"

int check_increasing_sequence(int arr[], size_t n)
{
    if (n <= 1)
        return 0;
    int el = arr[0];
    size_t i = 1;
    while (i < n)
    {
        if (arr[i] < el)
            return 0;
        el = arr[i];
        i++;
    }

    return 1;
}

int check_decreasing_sequence(int arr[], size_t n)
{
    if (n <= 1)
        return 0;
    int el = arr[0];
    size_t i = 1;
    while (i < n)
    {
        if (arr[i] > el)
            return 0;
        el = arr[i];
        i++;
    }

    return 1;
}

void solve(int arr[], int matx[N][M], size_t n, size_t m)
{
    int res1, res2;
    for (size_t i = 0; i < n; i++)
    {
        res1 = check_increasing_sequence(matx[i], m);
        res2 = check_decreasing_sequence(matx[i], m);

        if (res1 == 1 || res2 == 1)
            arr[i] = 1;
        else
            arr[i] = 0;
    }
}

// Главная функция
int main(void)
{
    size_t n, m;
    int matx[N][M];
    printf("Введите высоту матрицы: ");
    int res = input_len(&n);
    if (res != 0)
        return res;

    printf("Введите ширину матрицы: ");
    res = input_len(&m);
    if (res != 0)
        return res;

    res = input_matx(matx, n, m);
    if (res != 0)
        return res;

    // print_matx(matx, n, m);

    int answer[N];
    solve(answer, matx, n, m);
    print_array(answer, n);
    return SUCCESS_OUTPUT;
}
