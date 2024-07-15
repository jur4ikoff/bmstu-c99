#include "constants.h"
#include "errors.h"
#include "io.h"
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
    int count;
    if (scanf("%d", &count) != 1)
    {
        rc = ERR_MAX_COUNT;
        output(rc);
        return rc;
    }
    printf("%d", count);
    return rc;
}
