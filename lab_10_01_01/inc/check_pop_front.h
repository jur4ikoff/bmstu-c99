#ifndef CHECK_POP_H__
#define CHECK_POP_H__
#include <check.h>

int auto_t_comparator(void *data, char *name, int year, long long price);
int compare_data(const void *first, const void *second);
int compare_lists(const void *first, const void *second);

Suite *get_pop_front_suite(void);

#endif
