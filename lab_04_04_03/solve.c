#include "io.h"
#include "solve.h"
#include "constants.h"

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

bool extraxt_country_code(char string[], size_t *index)
{
    if (string[*index] != '+')
        return false;
    (*index)++;
    while (isdigit(string[*index]) != 0)
    {
        (*index)++;
        if (string[*index] == '\0')
            return false;
        if (string[*index] == '(')
            return true;
    }

    return false;
}

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
