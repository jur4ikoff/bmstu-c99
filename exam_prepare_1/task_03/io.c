#include "io.h"

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

void proccesing_output(int arg)
{
    if (arg == ERR_INPUT)
        printf("Wrong Input\n");
    else if (arg == ERR_OVERFLOW)
        printf("To long string\n");
    else if (arg == ERR_LENGTH)
        printf("Err word\n");
}