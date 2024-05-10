#include "io.h"
#include "solve.h"
#include "constants.h"

int main(void)
{
    // инициализация переменных
    int res;
    char string[MAX_STRING_LEN * 2 + 2];

    // Ввод первой строки
    res = string_input(string, MAX_STRING_LEN + 1);
    if (res != 0)
    {
        processing_errors(res);
        return res;
    }

    // Проверка на пустой ввод
    size_t len = strlen(string), word_count = 0;
    if (len == 0)
    {
        processing_errors(EMPTY_INPUT);
        return EMPTY_INPUT;
    }

    char words[MAX_WORDS][MAX_WORD_LEN + 1];
    res = separate_words(words, string, &word_count);
    if (res != 0)
    {
        processing_errors(res);
        return res;
    }
    
    char word_to_delete[MAX_STRING_LEN];
    strcpy(word_to_delete, words[word_count - 1]);
    delete_words(words, word_to_delete, &word_count);
    reverse_word(words, word_count);
    char answer[MAX_STRING_LEN + 1];
    solve(words, answer, word_count);
    printf("Result: %s\n", answer);
    // print_line(words, word_count);

    // return 0;

    // Замена знаков препинания на пробел
    // replace_punctuation(string, MAX_STRING_LEN * 2 + 2);
    // remove_extra_spaces(string);
    // printf("%s\n", string);
    return SUCCESS_OUTPUT;
}
