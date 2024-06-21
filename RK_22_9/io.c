#include "io.h"

// Ввод строки
int input_string(char *str, size_t max_len, char *msg)
{
    printf("%s", msg);
    if (!fgets(str, max_len, stdin))
        return ERR_WRONG_INPUT;
    char *newline = strchr(str, '\n');
    if (newline)
    {
        *newline = '\0';
    }
    else
        return ERR_STRING_OWERFLOW;
    return ERR_OK;
}

// Обработка ошибок
void processing_errors(int n)
{
    if (n == ERR_WRONG_INPUT)
        printf("Error, Wrong input\n");
    else if (n == ERR_STRING_OWERFLOW)
        printf("Error, String overflow\n");
    else if (n == ERR_WHILE_READING)
        printf("Error While Reading\n");
    else if (n == ERR_FILE_NOT_FOUND)
        printf("Error, File not found\n");
    else if (n == ERR_EMPTY_OUTPUT)
        printf("Error, Empty output\n");
}
