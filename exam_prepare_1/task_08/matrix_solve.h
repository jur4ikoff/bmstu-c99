#ifndef MATRIX_H
#define MATRIX_H
void find_max_even(int matrix[][MAX_SIZE], int n, int m, int *column, int *string);
void find_min_odd(int matrix[][MAX_SIZE], int n, int m, int *column, int *string);
void swap_strings(int matrix[][MAX_SIZE], int m, int index1, int index2);
void swap_columns(int matrix[][MAX_SIZE], int n, int index1, int index2);
#endif