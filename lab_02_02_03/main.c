#include <stdio.h>
#include <math.h>
#define WRONG_INPUT 1
#define WRONG_ARRAY_LEN 2
#define ONLY_NEGATIVE 3
#define ARRAY_LEN 10

// Вычисление длины числа
int get_digit_len(int n)
{
    int digit_len = 0;
    while (n)
    {
        digit_len++;
        n /= 10;
    }
    return digit_len;
}

// Проверка на число армстронга
int check_armstrong(int number)
{
    int digit_len = get_digit_len(number);
    int sum = 0, n;
    n = number;
    if (number < 0)
    {
        return 0;
    }
    while (n)
    {
        int el = (n % 10);
        sum += (int)pow(el, digit_len);
        n /= 10;
    }

    if (number == sum)
        return 1;
    else
        return 0;
}

int get_new_array(int array[], int new_array[], int array_len)
{
    // Создаем новый массив и добавляем в него элементы старого
    int index = 0;
    for (int i = 0; i < array_len; i++)
    {
        int el = array[i];
        int res = check_armstrong(el);
        if (res == 1)
        {
            new_array[index] = el;
            index++;
        }
    }
    if (index == 0)
    {
        return -1;
    }
    return index;
}

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

int main(void)
{
    int array_len;
    // Ввод
    printf("Введите длину массива: ");
    if (scanf("%d", &array_len) != 1)
    {
        printf("WRONG INPUT\n");
        return WRONG_INPUT;
    }
    // Обработка ошибок
    if (array_len > 10 || array_len < 1)
    {
        printf("len must be less ten\n");
        return WRONG_ARRAY_LEN;
    }

    // Ввод элементов списка
    printf("Введите элементы списка по одному: ");
    int array[ARRAY_LEN];
    int count = 0;
    for (int i = 0; i < array_len; i++)
    {
        int input_el;
        if (scanf("%d", &input_el) != 1)
        {
            printf("WRONG INPUT\n");
            return WRONG_INPUT;
        }
        // Проверка на положительное число
        if (input_el > 0)
            count++;
        array[i] = input_el;
    }
    if (count == 0)
    {
        printf("No positive numbers \n");
        return ONLY_NEGATIVE;
    }

    // Вывод
    int new_array[ARRAY_LEN];
    int res = get_new_array(array, new_array, array_len);
    if (res == -1)
    {
        printf("Zero Armstrong digits");
        return 1;
    }
    int len_new_array = res;
    print_array(new_array, len_new_array);
}
