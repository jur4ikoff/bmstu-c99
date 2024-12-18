#include "task.h"
#include "auto.h"
#include "errors.h"
#include "linked_list.h"
#include <stdlib.h>

int string_to_int(char *string, int *number)
{
    int rc = ERR_OK;
    char *endptr;
    *number = strtoll(string, &endptr, 10); // 10 - основание системы счисления (десятичная)

    // Проверяем на ошибки
    if (*endptr != '\0')
        return ERR_YEAR;

    return rc;
}

node_t *filter(node_t **head, int year, int price)
{
    if (head == NULL || *head == NULL)
        return NULL;

    node_t *new_head = NULL;

    node_t *cur = *head;
    while (cur)
    {
        auto_t *data = cur->data;
        if (data->year > year && (int)data->price < price)
        {
            add_to_list(&new_head, data);
        }
        cur = cur->next;
    }
    return new_head;
}
