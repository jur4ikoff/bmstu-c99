#ifndef SOLVE_H
#define SOLVE_H
#include "const.h"


void find_mean(double *mean, struct Person persons[], size_t count);
void run(struct Person persons[], size_t *count, double mean);
#endif
