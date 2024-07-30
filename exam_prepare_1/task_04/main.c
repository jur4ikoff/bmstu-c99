#include "constants.h"
#include "errors.h"
#include "io.h"
#include "solve.h"

/*Задача с экзамена 1. Вычислить структуру с ценой близкой к средней
3
Banana
4
Mango
4
Bread
5
Mango*/

int main(void)
{
    int rc = ERR_OK;
    size_t count;
    if ((rc = input_count(&count)) != ERR_OK)
    {
        output(rc);
        return rc;
    }
    fgetc(stdin);

    struct product products[MAX_COUNT];
    if ((rc = input_products_to_struct(count, products)) != ERR_OK)
    {
        output(rc);
        return rc;
    }

    float mean = get_mean(products, count);
    size_t index = 0;
    index = get_index_min_diff(products, count, mean);
    printf("%s\n%d\n", products[index].name, products[index].price);
    return rc;
}
