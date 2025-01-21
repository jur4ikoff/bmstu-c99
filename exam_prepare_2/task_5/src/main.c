/*
Даны длина и ширина прямоугольников, вещественные. Вводятся в конец списка. Из них квадраты поместить в новый список. Вывести сначала все прямоугольники, потом все квадраты.
Вывод строкой "%f %f\n"
В случае ошибки по памяти или если получили пустой вывод - выводим "ERROR\n"
Ввод до первой ошибки

Ввод до первой ошибки
5 7
5 5
20 3
4 4

5 7
20 3
5 5
4 4
*/

#include "constants.h"
#include "list.h"
#include <stdio.h>

void print_err_msg(int arg)
{
    if (arg == ERR_EMPTY)
        printf("ERR_EMPTY\n");
    else if (arg == ERR_MEMORY)
        printf("ERR_MEMORY\n");
}

int main(void)
{
    int rc = ERR_OK;
    size_t count = 0;
    node_t *head = NULL;
    input_to_list(&head, &count);
    if (count < 1)
    {
        print_err_msg(ERR_EMPTY);
        free_list(head);
        return ERR_EMPTY;
    }
    node_t *squares = NULL;
    copy_squares(&squares, head);
    
    print_only_rect(head);
    print_list(squares);
    free_list(head);
    return rc;
}
