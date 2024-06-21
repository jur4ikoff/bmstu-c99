#include "io.h"
#include "solve.h"
#include "constants.h"

int main(void)
{
    // инициализация переменных
    int res;
    char string[MAX_STRING_LEN * 2 + 2];

    // Ввод строки
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

    // Создаю двумерный массив для слов и разделяю строку на слова
    char words[MAX_WORDS][MAX_WORD_LEN + 1];
    res = separate_words(words, string, &word_count);
    if (res != 0)
    {
        processing_errors(res);
        return res;
    }

    // Копирование последнего слова для последующего удаления
    char word_to_delete[MAX_STRING_LEN];
    strcpy(word_to_delete, words[word_count - 1]);

    // Запуск функции для удаления слов равных поледнему
    delete_words(words, word_to_delete, &word_count);

    // Запись двумерного массива в обратном порядке
    reverse_word(words, word_count);

    // Запуск функции с решением задачи
    char answer[MAX_STRING_LEN + 1];
    solve(words, answer, word_count);

    // Вывод результата
    if (word_count == 0)
    {
        processing_errors(EMPTY_OUTPUT);
        return EMPTY_OUTPUT;
    }
    printf("Result: %s\n", answer);
    return SUCCESS_OUTPUT;
}
