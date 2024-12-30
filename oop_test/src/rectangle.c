#include "rectangle.h"
#include "const.h"
#include <stdio.h>
#include <stdlib.h>

int class_rect_create(rectangle_t **object, double a, double b)
{
    *object = malloc(sizeof(rectangle_t));
    if ((*object) == NULL)
    {
        return ERR_MEMORY_ALLOC;
    }
    (*object)->a = a;
    (*object)->b = b;
    (*object)->method.calc_squre = calc_rectangle_square;

    return ERR_OK;
}

void class_rect_destroy(rectangle_t *object)
{
    free(object);
}

double calc_rectangle_square(void *object)
{
    rectangle_t *square = (rectangle_t *)object;
    return square->a * square->b;
}
