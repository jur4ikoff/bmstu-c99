#include "mystrlib.h"

// Функция запуска и сравнения функции strpbrk
void run_strpbrk(char *msg1, char *msg2, int *count)
{
    char *a = strpbrk(msg1, msg2);
    char *b = (char *)my_strpbrk(msg1, msg2);
    if (a != NULL && b != NULL)
    {
        if (strcmp(a, b) != 0)
        {
            (*count)++;
        }
    }
    else if (a != b)
        (*count)++;
}

// Функция запуска и сравнения функции strspn
void run_strspn(char *msg1, char *msg2, int *count)
{
    size_t a = strspn(msg1, msg2);
    size_t b = my_strspn(msg1, msg2);

    if (a != b)
    {
        (*count)++;
    }
}

// Функция запуска и сравнения функции strcspn
void run_strcspn(char *msg1, char *msg2, int *count)
{
    size_t a = strcspn(msg1, msg2);
    size_t b = my_strcspn(msg1, msg2);
    if (a != b)
    {
        (*count)++;
    }
}

// Функция запуска и сравнения функции strchr
void run_strchr(char const *string, int symbol, int *count)
{
    char const *a = strchr(string, symbol);
    char const *b = my_strchr(string, symbol);

    if (a != NULL && b != NULL)
    {
        if (strcmp(a, b) != 0)
        {
            (*count)++;
        }
    }
    else if (a != b)
        (*count)++;
}

// Функция запуска и сравнения функции strrchr
void run_strrchr(char const *string, int symbol, int *count)
{
    char const *a = strrchr(string, symbol);
    char const *b = my_strrchr(string, symbol);
    if (a != NULL && b != NULL)
    {
        if (strcmp(a, b) != 0)
        {
            (*count)++;
        }
    }
    else if (a != b)
        (*count)++;
}

int main(void)
{
    int count = 0;
    // Последовательный запуск функций сравнения
    run_strpbrk("Hello World", "e", &count);
    run_strpbrk("Hello World", "H", &count);
    run_strpbrk("Hello World", "d", &count);
    run_strpbrk("Hello World", "Hd", &count);
    run_strpbrk("Hello World", "dH", &count);
    run_strpbrk("Hello World", " ", &count);
    run_strpbrk("Hello World", "g", &count);
    run_strpbrk("Hello World", "Hello World", &count);
    run_strpbrk("", "Hello World", &count);

    run_strspn("Hello World", "H", &count);
    run_strspn("Hello World", "d", &count);
    run_strspn("Hello World", "He", &count);
    run_strspn("Hello World", "eH", &count);
    run_strspn("Hello World", "g", &count);
    run_strspn("Hello World", "Hello World", &count);
    run_strspn("Hello World", "", &count);
    run_strspn("", "Hello World", &count);

    run_strcspn("Hello World", "H", &count);
    run_strcspn("Hello World", "d", &count);
    run_strcspn("Hello World", "oW", &count);
    run_strcspn("Hello World", "ga", &count);
    run_strcspn("Hello World", "Hello World", &count);
    run_strcspn("Hello World", "", &count);
    run_strcspn("", "Hello World", &count);

    run_strchr("Hello world", 'H', &count);
    run_strchr("Hello world", 'r', &count);
    run_strchr("Hello world", 'l', &count);
    run_strchr("Hello world", 'd', &count);
    run_strchr("Hello world", ' ', &count);
    run_strchr("Hello world", 'g', &count);
    run_strchr("", 'g', &count);

    run_strrchr("Hello world", 'H', &count);
    run_strrchr("Hello world", 'r', &count);
    run_strrchr("Hello world", 'd', &count);
    run_strrchr("Hello world", 'l', &count);
    run_strrchr("Hello world", ' ', &count);
    run_strrchr("Hello world", 'g', &count);
    run_strrchr("", 'g', &count);
    // Вывод
    printf("Result: %d\n", count);
    return SUCCESS_OUTPUT;
}
