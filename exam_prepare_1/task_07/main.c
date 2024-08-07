/*      строке слова разделены произвольным числом символов-разделителей (пробел, точка, запятая, двоеточие, точка с запятой).
Разделители могут стоять в начале и в конце строки. Все слова, стоящие в двойных кавычках записать заглавными буквами.
Вложенность кавычек не допускается.
Решить задачу в двух вариантах: с помощью массива слов и без него.
*/

#include "constants.h"
#include "io.h"

int main(void)
{
    size_t word_count = 0;
    int rc = ERR_OK;
    char string[MAX_STRING_LEN + 1], words[MAX_WORDS][MAX_WORD_LEN];
    if ((rc = input_string(string)) != ERR_OK)
    {
        output(rc);
        return rc;
    }

    if ((rc = split_string(words, string, &word_count)) != ERR_OK)
    {
        output(rc);
        return rc;
    }

    if (word_count == 0)
    {
        output(EMPTY_INPUT);
        return EMPTY_INPUT;
    }

    to_upper_in_brackets(words, word_count);

    return rc;
}
