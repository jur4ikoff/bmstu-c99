#include <stdio.h>
#include <math.h>
#define WRONG_INPUT 1
#define ARRAY_LEN 11

// Вывод массива
void print_array(int array[], int n)
{
    printf("new_array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }

    printf("\n");
}

// Ввод массива по конццевому признаку
int input_array(int arr[])
{
    int i = 0;
    printf("Введите элементы по концевому признаку: \n");
    while (1)
    {
        int el;
        if (scanf("%d", &el) == 1)
        {
            arr[i] = el;
            i++;
        }
        else
        {
            return i;
        }

        if (i > 10)
            return 100;
    }
}

// Функция меняет местами элементы массива
void swap(int arr[], int first, int second)
{
    int second_el = arr[second];
    arr[second] = arr[first];
    arr[first] = second_el;
}

// Реализация сортировки выбором
void selection_sort(int arr[], int len_array)
{
    for (int i = 0; i < (len_array - 1); i++)
    {
        int min_index = i;
        for (int j = i + 1; j < len_array; j++)
        {
            if (arr[j] < arr[min_index])
            {
                min_index = j;
            }
        }
        if (min_index != i)
        {
            swap(arr, i, min_index);
        }
    }
}

int main(void)
{
    // Ввод
    int array[ARRAY_LEN], array_len = 0;
    int res = input_array(array);
    // Обработка ошибок и получение длины списка
    if (res == 0)
    {
        printf("Zero input \n");
        return WRONG_INPUT;
    }
    else if (res <= 10)
    {
        array_len = res;
    }
    else if (res == 100)
    {
        array_len = 10;
    }
    // Сортировка и вывод
    selection_sort(array, array_len);
    print_array(array, array_len);
    // Возврат нужного exitcode
    if (res == 100)
        return 100;
    return 0;
}
