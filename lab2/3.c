#include <stdio.h>
#include <math.h>
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

    // Ввод списка
    printf("Введите элементы списка по одному: ");
    int array[ARRAY_LEN];
    for (int i = 0; i < array_len; i++)
    {
        int input_el;
        if (scanf("%d", &input_el) != 1)
        {
            printf("WRONG INPUT\n");
            return WRONG_INPUT;
        }
        array[i] = input_el;
    }
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
