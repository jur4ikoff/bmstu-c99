#include "io.h"

int input_string(char *string)
{
    if (!fgets(string, MAX_STRING_LEN, stdin))
        return ERR_INPUT;

    char *newline = strchr(string, '\n');
    if (!newline)
        return ERR_INPUT;
    *newline = '\0';

    return ERR_OK;
}

void processing_output(int args)
{
    if (args == ERR_INPUT)
        printf("Wrong input\n");
    else if (args == ERR_LENGTH)
        printf("Wrong Length\n");
}