#include "constants.h"
#include "string_proc.h"
// Перевернуть каждое слово внутри

int main(void)
{
    int rc = ERR_OK;
    char string[MAX_STRING_LEN + 1];

    if ((rc = input_string(string)) != ERR_OK)
    {
        output(rc);
        return rc;
    }

    char words[MAX_WORDS][MAX_WORD_LEN];
    size_t word_count = 0;
    if ((rc = separate_words(words, string, &word_count)) != ERR_OK)
    {
        output(rc);
        return rc;
    }

    reverse(words, word_count);

    for (size_t i = 0; i < word_count; i++)
    {
        printf("%s ", words[i]);
    }
    printf("\n");
    return rc;
}
