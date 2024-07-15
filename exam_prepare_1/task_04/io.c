#include "io.h"

void output(int arg)
{
    if (arg == ERR_MAX_COUNT)
        printf("Error count lines");
    else if (arg == ERR_OVERFLOW)
        printf("String overflow");
    else if (arg == EMPTY_INPUT)
        printf("Empty input");
}
