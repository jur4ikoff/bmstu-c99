#ifndef RECTANGLE_H__
#define RECTANGLE_H__
#include "const.h"

typedef struct _struct_rect_t
{
    method_t method;
    double a, b;
} rectangle_t;

int class_rect_create(rectangle_t **object, double, double);
void class_rect_destroy(rectangle_t *object);
#endif
