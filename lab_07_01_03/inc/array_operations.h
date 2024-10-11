#ifndef ARRAY_OPER_
#define ARRAY_OPER_
#include <stdio.h>

int create_array_from_file(char *filename, int **arr, size_t size);
void print_array(int *begin_arr, int *end_arr);
int compare(const void *elem1, const void *elem2);
int copy_array(int *begin_src, int *end_src, int **begin_dst, int **end_dst);
int key(const int *pbegin_source, const int *pend_source, int **pbegin_filtered_arr, int **pend_filtered_arr);
void my_sort(void *arr, size_t number, size_t width, int (*compare)(const void *, const void *));
void my_sort_test(void *arr, size_t number, size_t width, int (*compare)(const void *, const void *));
#endif
