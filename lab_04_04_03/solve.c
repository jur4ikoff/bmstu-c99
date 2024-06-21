#include "io.h"
#include "solve.h"
#include "constants.h"

// Пропуск пробельных символв
bool clear_spaces(char string[], size_t *index)
{
    while (isspace(string[*index]) != 0)
    {
        (*index)++;
        if (string[*index] == '\0')
            return false;
    }
    return true;
}

// Проверка на конец последовательности
bool check_endline(char string[], size_t *index)
{
    while (string[*index] != '\0')
    {
        if (isspace(string[*index]) == 0)
            return false;
        (*index)++;
    }
    return true;
}

// Проверка содержимого кода страны
bool extraxt_country_code(char string[], size_t *index)
{
    if (string[*index] == '+')
    {
        (*index)++;
        while (isdigit(string[*index]) != 0)
        {
            (*index)++;
            if (string[*index] == '\0')
                return false;
            if (string[*index] == '(')
                return true;
        }
    }
    else
    {
        if (string[*index] == '(')
            return true;
    }

    return false;
}

// Проверка кода оператора
bool extract_operator_code(char string[], size_t *index)
{
    size_t count = 0;
    while (isdigit(string[*index]) != 0)
    {
        (*index)++;
        count++;
        if (string[*index] == ')' && count == 3)
            return true;
    }
    return false;
}

// Проверка комбинации чисел
bool check_numbers_combinations(char string[], size_t *index, size_t count)
{
    size_t cur = 0;
    while (cur != count)
    {
        if (isdigit(string[*index]) != 0)
        {
            (*index)++;
            cur++;
        }
        else
            return false;
    }
    if (cur == count)
        return true;
    return false;
}

// Проверка по маске сочетания последних цифр
bool check_number(char string[], size_t *index)
{
    bool status = true;
    (*index)++;
    if (string[*index] != '-')
        return false;
    (*index)++;

    status = check_numbers_combinations(string, index, 3);
    if (!status)
    {
        return false;
    }
    if (string[*index] != '-')
        return false;
    (*index)++;

    status = check_numbers_combinations(string, index, 2);
    if (!status)
        return false;

    if (string[*index] != '-')
        return false;

    (*index)++;
    status = check_numbers_combinations(string, index, 2);
    if (!status)
        return false;

    status = check_endline(string, index);
    return status;
}
