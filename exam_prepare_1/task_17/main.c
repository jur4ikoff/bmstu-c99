#include "stdio.h"

int main(void)
{
    size_t a;
    if (scanf("%zu", &a) != 1)
        return 1;
    printf("%zu\n", a);
    return 0;
}
