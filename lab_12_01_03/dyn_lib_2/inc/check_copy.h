#ifndef CHECK_COPY_H_
#define CHECK_COPY_H_
#include "check.h"
#include <stdio.h>

Suite *get_copy_suite(void);

typedef int (*copy_array_fn)(int *begin_src, int *end_src, int *begin_dst, int **end_dst);
typedef int (*key_fn)(const int *pbegin_source, const int *pend_source, int *pbegin_filter, int **pend_filter);
typedef void (*mysort_fn)(void *arr, size_t number, size_t width, int (*compare)(const void *, const void *));

typedef struct test_func_load_type
{
    copy_array_fn copy_array;
    key_fn key;
    mysort_fn mysort;
} test_func_load_t;

int load_test_functions_from_dyn_lib(void *handle, test_func_load_t *load);

#endif
