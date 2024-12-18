#ifndef CHECK_ADD_H__
#define CHECK_ADD_H__
#include "check.h"
#include "matrix.h"
#define EPS 10e-7

Suite *get_add_suite(void);
int compare_matrix(matrix_t matrix_1, matrix_t matrix_2);
#endif
