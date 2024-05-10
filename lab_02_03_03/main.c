#include <stdio.h>
#include <math.h>
#define SUCCESS_OUTPUT 0
#define WRONG_INPUT 1
#define WRONG_ARRAY_LEN 2
#define ONLY_NEGATIVE 3
#define ARRAY_LEN 20

// Вывод массива на экран
void print_array(int array[], int n)
{
    printf("new_array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }

    printf("\n");
}

// Вставка элементна в массив по индексу
void insert_array(int arr[], int len_array, int index, int el)
{
    for (int i = len_array; i > index; i--)
    {
        arr[i] = arr[i - 1];
    }

    arr[index] = el;
}

// Ввод длины массива
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
    return 0;
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

    return SUCCESS_OUTPUT;
}
// Получение палидрома
int reverse_int(int el)
{
    int new_el = 0;
    while (el)
    {
        int digit = el % 10;
        el /= 10;
        new_el = new_el * 10 + digit;
    }
    return new_el;
}

// Главная функция
int main(void)
{
    int array_len;
    // Ввод
    int res = input_array_len(&array_len);
    // Обработка ошибок
    if (res == WRONG_INPUT)
    {
        return WRONG_INPUT;
    }
    else if (res == WRONG_ARRAY_LEN)
    {
        return WRONG_ARRAY_LEN;
    }

    // Ввод списка
    int array[ARRAY_LEN];
    res = input_array(array, array_len);
    // Обработка ошибок при вводе списка
    if (res != 0)
        return WRONG_INPUT;
    // Иттерация по списку и проверка по критерию
    for (int i = 0; i < array_len; i++)
    {
        if (array[i] > 0)
        {
            int el = array[i];
            int rev = reverse_int(el);
            insert_array(array, array_len, i + 1, rev);
            array_len++;
            i++;
        }
    }

    // Вывод списка
    print_array(array, array_len);
}
