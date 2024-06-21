#ifndef SOLVE_H
#define SOLVE_H
#include <math.h>
#include "constants.h"
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

int fill_bin_file(FILE *file, size_t count);
int file_size(FILE *f, size_t *size);
int print_int_file(FILE *f);
int sort_int_file(FILE *f);
#endif
