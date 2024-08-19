/*В строке слова разделены произвольным числом символов-разделителей (пробел, точка,
запятая, двоеточие, точка с запятой). Разделители могут стоять в начале и в конце
строки. Каждое число в этой строке записать в обратном направлении. Например, строка
«23 тетради и 34 карандаша» после преобразования станет «32 тетради и 43 карандаша».*/
#include "constants.h"
#include "io.h"
#include "solve.h"

int main(void)
{
    int rc = ERR_OK;
    char string[MAX_STRING_LEN + 1];
    if ((rc = input_string(string)) != ERR_OK)
    {
        processing_errors(rc);
        return rc;
    }

    if ((rc = run(string)) != ERR_OK)
    {
        processing_errors(rc);
        return rc;
    }
    return rc;
}
