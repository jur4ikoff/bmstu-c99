#include "io.h"

void output(int arg)
{
    if (arg == ERR_MAX_COUNT)
        printf("Error count lines\n");
    else if (arg == ERR_OVERFLOW)
        printf("String overflow\n");
    else if (arg == ERR_INPUT)
        printf("Empty input\n");
}

int input_count(size_t *count)
{
    if (scanf("%zu", count) != 1)
        return ERR_MAX_COUNT;

    if (*count < 1 || *count > 10)
        return ERR_MAX_COUNT;
    return ERR_OK;
}

int input_string(char *string)
{
    if (!fgets(string, MAX_STRING_LEN, stdin))
        return ERR_INPUT;

    char *newline = strchr(string, '\n');
    if (!newline)
        return ERR_OVERFLOW;
        
    *newline = '\0';

    return ERR_OK;
}
