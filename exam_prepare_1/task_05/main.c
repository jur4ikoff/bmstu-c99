#include "constants.h"
#include "io.h"
#include "my_strlib.h"
/*На вход строка не более 32 символов.
Из строки выделить слова, разделеленные табом и пробелами.
Найти слова, которые являются натуральными числами или нулем и найти сумму.
Если строка состоит только из \n, то ERR_EMPTY.
Если нет чисел, то ERR_NO_DATA.
Если переполнение (последний символ не \n), то ERR_OVERFLOW.
Иначе ERR_UNKNOWN.

Пример:
I 03 live 15 in 10 Moscow 2
Вывод:
30
Использовать стандартные функции перевода из строки в число нельзя*/

int main(void)
{
    int rc = ERR_OK;
    char string[MAX_STRING_LEN], words[MAX_WORDS][MAX_WORD_LEN];

    if ((rc = input_string(string)) != ERR_OK)
    {
        process_errors(rc);
        return rc;
    }

    size_t word_count = 0;
    if ((rc = separate_words(words, string, &word_count)) != ERR_OK)
    {
        process_errors(rc);
        return rc;
    }

    int sum = 0;
    if ((rc = sum_only_int(words, word_count, &sum)) != ERR_OK)
    {
        process_errors(rc);
        return rc;
    }

    printf("%d\n", sum);
    return rc;
}
