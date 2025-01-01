#include "square.h"
#include "const.h"
#include <stdio.h>
#include <stdlib.h>

double calc_square_square(void *object);

int class_square_create(square_t **object, double side)
{
    *object = malloc(sizeof(square_t));
    if (*object == NULL)
    {
        return ERR_MEMORY_ALLOC;
    }
    (*object)->side = side;
    (*object)->method.calc_squre = calc_square_square;

    return ERR_OK;
}

void class_square_destroy(square_t *object)
{
    free(object);
}


double calc_square_square(void *object)
{
    square_t *square = (square_t *)object;
    return square->side * square->side;
}
