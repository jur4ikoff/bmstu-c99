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
    run_strspn("Hello world", "Hello world", &count);
    run_strcspn("Hello world", "Hello world", &count);
    run_strchr("Hello world", 'g', &count);
    run_strrchr("Hello world", 'g', &count);
    // Вывод
    printf("Result: %d\n", count);
    return SUCCESS_OUTPUT;
}
