#include <stdio.h>
#include <math.h>
#define WRONG_INPUT 1
#define SUCCESS 0

// Попов Ю.А. ИУ7-22Б 7 Вариант

// Ввод числа
int input_number(int *array_len)
{
    printf("Введите число: ");
    // Ввод
    if (scanf("%d", array_len) != 1)
    {
        printf("WRONG INPUT\n");
        return WRONG_INPUT;
    }
    // Обработка ошибок
    if (*array_len <= 0)
    {
        printf("Число должно быть натуральным\n");
        return WRONG_INPUT;
    }
    return SUCCESS;
}

// Поиск в числе четных элементов и  замена их на еденицу
int change_even_digit(int number)
{
    // инициализация переменных
    int new_number = 0, i = 0, size = 1, digit;
    while (number > 0)
    {
        // Вычисляем разрядность
        size = (int)pow(10, i++);
        // Получаем последнюю цифру
        digit = (number % 10);
        // Проверка на четность
        if (digit % 2 == 0)
            digit = 1;

        // Добавляем в новую переменную
        new_number += digit * size;
        number /= 10;
    }
    return new_number;
}

int main(void)
{
    // Инициализация переменных
    int number, res;
    // Блок ввода
    res = input_number(&number);
    if (res != SUCCESS)
        return res;
    // Решение задачи
    res = change_even_digit(number);

    // Блок вывода
    printf("Новое число: %d \n", res);
    return SUCCESS;
}
