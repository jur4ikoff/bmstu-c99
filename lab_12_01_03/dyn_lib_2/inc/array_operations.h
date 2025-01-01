#ifndef ARRAY_OPER_
#define ARRAY_OPER_
#include <stdio.h>

int create_array_from_file(char *filename, int **arr, size_t size);
void print_array(int *begin_arr, int *end_arr);
int copy_array(int *begin_src, int *end_src, int *begin_dst, int **end_dst);
int key(const int *pbegin_source, const int *pend_source, int *pbegin_filter, int **pend_filter);
const int *find_last_neg_el(const int *pbegin, const int *pend);
void mysort(void *arr, size_t number, size_t width, int (*compare)(const void *, const void *));
#endif
