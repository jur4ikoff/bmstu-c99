#ifndef FILE_OPER_
#define FILE_OPER_
#include <stdio.h>

int file_elements_count(char *filename, size_t *count);
int file_write_int(char *filename, int *begin_arr, int *end_arr);

#endif
