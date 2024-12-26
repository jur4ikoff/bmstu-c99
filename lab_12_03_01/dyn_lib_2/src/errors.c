#include "errors.h"
#include <stdio.h>
#define OUT 1

// Функция для вывода ошибок на экран
void print_err_msg(int arg)
{
#if OUT
    if (arg == ERR_ARGS)
        printf("Ошибка в веденных аргументах\n");
    else if (arg == ERR_FILENAME)
        printf("Ошибка в имени файла\n");
    else if (arg == ERR_READ)
        printf("Ошибка при чтении файла\n");
    else if (arg == ERR_ALLOCATION)
        printf("Ошибка при выделении памяти\n");
    else if (arg == ERR_EMPTY_INPUT)
        printf("Ошибка, пустой ввод\n");
    else if (arg == ERR_POINTER)
        printf("Ошибка при передачи параметров\n");
    else if (arg == ERR_LONG_ARRAY)
        printf("Ошибка, массив переполнен\n");
    else if (arg == ERR_EMPTY_OUTPUT)
        printf("Ошибка, пустой вывод\n");
#else
    (void)arg;
#endif
}
