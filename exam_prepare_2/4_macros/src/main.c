#include "constants.h"
#include <stdio.h>

#define MAX(x, y) ((x) > (y) ? (x) : (y))

#define PRINT_INT(n) printf(#n " = %d\n", (n))

int main(void)
{
    int rc = ERR_OK;
    int a = MAX(4, 5);
    PRINT_INT(a);
    return rc;
}
