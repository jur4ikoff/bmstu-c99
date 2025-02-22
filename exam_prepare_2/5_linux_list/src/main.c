#include "constants.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#define PRINT_INT(name, d) ((printf("[%s] = %d\n", #name, (d))))

// Структура с данными, лист хранится внутри ноды, за счет того обеспечивается оптимизированное выделение памяти
typedef struct _data_type_
{
    int el;
    struct list_head list;
} data_t;

int main(void)
{
    int rc = ERR_OK;

    // Иниацилизируем голову списка
    LIST_HEAD(num_list);

    // Добавление элементов в список
    data_t *item = NULL;
    for (int i = 0; i < 10; i++)
    {
        item = malloc(sizeof(*item));
        if (item == NULL)
            return ERR_MEM_ALLOC;

        // Инициализация данных
        item->el = i;
        // Нужно инициализировать ноду списка внутри элеента
        INIT_LIST_HEAD(&item->list);

        // Добавление в лист
        list_add(&item->list, &num_list);
    }

    //
    // Вывод списка на экран
    //
    struct list_head *iter, *iter_safe;
    list_for_each(iter, &num_list)
    {
        item = list_entry(iter, struct _data_type_, list);
        PRINT_INT(LIST, item->el);
    }

    list_for_each_entry(item, &num_list, list)
    {
        PRINT_INT(LIST2, item->el);
    }

    list_for_each_safe(iter, iter_safe, &num_list)
    {
        item = list_entry(iter, data_t, list);
        list_del(iter);
        free(item);
    }

    return rc;
}
