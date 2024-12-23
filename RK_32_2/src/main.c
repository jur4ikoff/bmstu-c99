#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "list.h"
#include "errors.h"
#include "students.h"
#include <stdlib.h>

void print_error_message(int arg)
{
    if (arg == ERR_ARGS)
        printf("Ошибка в аргументах\n");
    else if (arg == ERR_HEAD)
        printf("Ошибка в функции\n");
    else if (arg == ERR_MEMORY_ALLOCATION)
        printf("Ошибка выделения памяти\n");
    else if (arg == ERR_INPUT)
        printf("Ошибка ввода\n");
    else if (arg == ERR_FILE)
        printf("Неверный файл\n");
    else if (arg == ERR_STRING)
        printf("Неверно введена строка\n");
    else if (arg == ERR_STRUCTS_OVERFLOW)
        printf("Переполнение списка. Максимальное количество элементов\n");
}

int main(int argc, char **argv)
{
    int rc = ERR_OK;
    if (argc != NEED_ARG_COUNT)
    {
        print_error_message(ERR_ARGS);
        return ERR_ARGS;
    }

    node_t *head = NULL;
    FILE *file = fopen(argv[2], "r");
    if (file == NULL)
    {
        free_list(head);
        return ERR_FILE;
    }

    if ((rc = read_list(&head, file)) != ERR_OK)
    {
        fclose(file);
        print_error_message(rc);
        free_list(head);
        return rc;
    }
    fclose(file);
    if (strcmp(argv[1], "list") == 0)
    {
        apply_list(head, print_student);
    }
    else if (strcmp(argv[1], "rd") == 0)
    {
        remove_duplicates(&head);
        apply_list(head, print_student);
    }
    else
    {
        rc = ERR_ARGS;
        print_error_message(rc);
        free_list(head);
        return rc;
    }
    free_list(head);
    return rc;
}
