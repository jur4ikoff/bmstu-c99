#ifndef CHECK_MULT_H__
#define CHECK_MULT_H__
#include <check.h>

Suite *get_mult_suite(void);
int compare_data(const void *a, const void *b);
int compare_lists(const void *first, const void *second);

#endif
