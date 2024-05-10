#include "solve.h"

int separate_words(char words[][MAX_WORD_LEN + 1], char *string, size_t *word_count)
{
    size_t spaces, word_len;
    while (*string != '\0')
    {
        // Извлечение количества знаков препинания и сдвиг указателя строки на это число
        spaces = strspn(string, SEPARATORS);
        string += spaces;
        if (*string == '\0')
            break;

        word_len = strcspn(string, SEPARATORS);
        if (word_len > MAX_WORD_LEN)
            return ERROR_LEN_WORDS;
        strncpy(words[*word_count], string, word_len);
        words[*word_count][word_len] = '\0';
        (*word_count)++;
        if (*word_count > MAX_WORDS)
            return ERROR_COUNT_WORDS;
        string += word_len;
    }
    return 0;
}

int make_words_unique(char matx[][MAX_WORD_LEN + 1], size_t len)
{
    size_t i, j;
    bool is_unique;
    size_t count = len;
    for (i = 0; i < len; i++)
    {
        is_unique = true;

        for (j = i + 1; j < len; j++)
        {
            if (matx[i][0] == '\0' || matx[j][0] == '\0')
                continue;
            if (strcmp(matx[i], matx[j]) == 0)
            {
                is_unique = false;
                matx[j][0] = '\0';
                count--;
                // break;
            }
            // printf("%s %s\n", matx[i], matx[j]);
        }
        if (!is_unique)
        {
            matx[i][0] = '\0';
            count--;
        }
    }
    // printf("count %zu\n", count);
    return count;
}
