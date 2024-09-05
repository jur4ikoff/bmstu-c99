#ifndef CONST_H
#define CONST_H
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "errors.h"

#define MAX_STRING 64
#define MAX_SIZE 10

struct Person
{
    char name[MAX_STRING];
    size_t height;
};

#endif
