#include "solve.h"

int run(char *string, int *sum)
{
    *sum = 0;
    size_t count = 0;
    char *token = strtok(string, DELIMETERS);

    while (token)
    {
        char *endptr;
        int number = (int)strtol(token, &endptr, 10);
        if (endptr != token && *endptr == 0)
        {
            *sum += number;
            count++;
        }

        token = strtok(NULL, DELIMETERS);
    }

    if (count == 0)
        return ERR_OUTPUT;

    return ERR_OK;
}
