#include "io.h"
#include "solve.h"
#include "constants.h"

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

void delete_words(char words[][MAX_WORD_LEN + 1], char word_to_delete[], size_t *word_count)
{
    char temp[MAX_STRING_LEN];
    for (size_t i = 0; i < *word_count; i++)
    {
        if (strcmp(words[i], word_to_delete) == 0)
        {
            for (size_t j = i; j < *word_count - 1; j++)
            {
                strcpy(temp, words[j + 1]);
                strcpy(words[j + 1], words[j]);
                strcpy(words[j], temp);
            }
            (*word_count)--;
        }
    }
}

void reverse_word(char words[][MAX_WORD_LEN + 1], size_t len)
{
    char temp[MAX_WORD_LEN + 1];
    for (size_t i = 0; i < len / 2; i++)
    {
        strcpy(temp, words[i]);
        strcpy(words[i], words[len - i - 1]);
        strcpy(words[len - i - 1], temp);
        // printf("%zu, %zu\n", i, len - i - 1);
    }
}

void swap(char arr[MAX_WORD_LEN], size_t first_index, size_t second_index)
{
    char temp;
    temp = arr[second_index];
    arr[second_index] = arr[first_index];
    arr[first_index] = temp;
}

void delete_symbol(size_t index, char arr[MAX_WORD_LEN], size_t *len)
{
    for (size_t i = index; i < *len - 1; i++)
    {
        swap(arr, i, i + 1);
    }
    (*len)--;
    arr[*len] = '\0';
}

void delete_repeat_letters(char arr[])
{
    size_t len = strlen(arr);

    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = i + 1; j < len; j++)
        {
            if (arr[i] == arr[j])
            {
                delete_symbol(j, arr, &len);
                j--;
            }
        }
    }
}

void solve(char words[][MAX_WORD_LEN + 1], char answer[MAX_STRING_LEN + 1], size_t word_count)
{
    size_t arr_len = 0;
    for (size_t i = 0; i < word_count; i++)
    {
        delete_repeat_letters(words[i]);
        for (size_t j = 0; j < strlen(words[i]); j++)
        {
            answer[arr_len++] = words[i][j];
        }
        answer[arr_len++] = ' ';
    }
    answer[arr_len] = '\0';
}
