#include "io.h"

int input_string(char *string, size_t len)
{
    if (!fgets(string, len, stdin))
        return ERR_INPUT;

    char *newline = strchr(string, '\n');
    if (newline)
        *newline = '\0';
    else
        return ERR_STRING_OVERFLOW;

    return ERR_OK;
}

void proccesing_errors(int arg)
{
    if (arg == ERR_INPUT)
        printf("Error Input\n");
    else if (arg == ERR_STRING_OVERFLOW)
        printf("String Overflow\n");
    else if (arg == ERR_LEN)
        printf("Wring length\n");
    else if (arg == ERR_MAX_MIN)
        printf("No max and min number\n");
}

int split_string(char words[][MAX_WORD_LEN + 1], char *string, size_t *count)
{
    *count = 0;
    size_t word_len;
    while (*string != '\0')
    {
        size_t spaces = strspn(string, SEPARATORS);
        string += spaces;
        if (*string == '\0')
            break;

        word_len = strcspn(string, SEPARATORS);
        if (word_len >= MAX_WORD_LEN)
            return ERR_LEN;
        strncpy(words[*count], string, word_len);
        (*count)++;

        if (*count > MAX_WORDS)
            return ERR_LEN;

        string += word_len;
    }

    return ERR_OK;
}

int is_digit(char *string, int *num)
{
    if (strcmp(string, "0") == 0)
    {
        *num = 0;
        return 0;
    }
    int res = atoi(string);
    if (res != 0)
    {
        *num = res;
        return 0;
    }
    return 1;
}

void swap(size_t index1, size_t index2, char words[][MAX_WORD_LEN + 1])
{
    char temp[MAX_WORD_LEN + 1];
    strcpy(temp, words[index1]);
    strcpy(words[index1], words[index2]);
    strcpy(words[index2], temp);
}

int solve(char words[][MAX_WORD_LEN + 1], size_t word_count)
{
    size_t index_min = 0, index_max = 0;
    int min = 10e6, max = -10e6;
    for (size_t i = 0; i < word_count; i++)
    {
        int num;
        int res = is_digit(words[i], &num);
        if (res != 0)
            continue;
        else
        {
            if (num < min)
            {
                min = num;
                index_min = i;
            }
            else if (num > max)
            {
                max = num;
                index_max = i;
            }
        }
    }
    if (index_min == 0 && index_max == 0)
        return ERR_MAX_MIN;

    swap(index_min, index_max, words);
    return ERR_OK;
}

void print_words(char words[][MAX_WORD_LEN + 1], size_t word_count)
{
    for (size_t i = 0; i < word_count; i++)
        printf("%s ", words[i]);
    printf("\n");
}