#include "io.h"

// Проверка является ли последовательность возрастающей
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

// Проверка является ли последовательность убывающей
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

// функция с решением задачи
void solve(int arr[], int matx[N][M], size_t n, size_t m)
{
    int res1, res2;
    for (size_t i = 0; i < n; i++)
    {
        // получаем результат для строки
        res1 = check_increasing_sequence(matx[i], m);
        res2 = check_decreasing_sequence(matx[i], m);

        // проверка по критерию
        if (res1 == 1 || res2 == 1)
            arr[i] = 1;
        else
            arr[i] = 0;
    }
}

// Главная функция
int main(void)
{
    // инициализация переменных
    size_t n, m;
    int matx[N][M];
    // ввод размерность матрицы
    printf("Введите высоту матрицы: ");
    int res = input_len(&n);
    if (res != 0)
        return res;

    printf("Введите ширину матрицы: ");
    res = input_len(&m);
    if (res != 0)
        return res;

    // ввод матрицы
    res = input_matx(matx, n, m);
    if (res != 0)
        return res;

    // print_matx(matx, n, m);

    // решение задачи
    int answer[N];
    solve(answer, matx, n, m);

    // Вывод ответа
    print_array(answer, n);
    return SUCCESS_OUTPUT;
}
