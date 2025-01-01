#include "my_strlib.h"
#include <stdlib.h>
#define ABS(x) ((x) > 0 ? x : -(x))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

/**
 * @brief Функция склеевает две строки
 * @param dst Указатель на итоговую строку
 * @param src Указатель на исходную строку
 * @param size Размер исходной строки
 * @param max Максимальное ограничен
 */
void my_strcat(char *dst, const char *src, size_t *count, const size_t max)
{
    if (!src)
        return;
    while (*src)
    {
        // Проверка на то что память не выходит за пределы выделенного массива
        if ((int)*count < ((int)max - 1))
            dst[*count] = *src;

        (*count)++;
        src++;
    }
    // Не забываем про терминальный нуль
    if (dst)
        dst[*count] = 0;
}

/**
 * @brief Функция возвращает длинну целого числа
 * @param num Число
 * @return Количество разрядов числа num
 */
size_t integer_len(long long num)
{
    size_t count = 0;
    if (num == 0)
        return 1;
    num = ABS(num);
    while (num > 0)
    {
        num /= BASE;
        count++;
    }
    return count;
}

/**
 * @brief Функция конвертирует число в строку
 * @param num Число, для конвертации
 * @param width Ширина поля, для выравнивания по правому краю
 */
char *integer_to_string(long long num, size_t width, size_t is_sign, size_t align)
{
    // Получаем длину числа (без знака)
    int len = (int)integer_len(num);
    int num_len = len;
    // Знак числа 0 - Положительное, 1 - Отрицательное
    int is_negative = 0;
    if (num < 0)
    {
        is_negative = 1;
        // Если число отрицательное, то закладываем еще один символ на знак
        len++;
    }
    else if (is_sign)
    {
        len++;
    }
    // Задаем ширину поля, если она больше длины числа
    len = MAX(len, (int)width);

    // Выделение памяти + проверка
    char *buffer = malloc(sizeof(char) * (len + 1));
    if (!buffer)
        return NULL;

    num = ABS(num); // Не забыть, а то атата
    int i = 0;

    if (align == 0)
    {
        // Выравнивание по правому краю
        if (num == 0)
        {
            buffer[len - i - 1] = (char)((num % BASE) + '0');
            i++;
        }
        // Если не ноль, соответственно
        while (num > 0)
        {
            // Чтобы не реверсить строку, заполняю память с помощью формулы обратной иттерации
            buffer[len - i - 1] = (char)((num % BASE) + '0');
            num /= BASE;
            i++;
        }

        //  Если нужен знак
        if (is_negative)
        {
            buffer[len - i - 1] = '-';
            i++;
        }
        else if (is_sign)
        {
            buffer[len - i - 1] = '+';
            i++;
        }

        // Заполняем оставшееся пространство пробелами с левого края до ширины поля
        while (len - i - 1 >= 0)
        {
            buffer[len - i - 1] = ' ';
            i++;
        }
    }
    else if (align == 1)
    {
        // Выравнивание по левому краю
        if (is_negative)
        {
            buffer[i] = '-';
            i++;
        }
        else if (is_sign)
        {
            buffer[i] = '+';
            i++;
        }

        if (num == 0)
        {
            buffer[i] = (char)((num % BASE) + '0');
            i++;
        }

        // Если не ноль, соответственно
        int j = 0;
        while (num > 0)
        {
            // Чтобы не реверсить строку, заполняю память с помощью формулы обратной иттерации
            buffer[i + num_len - j - 1] = (char)((num % BASE) + '0');
            num /= BASE;
            j++;
        }
        i += j;

        // Заполняем оставшееся пространство пробелами с левого края до ширины поля
        while (i < len)
        {
            buffer[i] = ' ';
            i++;
        }
    }

    // В конец терминальный нуль и возврат
    buffer[len] = 0;
    return buffer;
}

int my_strlen(char *string)
{
    int count = 0;
    if (!string)
        return count;

    while (*string)
    {
        string++;
        count++;
    }
    return count;
}

/**
 * @brief Функция для выравнивания строки пробелами.
 * @param src исходная строка
 * @param width Ширина, в которой должна располагатся строка
 * @param align Рыжим выравнивания 0 - Право, 1 - Лево
 * @return Выделенная память под строку, в которая записана строка из src
 */
char *align_string(char *src, size_t width, int align)
{
    size_t len = (size_t)my_strlen(src);
    width = (size_t)MAX(width, len);

    char *string = NULL;
    string = malloc((width + 1) * sizeof(char));
    if (!string)
        return NULL;

    size_t index = 0;
    if (align == 0)
    {
        while (index + len < width)
        {
            string[index++] = ' ';
        }

        size_t i = 0;
        while (index < width)
        {
            string[index++] = src[i++];
        }
    }
    else if (align == 1)
    {
        while (*src)
        {
            string[index++] = *src;
            src++;
        }
        while (index < width)
        {
            string[index++] = ' ';
        }
    }
    string[index] = 0;
    return string;
}
