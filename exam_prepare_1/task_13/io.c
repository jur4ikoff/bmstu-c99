#include "io.h"

int input_string(char *string)
{
    if (!(fgets(string, MAX_STRING_LEN, stdin)))
        return ERR_INPUT;

    char *newline = strchr(string, '\n');
    if (!newline)
        return ERR_OVERFLOW;

    *newline = '\0';
    return ERR_OK;
}

void output_rc(int arg)
{
    switch (arg)
    {
    case ERR_INPUT:
        printf("ERR_INPUT");
        break;
    case ERR_OVERFLOW:
        printf("ERR_OVERFLOW");
        break;
    case ERR_EMPTY:
        printf("ERR_EMPTY");
        break;
    }
}
