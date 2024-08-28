/*На вход подается слова, нужно сложить все числа в строке*/

#include "constants.h"
#include "io.h"
#include "solve.h"

int main(void)
{
    int rc = ERR_OK;

    char string[MAX_STRING_LEN + 1];
    if ((rc = input_string(string)) != ERR_OK)
    {
        output(rc);
        return rc;
    }
    int result = 0;
    if ((rc = run(string, &result)) != ERR_OK)
    {
        output(rc);
        return rc;
    }
    printf("%d\n", result);
    return rc;
}
