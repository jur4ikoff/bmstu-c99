#include "mystrlib.h"

// Функция проверяет, принадлежит ли символ cur_symb строке find
bool check_include_symbol(char const *cur_symb, char const *find)
{
    while (*find != '\0')
    {
        if (*find == *cur_symb)
        {
            return true;
        }
        find++;
    }
    return false;
}

// Функция - аналог библиотечной функции strlen, возвращает длинну строки
size_t my_strlen(char const *string)
{
    size_t len = 0;
    for (size_t i = 0; *(string + i) != '\0'; i++)
    {
        len++;
    }
    return len;
}

// Функция - аналог библиотечной функции strpbrk. Возвращает указатель на первое вхождение символов из строки find
char const *my_strpbrk(char const *str, char const *find)
{
    bool res = false;
    char const *ptr = str;
    for (ptr = str; *ptr != '\0'; ptr++)
    {
        res = check_include_symbol(ptr, find);
        if (res)
            return ptr;
    }

    return NULL;
}

/* Функция - аналог библиотечной функции strspn. Вычисляет длину начального сегмента строки str,
состоящего только из символов строки symbols */
size_t my_strspn(char const *str, char const *symbols)
{
    size_t count = 0;
    char const *ptr;
    for (ptr = str; *ptr != '\0'; ptr++)
    {
        if (check_include_symbol(ptr, symbols))
            count++;
        else
            break;
    }
    return count;
}

/* Функция - аналог библиотечной функции strcspn. Вычисляет длину начального сегмента строки str,
до первого вхождения символов из строкт symbols */
size_t my_strcspn(char const *str, char const *symbols)
{
    size_t count = 0;
    char const *ptr;
    for (ptr = str; *ptr != '\0'; ptr++)
    {
        if (check_include_symbol(ptr, symbols))
            return count;
        count++;
    }

    return count;
}
/* Функция - аналог библиотечной функции strchr. Возвращает указатель на первое вхождение символа в строке.
NULL, если символ не встретился*/
char const *my_strchr(char const *str, int symbol)
{
    if (str == NULL || symbol > 255 || symbol < 0)
        return NULL;

    if (symbol == 0)
        return (char *)(str + strlen(str));

    char const *ptr = str;
    for (ptr = str; *ptr != '\0'; ptr++)
    {
        if (*ptr == symbol)
            return ptr;
    }
    return NULL;
}

/* Функция - аналог библиотечной функции strchr. Возвращает указатель на последнее вхождение символа в строке.
NULL, если символ не встретился*/
char const *my_strrchr(char const *str, int symbol)
{
    if (str == NULL || symbol > 255 || symbol < 0)
        return NULL;

    if (symbol == 0)
        return (char *)(str + strlen(str));

    size_t len = my_strlen(str);
    char const *ptr;
    for (ptr = str + len - 1; ptr >= str; ptr--)
    {
        if (*ptr == symbol)
            return ptr;
    }

    return NULL;
}
