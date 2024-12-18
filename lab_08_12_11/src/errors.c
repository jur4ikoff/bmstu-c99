#include "errors.h"
#include <stdio.h>

// Функция для вывода сообщение об ошибки
void print_err_message(int arg)
{
#if OUTPUT
    if (arg == ERR_ARG_COUNT)
    {
        printf("Ошибка, в количестве аргументов\n");
    }
    else if (arg == ERR_ARG_LENGTH)
        printf("Ошибка, введенный аргумент слишком длинный\n");
    else if (arg == ERR_MEMORY_ALLOCATION)
        printf("Ошибка при выделении памяти\n");
    else if (arg == ERR_FILENAME)
        printf("Ошибка, не удалось открыть файл\n");
    else if (arg == ERR_WRONG_MATRIX_SIZE)
        printf("Ошибка, неверно введен размер матрицы\n");
    else if (arg == ERR_MATRIX_HAVE_NOT_EQ_SIZE)
        printf("Ошибка, матрицы разного размера\n");
    else if (arg == ERR_EMPTY_MATRIX)
        printf("Ошибка, матрица пустая\n");
    else if (arg == ERR_WRITE)
        printf("Ошибка во время записи\n");
    else if (arg == ERR_MATRIX_CANNOT_MULT)
        printf("Ошибка, матрицы нельзя пермножить, количество столбцов в первой матрице должно быть равно количеству строк во второй\n");
    else if (arg == ERR_WRONG_MATRIX_ELEMENT)
        printf("Неверный элемент матрицы\n");
    else if (arg == ERR_WRONG_ACTION)
        printf("Неверное действие\n");
    else if (arg == ERR_NOT_SQUARE_MATRIX)
        printf("Матрица должна быть квадратная\n");

#else
    (void)arg;
#endif
}
