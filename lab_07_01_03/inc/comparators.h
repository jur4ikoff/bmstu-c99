#ifndef COMPARATORS_H_
#define COMPARATORS_H_
#define ERR_NOT_EQ -1
#include <stdio.h>

int int_compare(const void *a, const void *b);
int int_arr_compare(int first_arr[], int second_arr[], size_t count);
int char_compare(const void *a, const void *b);
int double_compare(const void *a, const void *b);
#endif
