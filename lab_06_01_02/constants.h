#ifndef CONST_H
#define CONST_H

#include "errors.h"
#include "includes.h"

#define MAX_STRING_LEN 25
#define MAX_PRODUCTS 15
#define EPS 10e-9

typedef struct
{
    char name[MAX_STRING_LEN];
    float weight;
    float volume;
} product_struct;
#endif
