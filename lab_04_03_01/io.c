#include "io.h"

// Считывание строки из входного потока
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

// Обработка ошибок
void processing_errors(int exitcode)
{
    if (exitcode == 2)
        printf("One of world too long\n");
    else if (exitcode == 3)
        printf("Words too many\n");
    else if (exitcode == 4)
        printf("Empty Output\n");
    else if (exitcode == 5)
        printf("Empty Input\n");
    else if (exitcode == 6)
        printf("Error While Input\n");
    else if (exitcode == 7)
        printf("String Overflow\n");
}
