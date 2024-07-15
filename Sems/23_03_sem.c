#include <stdio.h>
#include <stdlib.h>
#define ARR_LEN 10
#define WRONG_INPUT 1


// Ввод массива
int input_list(int arr[])
{
    int array_len;
    printf("Введите длину массива: ");
    if (scanf("%d", &array_len) != 1)
    {
        printf("WRONG INPUT\n");
        return WRONG_INPUT;
    }

    if (array_len > 10 || array_len < 1)
    {
        printf("len must be less ten\n");
        return WRONG_INPUT;
    }

    printf("Введите элементы списка по одному: ");
    for (int i = 0; i < array_len; i++)
    {
        int input_el;
        if (scanf("%d", &input_el) != 1)
        {
            printf("WRONG INPUT\n");
            return WRONG_INPUT;
        }
        arr[i] = input_el;
    }
    return array_len;
}
    

// Вывод массива
void print_array(int array[], int n)
{
    printf("array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }

    printf("\n");
}

int check_digits(int arr[], int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        int el = abs(arr[i]);
        if (el % 3 == 0 && el % 2 != 0)
            count++;
    }
    return count;
}

int calculate_sum(int arr[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        int el = (arr[i]);
        if (abs(el) % 3 == 0 && abs(el) % 2 != 0)
            sum+= el;
    }
    return sum;
}
// Главная функция
int main(void)
{
    int arr[ARR_LEN];
    int res = input_list(arr);
    if (res == -1)
        return WRONG_INPUT;
    int len_arr = res;
    res = check_digits(arr, len_arr);
    if (res == 0)
        {
            printf("Нет таких чисел");
            return WRONG_INPUT;
        }
    res = calculate_sum(arr, len_arr);
    print_array(arr, len_arr);
    printf("%d\n", res);
    return 0;
}
