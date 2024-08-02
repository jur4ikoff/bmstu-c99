#include "my_strlib.h"

int separate_words(char words[][MAX_WORD_LEN], char *string, size_t *word_count)
{
    size_t word_len, spaces;

    while (*string != '\0')
    {

        spaces = strspn(string, SEPARATORS);
        string += spaces;
        if (*string == '\0')
            break;

        word_len = strcspn(string, SEPARATORS);
        strncpy(words[*word_count], string, word_len);
        words[*word_count][word_len] = '\0';
        (*word_count)++;

        if (*word_count > MAX_WORD_LEN)
            return ERR_UNKNOWN;
        string += word_len;
    }

    return ERR_OK;
}

// Функция проверяет является ли строка число 0 - не явл, 1 - явл
int check_is_number(char *string)
{
    if (*string == '\0')
        return 0;

    while (*string != '\0')
    {
        if (*string >= '0' && *string <= '9')
        {
            string++;
        }
        else
            return 0;
    }

    return 1;
}

// Конвертирует строку в число
int convert_string_to_int(char *string)
{
    int number = 0;
    while (*string != '\0')
    {
        number = number * 10 + (*string - '0');
        string++;
    }

    return number;
}

// Функция конвертирует слова в числа
int sum_only_int(char words[][MAX_WORD_LEN], size_t word_count, int *sum)
{
    *sum = 0;
    size_t convert_count = 0;
    for (size_t i = 0; i < word_count; i++)
    {
        if (check_is_number(words[i]) == 1)
        {
            *sum += convert_string_to_int(words[i]);
            convert_count++;
        }
    }
    if (convert_count == 0)
        return ERR_EMPTY;
    return ERR_OK;
}
