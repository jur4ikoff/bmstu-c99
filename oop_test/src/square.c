#include "square.h"
#include "const.h"
#include <stdio.h>
#include <stdlib.h>

int class_square_create(square_t **object, double side)
{
    square_t *object = malloc(sizeof(square_t));
    if (*object == NULL)
    {
        return ERR_MEMORY_ALLOC;
    }
    (*object)->side = side;
    (*object)->method.calc_squre_fn = calc_squre;

    return ERR_OK;
}

double calc_squre(void *object)
{
}
