#include "my_realization.h"
#include "constants.h"
#include "my_strlib.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

// Енумка для операций / Сделал для удобства парсинга спецификаторов
typedef enum
{
    SPEC_D,
    SPEC_HD,
    SPEC_S,
    SPEC_OTHER
} specifier_t;

// Структура для обработки спецификатора
typedef struct
{
    specifier_t specifier; // Спецификатор
    int width;             // Ширина поля для выравнивцания
    int sign;              // Знак спецификатора 0 не нужен ; 1 нужен
    int align;             // 0 – right, 1 – left
} parse_specifier_t;

/**
 * @brief Функция для парсинга спецификаторов
 * @param format Указатель на строку форматирования (Обратить внимание: без знака %)
 * @param data Указатель на структуру для получения данных о спецификаторе
 * @return Код возврата
 */
static int specificator_parser(const char **format, parse_specifier_t *data)
{
    int is_spec = 0; // Найден ли хоть один спецификатор
    data->width = 0; // Инициализация на всякий случай

    while (**format == '-' || **format == '+')
    {
        if (**format == '-')
        {
            data->align = 1;
        }
        else if (**format == '+')
        {
            data->sign = 1;
        }
        (*format)++;
    }

    if (**format >= '0' && **format <= '9')
    {
        // Парсим ширину, если она есть
        size_t count = 0; // Ограничил максимальную ширину 3 разрядами
        int width = 0;
        while (**format >= '0' && **format <= '9')
        {
            if (count < MAX_WIDTH_LEN)
            {
                width = width * 10 + (**format - '0');
                (*format)++;
            }
            else
                return ERR_WIDTH;
        }
        // Записываем в структуру
        data->width = width;
    }
    if (**format == 's')
    {
        // Проверка на спецификатор %s
        is_spec = 1;
        data->specifier = SPEC_S;
        (*format)++;
    }
    // Проверка на модификатор %h
    else if (**format == 'h')
    {
        (*format)++;
        // Если модификатор есть, тогда проверяем, что за ним стоит d
        if (**format == 'd')
        {
            data->specifier = SPEC_HD;
            is_spec = 1;
            (*format)++;
        }
        else if (**format == 's')
        {
            data->specifier = SPEC_S;
            is_spec = 1;
            (*format)++;
        }
        else
        {
            // Случай, если после h нет ничего
            return ERR_SPECIFICATOR;
        }
    }
    else if (**format == 'd')
    {
        // Проверка на спецификатор %d
        data->specifier = SPEC_D;
        is_spec = 1;
        (*format)++;
    }
    else if (**format == '%')
    {
        // Если спецификатор равен %%
        data->specifier = SPEC_OTHER;
        return ERR_OK;
    }

    // Если спецификатор найден, возвращаем ERR_OK
    if (is_spec)
        return ERR_OK;

    return ERR_SPECIFICATOR;
}

/**
 * @brief Функция аналог библиотечной snprintf
 * @param buffer Строка, в которую по формату записаны аргументы
 * @param count Ограничение по размеру
 * @param format Строка форматирования
 * @param ... Аргументы
 * @return Код возврата
 */
int my_snprintf(char *buffer, size_t count, const char *format, ...)
{
    if (!buffer && count)
        return ERR_MEMORY_ALLOCATION;

    int rc = ERR_OK;
    char *string = NULL;
    size_t read = 0;
    va_list args;
    va_start(args, format);

    while (*format)
    {
        if (*format == '%')
        {
            // Сдвигаем спецификатор, чтобы дойти до значащей части
            format++;
            parse_specifier_t data = { 0 };
            if ((rc = specificator_parser(&format, &data)) != ERR_OK)
            {
                buffer[MIN(read, count - 1)] = 0;
                return rc;
            }

            if (data.specifier == SPEC_S)
            {
                char *string = align_string(va_arg(args, char *), data.width, data.align);
                // printf("%d\n", len);
                my_strcat(buffer, string, &read, count);
                free(string);
            }
            else if (data.specifier == SPEC_D)
            {
                int num = va_arg(args, int);
                string = integer_to_string(num, (size_t)data.width, data.sign, data.align);
                my_strcat(buffer, string, &read, count);
                free(string);
            }
            else if (data.specifier == SPEC_HD)
            {
                short num = va_arg(args, int);
                string = integer_to_string(num, (size_t)data.width, data.sign, data.align);
                // printf("%s-\n", string);
                my_strcat(buffer, string, &read, count);
                free(string);
            }
            else if (data.specifier == SPEC_OTHER)
            {
                my_strcat(buffer, "%", &read, count);
                format++;
            }
        }
        while (*format && *format != '%')
        {
            if ((int)read < (int)count - 1)
                buffer[read] = *format;
            read++;
            format++;
        }
    }

    if (buffer)
    {
        if ((int)count - 1 > 0)
            buffer[MIN(read, count - 1)] = 0;
        else
            buffer[0] = 0;
    }
    va_end(args);
    return (int)read;
}
