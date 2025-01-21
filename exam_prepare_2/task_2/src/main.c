/*
Задача 4ой группы

Реализовать структуру данных Очередь, основанную на линейном односвязном списке
Считать с клавиатуры натуральное число, если оно не считалось, напечатать Input error
Если оно не натуральное, печатать Range error. С помощью очереди распечатать число в инвертированном виде

Вход
123

Выход
321

Вход
lom
Выход
Input error

При ошибке выделения памяти Memory error
*/

#include "constants.h"
#include "queue.h"
#include <stdio.h>

#define PRINT_INT(n) (printf("%d\n", (n)))

err_t input_number(int *number)
{
    if (scanf("%d", number) != 1)
        return ERR_NUMBER;

    if (*number < 1)
        return ERR_RANGE;

    return ERR_OK;
}

void print_err_msg(int arg)
{
    if (arg == ERR_NUMBER)
        printf("Err Number\n");
    else if (arg == ERR_RANGE)
        printf("Err Range\n");
    else if (arg == ERR_MEM)
        printf("Err Mem\n");
    else if (arg == ERR_ARG)
        printf("Err Args\n");
}

err_t main(void)
{
    int rc = ERR_OK;
    int number;
    if ((rc = input_number(&number)) != ERR_OK)
    {
        print_err_msg(rc);
        return rc;
    }

    node_t *head = NULL;
    convert_int_to_list(&head, number);
    print_queue(head);
    return rc;
}
