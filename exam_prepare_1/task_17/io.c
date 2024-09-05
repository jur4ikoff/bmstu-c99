#include "io.h"

void output(int arg)
{
    switch (arg)
    {
    case ERR_INVALID_SIZE:
        printf("Invalid size\n");
        break;
    case ERR_EMPYTY_INPUT:
        printf("Empty input\n");
        break;
    case ERR_OUTPUT:
        printf("Error in output\n");
        break;
    case ERR_INPUT:
        printf("Input Error\n");
        break;
        /*case ERR_INVALID_SIZE:
            printf("Invalid size\n");
            break;*/
    }
}