/*
Задача:
Даны слова или словосочетания, разделенные символом начала новой строки.
Окончанием ввода является ввод «END».
Регистр имеет значение.

Слова и словосочетания добавляются в конец (!) списка.
Запрещено использовать функции не из стандарта с99. Таких как getline, strdup и т.д.
Гарантируется, что слово или словосочетание не длиннее 63 символов.
Все строки, кроме буфера должны выделяться динамически.
Если ошибка ввода, вывести “Input error\n”
Если ошибка памяти, вывести “Memory error\n”

Результат вывести в виде одной строки, соединяющей все слова и словосочетания через пробел строкой форматирования “‘%s’\n”.
После последнего слова или словосочетания пробел не ставится.

Пример:
in:
I
read
Red book
END
out:
‘I read Red book’
*/

#include "constants.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define END_INPUT -1

void print_err_msg(int arg)
{
    switch (arg)
    {
        case ERR_INPUT:
            printf("ERR_INPUT\n");
            break;
        case ERR_MEMORY_AlLOCATION:
            printf("ERR_MEM\n");
            break;
    }
}

int input_string(char **string)
{
    char buffer[MAX_STRING_LEN];

    if (!fgets(buffer, MAX_STRING_LEN - 1, stdin))
    {
        return ERR_INPUT;
    }

    char *newline = strchr(buffer, '\n');
    if (!newline)
    {
        return ERR_INPUT;
    }
    *newline = 0;

    if (strcmp(buffer, "END") == 0)
    {
        return END_INPUT;
    }
    
    *string = malloc(sizeof(char) * (strlen(buffer) + 1));
    if (*string == NULL)
    {
        return ERR_MEMORY_AlLOCATION;
    }

    for (size_t i = 0; i < strlen(buffer); i++)
    {
        (*string)[i] = buffer[i];
    }
    (*string)[strlen(buffer)] = 0;
    return ERR_OK;
}

int input_to_list(node_t **head)
{
    int rc = ERR_OK;
    if (head == NULL)
    {
        return ERR_ARG;
    }

    char *string = NULL;
    while ((rc = input_string(&string)) == ERR_OK)
    {
        if ((rc = add_list(head, string)) != ERR_OK)
        {
            return rc;
        }
    }

    if (rc == END_INPUT)
        return ERR_OK;
    else
        return rc;
}

int main(void)
{
    int rc = ERR_OK;
    node_t *head = NULL;

    if ((rc = input_to_list(&head)) != ERR_OK)
    {
        print_err_msg(rc);
        free_list(head);
        return rc;
    }

    // print_list(head);
    size_t len = len_string_in_list(head);

    char *output = malloc(sizeof(char) * (len + 1));
    if (output == NULL)
    {
        rc = ERR_MEMORY_AlLOCATION;
        print_err_msg(rc);
        free_list(head);
        return rc;
    }

    merge_list(head, output);
    printf("%s\n", output);

    free(output);
    free_list(head);
    return rc;
}
