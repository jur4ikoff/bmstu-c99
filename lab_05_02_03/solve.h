#include <stdio.h>
#include <string.h>
#include "constants.h"

#ifndef SOLVE_H
#define SOLVE_H
#include <math.h>
int calculate_sum(FILE *file, int *count, double *sum, double *qsum);
int calculate_dispersion(FILE *file, int *count, double *dispersion, double mean);
int check_rule_of_three_sigma(FILE *file, double mean, double sum, double qsum, size_t count);
#endif
