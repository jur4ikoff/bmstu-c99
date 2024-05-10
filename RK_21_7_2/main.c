#include <stdio.h>
#include <math.h>
#define SUCCESS 0
#define WRONG_INPUT 1
#define WRONG_ARRAY_LEN 2
#define ARRAY_LEN 12

// Вывод массива
void print_array(int array[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }

    printf("\n");
}

// Получить длинну массива
int input_array_len(int *array_len)
{
    printf("Введите длину массива: ");
    if (scanf("%d", array_len) != 1)
    {
        printf("WRONG INPUT\n");
        return WRONG_INPUT;
    }
    // Обработка ошибок
    if (*array_len > 10 || *array_len < 1)
    {
        printf("len must be less ten\n");
        return WRONG_ARRAY_LEN;
    }
    return SUCCESS;
}

// Ввод массива
int input_array(int arr[], int n)
{
    printf("Введите элементы массива по одному: \n");
    for (int i = 0; i < n; i++)
    {
        // Получаем элемент
        int el;
        if (scanf("%d", &el) != 1)
        {
            printf("WRONG INPUT");
            return WRONG_INPUT;
        }
        arr[i] = el;
    }

    return SUCCESS;
}

// Получение максимального элемента массива
int max(int arr[], int n)
{
    int max = -1 * (int)(pow(2, 32) - 1);

    for (int i = 0; i < n; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

// Получение минимального элемента массива
int min(int arr[], int n)
{
    int min = (int)(pow(2, 32) - 1);

    for (int i = 0; i < n; i++)
    {
        if (arr[i] < min)
            min = arr[i];
    }
    return min;
}

// Вставка первым эллементом
void insert(int arr[], int n, int el)
{
    for (int i = n - 1; i >= 0; i--)
    {
        arr[i + 1] = arr[i];
    }
    arr[0] = el;
}

int main(void)
{
    // Блок ввода
    int array[ARRAY_LEN], array_len, res;
    res = input_array_len(&array_len);
    if (res != 0)
        return res;
    res = input_array(array, array_len);
    if (res != 0)
        return res;

    // Вывод исходного массива
    printf("Исходный массив: ");
    print_array(array, array_len);

    // Решение задачи
    // получение суммы
    int min_el = min(array, array_len);
    int max_el = max(array, array_len);
    int sum = min_el + max_el;
    array_len++;
    // Вставка суммы
    if (sum % 2 == 0)
        insert(array, array_len, sum);
    else
        array[array_len - 1] = sum;

    // Блок вывода
    printf("Измененный массив: ");
    print_array(array, array_len);
    return SUCCESS;
}
