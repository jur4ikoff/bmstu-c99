#ifndef CONST_H__
#define CONST_H__
#include <stdio.h>

#define ERR_OK 0
#define ERR_MEMORY_ALLOC 1

typedef double (*calc_squre_fn)(void *object);
typedef void (*set_fn_x)(void *object, double x);
typedef double (*set_fn_y)(void *object);

typedef struct _method_t_
{
    calc_squre_fn calc_squre;
    set_fn_x set_x;
    set_fn_y set_y;
} method_t;

#endif
