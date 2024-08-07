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

void output(int arg)
{
    switch (arg)
    {
    case ERR_INPUT:
        printf("ERR_INPUT\n");
        break;
    case ERR_OVERFLOW:
        printf("ERR_OVERFLOW\n");
        break;
    case ERR_TO_MANY:
        printf("ERR_TO_MANY WORDS OR SYMBS.\n");
        break;
    case EMPTY_INPUT:
        printf("EMPTY_INPUT\n");
        break;
    }
}

int split_string(char words[][MAX_WORD_LEN], char *string, size_t *word_count)
{
    *word_count = 0;
    char *token = strtok(string, SEPARATORS);

    while (token)
    {
        if (*word_count >= MAX_WORDS)
            return ERR_TO_MANY;

        strncpy(words[*word_count], token, MAX_STRING_LEN);
        words[*word_count][MAX_STRING_LEN - 1] = '\0';
        (*word_count)++;
        token = strtok(NULL, SEPARATORS);
    }

    return ERR_OK;
}

void to_upper_in_brackets(char words[][MAX_WORD_LEN], size_t word_count)
{
    for (size_t i = 0; i < word_count; i++)
    {
        char element[MAX_WORD_LEN];
        strcpy(element, words[i]);
        size_t len = strlen(element);
        int index_start = -1, index_end = -1;
        for (size_t j = 0; j < len; j++)
        {
            if (element[j] == '"')
                index_start = j;
            if (element[len - j - 1] == '"')
                index_end = len - j - 1;
            if (index_start != -1 && index_end != -1)
                break;
        }
        for (int k = index_start; k <= index_end; k++)
        {
            element[k] = toupper(element[k]);
        }
        printf("%s ", element);
    }
    printf("\n");
}
