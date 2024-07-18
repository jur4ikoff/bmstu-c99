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

    if ((rc = input_products_to_struct(count)) != ERR_OK)
    {
        output(rc);
        return rc;
    }

    return rc;
}
