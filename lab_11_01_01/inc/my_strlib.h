#ifndef MY_STRLIB_H__
#define MY_STRLIB_H__

#include <stdio.h>
#define BASE 10

void my_strcat(char *dst, const char *src, size_t *count, const size_t max);
size_t integer_len(long long num);
char *integer_to_string(long long num, size_t width, size_t is_sign, size_t align);
int my_strlen(char *string);
char *align_string(char *src, size_t width, int align);
#endif
