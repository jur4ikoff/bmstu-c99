#include "io.h"

int input_string(char *string)
{
    if (!fgets(string, MAX_STRING_LEN, stdin))
        return ERR_EMPTY;

    char *newline = strchr(string, '\n');
    if (!newline)
        return ERR_OVERFLOW;

    *newline = '\0';
    return ERR_OK;
}

void process_errors(int arg)
{
    switch (arg)
    {
    case ERR_EMPTY:
        printf("ERR_EMPTY\n");
        break;
    case ERR_OVERFLOW:
        printf("ERR_OVERFLOW\n");
        break;
    case ERR_UNKNOWN:
        printf("ERR_UNKNOWN\n");
        break;
    }
}
