#include <stdio.h>

#ifndef IO_H
#define IO_H
#define N 10
#define M 10
#define SUCCESS_OUTPUT 0
#define WRONG_INPUT 1
#define WRONG_ARRAY_LEN 2
#define EMPTY_OUTPUT 3
#define WRONG_DIGIT_INPUT 4
 
int input_len(size_t *array_len);
int input_digit(int *digit);
int input_matx(int matx[N][M], size_t n, size_t m);
int print_matx(int matx[N][M], size_t n, size_t m);

#endif
