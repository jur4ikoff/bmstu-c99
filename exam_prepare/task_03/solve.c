#include "solve.h"

int split_words(char words[][MAX_WORD_LEN + 1], char *string, size_t *word_count)
{
    *word_count = 0;
    size_t word_len;

    while (*string != '\0')
    {
        size_t spaces = strspn(string, SEPARATORS);
        string += spaces;
        if (*string == 0)
            break;

        word_len = strcspn(string, SEPARATORS);
        if (word_len > MAX_WORD_LEN)
            return ERR_LENGTH;

        strncpy(words[*word_count], string, word_len);
        words[*word_count][word_len] = '\0';
        (*word_count)++;

        if (*word_count > MAX_WORDS)
            return ERR_LENGTH;

        string += word_len;
    }

    if (*word_count == 0)
        return ERR_LENGTH;

    return ERR_OK;
}

//  1 if palindrome else 0
int check_palindrome(char *string)
{
    size_t len = strlen(string);
    for (size_t i = 0; i < (len / 2); i++)
    {
        if (string[i] != string[len - i - 1])
            return 0;
    }
    return 1;
}

void upper(char *string)
{
    char *ptr = string;
    while (*ptr != 0)
    {
        *ptr = toupper(*ptr);
        ptr++;
    }
}

int solve(char words[][MAX_WORD_LEN + 1], size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        char element[MAX_WORD_LEN + 1];
        strcpy(element, words[i]);
        // printf("%s\n", element);
        if (check_palindrome(element) == 1)
        {
            upper(element);
            printf("%s ", element);
        }
        else
            printf("%s ", element);
    }
    printf("\n");
    return ERR_OK;
}