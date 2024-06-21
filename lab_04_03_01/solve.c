#include "io.h"
#include "solve.h"
#include "constants.h"

// Проверка на то ялвяется ли символ разделитилем
int is_delimiter(char c)
{
    size_t separators_count = strlen(SEPARATORS);
    for (size_t i = 0; i < separators_count; i++)
    {
        if (c == SEPARATORS[i])
            return 1;
    }

    return 0;
}

int separate_words(char words[][MAX_WORD_LEN + 1], char *sentence, size_t *word_count)
{
    size_t len = strlen(sentence);
    if (len == 0 || sentence[0] == '\0')
    {
        return EMPTY_OUTPUT;
    }

    size_t count = 0;
    size_t word_len = 0;

    for (size_t i = 0; i < len; i++)
    {
        if (!is_delimiter(sentence[i]))
        {
            if (count >= MAX_WORDS)
                return ERROR_COUNT_WORDS;
            else if (word_len >= MAX_WORD_LEN)
                return ERROR_LEN_WORDS;
            words[count][word_len++] = sentence[i];
        }
        else
        {
            if (word_len > 0)
            {
                words[count][word_len] = '\0'; // Null-terminate the word
                count++;
                word_len = 0;
            }
        }
    }

    // Add the last word if it exists
    if (word_len > 0)
    {
        if (count >= MAX_WORDS || word_len >= MAX_WORD_LEN)
        {
            return -2; // Exceeded maximum number of words or word length
        }

        words[count][word_len] = '\0';
        count++;
    }

    *word_count = count;
    return 0; // Success
}

// Удаление слова схожего с заданным
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
            i--;
            (*word_count)--;
        }
    }
}

// "Разворот" двумерного массива
void reverse_word(char words[][MAX_WORD_LEN + 1], size_t len)
{
    char temp[MAX_WORD_LEN + 1];
    for (size_t i = 0; i < len / 2; i++)
    {
        strcpy(temp, words[i]);
        strcpy(words[i], words[len - i - 1]);
        strcpy(words[len - i - 1], temp);
    }
}

// Функция меняет местами два элемента одномерно массива
void swap(char arr[MAX_WORD_LEN], size_t first_index, size_t second_index)
{
    char temp;
    temp = arr[second_index];
    arr[second_index] = arr[first_index];
    arr[first_index] = temp;
}

// Функция удаляет символ из одномерного массива чаров
void delete_symbol(size_t index, char arr[MAX_WORD_LEN], size_t *len)
{
    for (size_t i = index; i < *len - 1; i++)
    {
        swap(arr, i, i + 1);
    }
    (*len)--;
    arr[*len] = '\0';
}

// Функция удаляет все символы, которые употребляются более 1-го раза
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

// Запуск решения
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
