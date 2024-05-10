#include "io.h"
#include "solve.h"

int main(void)
{
    // инициализация переменных
    int res;
    char string1[MAX_STRING_LEN + 1], string2[MAX_STRING_LEN + 1], string[MAX_STRING_LEN * 2 + 1];
    string[0] = 0;
    // Ввод первой строки
    res = string_input(string1, MAX_STRING_LEN + 1);
    if (res != 0)
    {
        processing_errors(res);
        return res;
    }
    // return 0;
    // Ввод второй строки
    res = string_input(string2, MAX_STRING_LEN + 1);
    if (res != 0)
    {
        processing_errors(res);
        return res;
    }
    
    // Проверка на пустой ввод
    size_t len1 = strlen(string1), len2 = strlen(string2);
    if (len1 == 0 && len2 == 0)
    {
        processing_errors(EMPTY_INPUT);
        return EMPTY_INPUT;
    }

    
    // Склеивание двух строк в одну
    strcat(string, string1);
    strcat(string, " ");
    strcat(string, string2);


    // Замена знаков препинания на пробел
    char words[MAX_WORDS * 2][MAX_WORD_LEN + 1];
    size_t word_count = 0;
    // int separate_words(char words[][MAX_WORD_LEN + 1], char *string, size_t *word_count);
    res = separate_words(words, string, &word_count);

    if (res != 0)
    {
        processing_errors(res);
        return res;
    }

    res = make_words_unique(words, word_count);
    if (res <= 0)
    {
        processing_errors(EMPTY_OUTPUT);
        return EMPTY_OUTPUT;
    }

    print_line(words, word_count);
    return SUCCESS_OUTPUT;
}
