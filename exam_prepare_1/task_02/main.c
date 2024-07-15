#include "constants.h"
#include "io.h"
#include "solve.h"

/* 2. В строке слова разделены произвольным числом символов-разделителей (пробел, точка, запятая, двоеточие, точка с запятой).
Разделители могут стоять в начале и в конце строки. Каждое число в этой строке записать в обратном направлении.
Например, строка «23 тетради и 34 карандаша» после преобразования станет «32 тетради и 43 карандаша».
Решить задачу в двух вариантах: с помощью массива слов и без него.*/

int main(void)
{
    int rc = ERR_OK;
    char string[MAX_STRING_LEN + 1], words[MAX_WORDS][MAX_WORD_LEN + 1];
    size_t word_count = 0;
    if ((rc = input_string(string)) != ERR_OK)
    {
        processing_output(rc);
        return rc;
    }

    if ((rc = split_words(words, string, &word_count)) != ERR_OK)
    {
        processing_output(rc);
        return rc;
    }

    if ((rc = solve(words, word_count)) != ERR_OK)
    {
        processing_output(rc);
        return rc;
    }

    
    return ERR_OK;
}