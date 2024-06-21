#include "solve.h"

// Разделение строки на слова
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
        // получаем длину слова
        word_len = strcspn(string, SEPARATORS);
        if (word_len > MAX_WORD_LEN)
            return ERROR_LEN_WORDS;
        // добавляем в двумерный массив
        strncpy(words[*word_count], string, word_len);
        words[*word_count][word_len] = '\0';
        (*word_count)++;
        // Обработка ошибочной ситуации
        if (*word_count > MAX_WORDS)
            return ERROR_COUNT_WORDS;
        string += word_len;
    }
    return 0;
}

// Функция оставляет только уникальные массивы в двумерном массиве
int make_words_unique(char matx[][MAX_WORD_LEN + 1], size_t len)
{
    size_t i, j;
    bool is_unique;
    size_t count = len;
    // Попарно итеррируемся по элементам двумерного массива
    for (i = 0; i < len; i++)
    {
        is_unique = true;
        for (j = i + 1; j < len; j++)
        {
            // Проверка на существование массива
            if (matx[i][0] == '\0' || matx[j][0] == '\0')
                continue;

            // Сравнение строк и обработка ситуации
            if (strcmp(matx[i], matx[j]) == 0)
            {
                is_unique = false;
                matx[j][0] = '\0';
                count--;
            }
        }
        if (!is_unique)
        {
            matx[i][0] = '\0';
            count--;
        }
    }
    return count;
}
