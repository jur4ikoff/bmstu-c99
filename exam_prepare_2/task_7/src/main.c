// Написать СД лист
#include <stdio.h>
#include "list.h"
#include "constants.h"

int main(void)
{
    int rc = ERR_OK;
    node_t *list = NULL;

    append(&list, 1);
    print_list(list);
    append(&list, 10);
    print_list(list);
    append(&list, 15);
    print_list(list);
    free_list(list);

    return rc;
}
