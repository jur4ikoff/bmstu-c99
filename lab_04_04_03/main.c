#include "io.h"
#include "solve.h"
#include "constants.h"

int main(void)
{
    // инициализация переменных
    int res;
    size_t index = 0;
    char string[MAX_STRING_LEN + 1];

    // Ввод строки с номером
    res = string_input(string, MAX_STRING_LEN + 1);
    if (res != 0)
        return res;

    // Проверка на пустой ввод
    size_t len = strlen(string);
    if (len == 0)
    {
        printf("NO\n");
        return SUCCESS_OUTPUT;
    }

    // Пропуск пробельных символов в начале
    bool status = clear_spaces(string, &index);
    if (!status)
    {
        printf("NO\n");
        return SUCCESS_OUTPUT;
    }

    // Проверка на существование кода страны
    status = extraxt_country_code(string, &index);
    if (!status)
    {
        printf("NO\n");
        return SUCCESS_OUTPUT;
    }
    index++;

    // Проверка на корректность кода оператора
    status = extract_operator_code(string, &index);
    if (!status)
    {
        printf("NO\n");
        return SUCCESS_OUTPUT;
    }

    // Проверка номера
    status = check_number(string, &index);
    if (!status)
    {
        printf("NO\n");
        return SUCCESS_OUTPUT;
    }

    // Вывод
    printf("YES\n");
    return SUCCESS_OUTPUT;
}
