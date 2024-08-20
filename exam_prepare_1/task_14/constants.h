#ifndef CONST_H
#define CONST_H

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define MAX_NAME 10
#define MAX_POINTS 10

#define ERR_OK 0
#define ERR_NAME 1
#define ERR_NUMBER 2
#define ERR_EMPTY 3
#define ERR_SIZE 4

typedef struct
{
    char name[MAX_NAME + 1];
    double x;
    double y;
}Point;
#endif
