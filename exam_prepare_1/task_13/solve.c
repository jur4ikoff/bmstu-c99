#include "solve.h"

// 1 - true 0 - false
int is_apostrophe(char *string)
{
    size_t len = strlen(string);
    if (string[0] == '\'' && string[len - 1] == '\'')
        return 1;

    return 0;
}

void solve(char *string)
{
    char *ptr = string + 1;
    while (*ptr != 0)
    {
        *ptr = toupper(*ptr);
        ptr++;
        if (*ptr == 0)
            break;

        *ptr = tolower(*ptr);
        ptr++;
    }
}

int run(char *string)
{
    size_t word_count = 0;
    char *token = strtok(string, DELIMETRS);
    while (token)
    {
        if (is_apostrophe(token) == 1)
            solve(token);

        printf("%s ", token);
        word_count++;
        token = strtok(NULL, DELIMETRS);
    }

    if (word_count == 0)
        return ERR_EMPTY;
    printf("\n");
    return ERR_OK;
}