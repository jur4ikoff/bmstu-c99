#include "io.h"

// Функция принимает строку из стандартного ввода
int string_input(char *str, size_t max_len)
{
    if (!fgets(str, max_len, stdin))
        return INPUT_ERROR;
    char *newline = strchr(str, '\n');
    if (newline)
        *newline = '\0';
    else
        return STRING_OVERFLOW;
    return 0;
}
