#include "string_proc.h"

int separate_words(char words[][MAX_WORD_LEN], char *string, size_t *word_count)
{
    char *token = strtok(string, SEPARATORS);
    *word_count = 0;

    while (token != NULL)
    {
        if (*word_count >= MAX_WORDS)
            return ERR_INPUT;

        strncpy(words[*word_count], token, MAX_WORD_LEN - 1);
        words[*word_count][MAX_WORD_LEN - 1] = '\0';
        (*word_count)++;
        token = strtok(NULL, " ");
    }
    return ERR_OK;
}

void reverse(char words[][MAX_WORD_LEN], size_t word_count)
{
    for (size_t i = 0; i < word_count; i++)
    {
        size_t len = strlen(words[i]);
        for (size_t j = 0; j < len / 2; j++)
        {
            char temp = words[i][j];
            words[i][j] = words[i][len - j - 1];
            words[i][len - j - 1] = temp;
        }
    }
}