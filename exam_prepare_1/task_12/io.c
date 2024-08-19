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

void processing_errors(int arg)
{
    switch (arg)
    {
    case ERR_INPUT:
        printf("ERR_INPUT");
        break;
    case ERR_OVERFLOW:
        printf("ERR_OVERFLOW");
        break;
    case EMPTY_INPUT:
        printf("EMPTY_INPUT");
        break;
    }
}
