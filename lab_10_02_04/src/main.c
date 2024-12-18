/*
Варианты 1: 1,2 и 2: 1, 3:1
Аргументы указываются в формате ./app.exe OPERATION FILE_IN FILE_OUT
Возможные операции:
F - поиск
P - Вставка в начало списка
C - Копирование списка
S - Сортировка
Задача:
*/

#include "constants.h"
#include "errors.h"
#include "list.h"
#include "number.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Функция выводит сообщения об ошибке
static void print_error_message(int arg)
{
#if DEBUG
    printf("%s", RED);
    if (arg == ERR_STRING_INPUT)
        printf("Ошибка, при вводе строки\n");
    else if (arg == ERR_OPERATION)
        printf("Ошибка при выборе операции\n");
    else if (arg == ERR_NUMBER)
        printf("Ошибка при вводе числа\n");
    else if (arg == ERR_MEMORY_ALLOCATION)
        printf("Ошибка при выделении памяти\n");
    else if (arg == ERR_CONVERTATION)
        printf("Ошибка при конвертации числа список целых чисел\n");
    else if (arg == ERR_DIV)
        printf("Ошибка во время деления числа")
    printf("%s", RESET);
#else
    (void)arg;
#endif
}

// Функция проверяет корректность аргумента операции и возвращает соответствующее значение из перечисления operations_t
static operations_t validate_operation_arg(char *argument)
{
    if (strcmp(argument, "out") == 0)
        return OP_OUT;
    else if (strcmp(argument, "mul") == 0)
        return OP_MULT;
    else if (strcmp(argument, "sqr") == 0)
        return OP_SQRT;
    else if (strcmp(argument, "div") == 0)
        return OP_DIV;

    return OP_UNKNOWN;
}

int input_string(char *string, size_t max, FILE *file)
{
    if (!fgets(string, max, file))
        return ERR_STRING_INPUT;

    char *newline = strchr(string, '\n');
    if (!newline)
        return ERR_STRING_INPUT;

    *newline = 0;
    if (strlen(string) < 1)
        return ERR_STRING_INPUT;

    return ERR_OK;
}

int main(void)
{
    int rc = ERR_OK;
    // Проверка на количвество аргументов
    char string_operation[MAX_OPERATION_LEN];

    if ((rc = input_string(string_operation, MAX_OPERATION_LEN, stdin)) != ERR_OK)
    {
        print_error_message(rc);
        return rc;
    }

    if (strlen(string_operation) != OPERATION_STRING_LEN)
    {
        rc = ERR_OPERATION;
    }

    // Валидация первого аргумента
    operations_t operation = validate_operation_arg(string_operation);
    if (operation == OP_UNKNOWN)
    {
        print_error_message(ERR_OPERATION);
        return ERR_OPERATION;
    }
    else if (operation == OP_OUT)
    {
        long long number;

        if (scanf("%lld", &number) != 1)
        {
            print_error_message(ERR_NUMBER);
            return ERR_NUMBER;
        }

        node_t *convert_number = NULL;
        if ((rc = convert_to_list(&convert_number, number)) != ERR_OK)
        {
            print_error_message(rc);
            free_full(convert_number);
            return rc;
        }

        apply_list(convert_number, print_number);
        free_full(convert_number);
    }
    else if (operation == OP_MULT)
    {
        long long number_1, number_2;
        if (scanf("%lld %lld", &number_1, &number_2) != 2)
        {
            print_error_message(ERR_NUMBER);
            return ERR_NUMBER;
        }

        node_t *convert_number_1 = NULL, *convert_number_2 = NULL;
        if ((rc = convert_to_list(&convert_number_1, number_1)) != ERR_OK)
        {
            print_error_message(rc);
            free_full(convert_number_1);
            return rc;
        }

        if ((rc = convert_to_list(&convert_number_2, number_2)) != ERR_OK)
        {
            print_error_message(rc);
            free_full(convert_number_1);
            free_full(convert_number_2);
            return rc;
        }

        node_t *mult_list = NULL;
        mult_list = mult_number(convert_number_1, convert_number_2, compare_by_prime);
        apply_list(mult_list, print_number);

        free_full(mult_list);
    }
    else if (operation == OP_SQRT)
    {
        long long number;
        if (scanf("%lld", &number) != 1)
        {
            print_error_message(ERR_NUMBER);
            return ERR_NUMBER;
        }

        node_t *convert_number = NULL;
        if ((rc = convert_to_list(&convert_number, number)) != ERR_OK)
        {
            print_error_message(rc);
            return rc;
        }

        node_t *sqrt_head = sqrt_list(convert_number);
        apply_list(sqrt_head, print_number);
        free_full(sqrt_head);
    }
    else if (operation == OP_DIV)
    {
        // Целочисленное деление
        long long number_1, number_2;
        if (scanf("%lld %lld", &number_1, &number_2) != 2)
        {
            print_error_message(ERR_NUMBER);
            return ERR_NUMBER;
        }

        node_t *div_result = NULL;
        div_result = div_list(number_1, number_2);

        if (div_result == NULL)
            return ERR_DIV;
        apply_list(div_result, print_number);
        free_full(div_result);
    }

    return rc;
}
