#include "constants.h"
#include "io.h"
#include "solve.h"

/*3. В строке слова разделены произвольным числом символов-разделителей
(пробел, точка, запятая, двоеточие, точка с запятой).
Разделители могут стоять в начале и в конце строки.
Все слова-палиндромы данной строки записать заглавными буквами.
Решить задачу в двух вариантах: с помощью массива слов и без него.*/

int main(void)
{
    char string[MAX_STRING_LEN + 1], words[MAX_WORDS][MAX_WORD_LEN + 1];
    int rc = ERR_OK;
    size_t word_count = 0;
    if ((rc = input_string(string)) != ERR_OK)
    {
        proccesing_output(rc);
        return rc;
    }

    if ((rc = split_words(words, string, &word_count)))
    {
        proccesing_output(rc);
        return rc;
    }

    if ((rc = solve(words, word_count)))
    {
        proccesing_output(rc);
        return rc;
    }

    
    return rc;
}
