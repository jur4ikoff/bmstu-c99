#include <stdio.h>
#include <math.h>
#define WRONG_LEN_INPUT -1
#define SUCCESS_OUTPUT 0
#define WRONG_ARRAY_INPUT 1
#define WRONG_INPUT 1
#define ARRAY_LEN 10

// Ввод длины массива
int input_array_len(void)
{
    int array_len = 0;
    printf("Введите количество элементом массива: ");
    if (scanf("%d", &array_len) != 1)
    {
        printf("WRONG INPUT\n");
        return WRONG_LEN_INPUT;
    }

    if (array_len > 10 || array_len < 2)
    {
        printf("len must be betwen two and ten\n");
        return WRONG_LEN_INPUT;
    }

    return array_len;
}

// Ввод элементов массива
int input_array(int *start, int *finish)
{
    printf("Введите элементы массива по одному: \n");
    for (int *i = start; i < finish; i++)
    {
        if (scanf("%d", i) != 1)
        {
            printf("WRONG INPUT");
            return WRONG_ARRAY_INPUT;
        }
    }

    return SUCCESS_OUTPUT;
}

// Формирование нового массива
void get_new_arr(int *start1, int *finish1, int *start2)
{
    int j = 0;
    for (int *i = start1; i < finish1 - 1; i++)
    {
        // Получение элемента
        int el = *(i) * (*(i + 1));
        *(start2 + j) = el;
        j++;
    }
}

// Получение минимального значения массива
int min(int *start, int *finish)
{
    // Определение минимума, как максимально возможное целое число
    int min = 21478367;
    for (int *i = start; i < finish; i++)
    {
        if (*i < min)
            min = *i;
    }
    return min;
}

// Главная функция
int main(void)
{
    // Определение массивов
    int array[ARRAY_LEN], new_array[ARRAY_LEN];
    // Получение длины и обработка ошибки
    int array_len = input_array_len();
    if (array_len == -1)
    {
        printf("WRONG LEN INPUT");
        return WRONG_ARRAY_INPUT;
    }

    // Объявление указателей в двух массивах
    int *start = array;
    int *finish = array + array_len;
    int *start2 = new_array;
    int *finish2 = new_array + array_len - 1;

    // Ввод в первый массив
    if (input_array(start, finish) == WRONG_ARRAY_INPUT)
        return WRONG_ARRAY_INPUT;

    // Заполнение второго массива
    get_new_arr(start, finish, start2);
    // Получение минимального элемента
    int res = min(start2, finish2);
    printf("min: %d\n", res);
    return SUCCESS_OUTPUT;
}
