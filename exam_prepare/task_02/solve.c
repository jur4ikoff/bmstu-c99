#include "solve.h"

int split_words(char words[][MAX_WORD_LEN + 1], char *string, size_t *count)
{
    size_t word_len;
    *count = 0;

    while (*string != '\0')
    {
        size_t spaces = strspn(string, SEPARATORS);
        string += spaces;

        if (*string == '\0')
            break;

        word_len = strcspn(string, SEPARATORS);
        if (word_len > MAX_WORD_LEN)
            return ERR_LENGTH;

        strncpy(words[*count], string, word_len);
        // words[*count][word_len] = '\0';
        (*count)++;
        if (*count > MAX_WORDS)
            return ERR_LENGTH;

        string += word_len;
    }

    return ERR_OK;
}

// 0 - if not number, 1 if number
int is_number(char *string)
{
    if (strcmp(string, "0") == 0)
        return 1;
    char *endptr;
    strtol(string, &endptr, 10);
    if (*endptr != '\0')
        return 0;
    else
        return 1;
    return 0;
}

void reverse_string(char string[MAX_STRING_LEN])
{
    size_t len = strlen(string);
    for (size_t i = 0; i < (len / 2); i++)
    {
        char temp = string[i];
        string[i] = string[len - i - 1];
        string[len - i - 1] = temp;
    }
}

int solve(char words[][MAX_WORD_LEN + 1], size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        if (is_number(words[i]) == 1)
        {
            char element[MAX_STRING_LEN];
            strcpy(element, words[i]);
            reverse_string(element);
            strcpy(words[i], element);
            printf("%s ", words[i]);
        }
    }
    printf("\n");
    return ERR_OK;
}