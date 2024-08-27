#ifndef IO_H
#define IO_H
#include "constants.h"
#include "math.h"
int input_from_file(FILE *filename, int number_array[], size_t *word_count);
void output(int arg);
void find_closest(int numbers[], size_t count, double average);
double calculate_average(int numbers[], size_t count);
#endif
