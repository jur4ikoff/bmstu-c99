#include "constants.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

// Структура с данными, лист хранится внутри ноды, за счет того обеспечивается оптимизированное выделение памяти
typedef struct _data_t__
{
    int el;
    struct list_head list;
} data_t;

int main(void)
{
    int rc = ERR_OK;

    // Иниацилизируем голову списка
    LIST_HEAD(num_list);

    data_t *item = NULL;

    for (size_t i = 0; i < 10; i++)
    {
        item = malloc(sizeof(*item));
        if (item == NULL)
            return ERR_MEM_ALLOC;
            
        // Инициализация данных
        item->el = (int)i;
        // Нужно инициализировать ноду списка внутри элеента
        INIT_LIST_HEAD(&item->list);

        // Добавление в лист
        list_add(&item->list, &num_list);
    }

    //
    // Вывод списка на экран
    //
    struct list_head *iter;
    list_for_each(iter, &num_list)
    {
        item = list_entry(&iter, struct _data_t__, list);
        printf("[LIST] = %d\n", item->el);
    }
    return rc;
}
