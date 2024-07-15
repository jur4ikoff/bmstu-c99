#include "constants.h"
#include "io.h"
/*    1. В строке слова разделены произвольным числом символов-разделителей (пробел, точка, запятая, двоеточие, точка с запятой).
Разделители могут стоять в начале и в конце строки. Некоторые слова являются числами. Поменять местами максимальное и минимальное числа.
Решить задачу в двух вариантах: с помощью массива слов и без него.*/

int main(void)
{
    char str[MAX_STRING_LEN + 1], words[MAX_WORDS][MAX_WORD_LEN + 1];
    size_t word_count = 0;
    int rc = ERR_OK;

    if ((rc = input_string(str, MAX_STRING_LEN)) != ERR_OK)
    {
        proccesing_errors(rc);
        return rc;
    }

    if ((rc = split_string(words, str, &word_count)) != ERR_OK)
    {
        proccesing_errors(rc);
        return rc;
    }

    if ((rc = solve(words, word_count)) != ERR_OK)
    {
        proccesing_errors(rc);
        return rc;
    }
    
    print_words(words, word_count);
    
    return ERR_OK;
}