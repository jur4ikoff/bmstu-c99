#ifndef CONST_H
#define CONST_H
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"

#define ERR_OK 0
#define ERR_STRING_INPUT 1
#define ERR_OVERFLOW 2
#define ERR_INPUT 3
#define ERR_EMPTY 4

#define MAX_POINTS 100
#define MAX_NAME_LEN 20
typedef struct
{
    char name[MAX_NAME_LEN + 1];
    double x, y;
} Point;

#endif
