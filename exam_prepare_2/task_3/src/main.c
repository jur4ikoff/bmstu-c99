/*
Условие

Считать от пользователя целые числа до первого нуля, добавить в конец односвязанного списка.
Далее удалить из списка все элементы, которые больше предыдущего и следующего.
Вывести итоговый список или Empty list, если пустой.
При ошибке выделения памяти вывести Memory error.
При ошибке ввода вывести Input error.

Комментарии
▶️Задача должна решаться за один проход по списку.
▶️Не выводить не угодные элементы нельзя.
▶️Новый список создавать нельзя.

Пример
4 2 5 8 3 9 1 0
4 2 5 3 1
*/

#include "constants.h"
#include "list.h"
#include <stdio.h>

void print_error_message(int arg)
{
    if (arg == ERR_MEMORY)
        printf("Memory error\n");
    else if (arg == ERR_EMPTY)
        printf("Empty list\n");
    else if (arg == ERR_INPUT)
        printf("Input error\n");
}

static int input_number(int *number)
{
    if (scanf("%d", number) != 1)
        return ERR_INPUT;
    
    return ERR_OK;
}

static int input_numbers_array(int *arr, size_t *index)
{
    int number = 0;
    err_t rc = ERR_OK;
    *index = 0;
    while ((rc = input_number(&number)) == ERR_OK)
    {
        if (number == 0)
            return ERR_OK;

        arr[(*index)++] = number;
    }
    return rc;
}

err_t main(void)
{
    err_t rc = ERR_OK;
    int numbers[MAX_NUMBERS];
    size_t count = 0;
    if ((rc = input_numbers_array(numbers, &count)) != ERR_OK)
    {
        print_error_message(rc);
        return rc;
    }

    if (count == 0)
    {
        print_error_message(ERR_EMPTY);
        return ERR_EMPTY;
    }

    node_t *head = NULL;
    convert_arr_to_list(&head, numbers, count);
    delete_by_task(head);
    print_list(head);
    free_list(head);
    return rc;
}
