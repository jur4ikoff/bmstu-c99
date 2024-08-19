#include "solve.h"

// 1 - True, 0 - False
int is_digit(char *string)
{
    char *ptr = string;
    while (*ptr != 0)
    {
        if (*ptr < '0' || *ptr > '9')
            return 0;

        ptr++;
    }

    return 1;
}

void reverse(char *string)
{
    size_t len = strlen(string);
    for (size_t i = 0; i < len / 2; i++)
    {
        char temp = string[i];
        string[i] = string[len - 1 - i];
        string[len - i - 1] = temp;
    }
}

int run(char *string)
{
    size_t word_count = 0;
    char *token = strtok(string, DELIMETRS);

    while (token)
    {
        int res = is_digit(token);
        if (res == 1)
            reverse(token);
        printf("%s ", token);
        word_count++;
        token = strtok(NULL, DELIMETRS);
    }

    if (word_count == 0)
        return EMPTY_INPUT;
    printf("\n");
    return ERR_OK;
}
