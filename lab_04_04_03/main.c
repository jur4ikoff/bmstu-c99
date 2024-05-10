#include "io.h"
#include "solve.h"
#include "constants.h"

int main(void)
{
    // инициализация переменных
    int res;
    size_t index = 0;
    char string[MAX_STRING_LEN + 1];

    // Ввод первой строки
    res = string_input(string, MAX_STRING_LEN + 1);
    if (res != 0)
        return res;
    

    // Проверка на пустой ввод
    size_t len = strlen(string);
    if (len == 0)
        return EMPTY_INPUT;

    bool status;
    status = clear_spaces(string, &index);
    if (!status)
    {
        printf("NO\n");
        return SUCCESS_OUTPUT;
    }

    status = extraxt_country_code(string, &index);
    if (!status)
    {
        printf("NO\n");
        return SUCCESS_OUTPUT;
    }

    index++;
    status = extract_operator_code(string, &index);
    if (!status)
    {
        printf("NO\n");
        return SUCCESS_OUTPUT;
    }
    

    status = check_number(string, &index);
    if (!status)
    {
        printf("NO\n");
        return SUCCESS_OUTPUT;
    }
    printf("YES\n");
    return SUCCESS_OUTPUT;
}
