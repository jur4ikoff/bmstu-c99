#include "constants.h"
#include <stdio.h>

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define SCALE(x) ((x) * 10)
#define PRINT_INT(n) printf(#n " = %d\n", (n))
#define PRINT(s, ...) printf(s, __VA_ARGS__)

#define PRICOL(x)         \
    if (x > 5)            \
    {                     \
        PRINT_INT(x + 1); \
    }                     \

#define CR_INT(s) int i##s

int main(void)
{
    int rc = ERR_OK;
    int a = MAX(4, 5);
    a = SCALE(a + 1);
    PRINT_INT(a);
    PRICOL(a);
    PRINT("test %d\n", 5);

    CR_INT(1);
    i1 = 1;
    PRINT_INT(i1);
    return rc;
}
