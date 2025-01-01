#ifndef CIRCLE_H__
#define CIRCLE_H__
#include "const.h"

typedef struct _struct_square_t
{
    method_t method;
    double side;
} square_t;

int class_square_create(square_t **object, double side);
void class_square_destroy(square_t *object);
#endif
