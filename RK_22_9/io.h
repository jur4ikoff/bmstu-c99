#ifndef IO_H
#define IO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"

void processing_errors(int n);
int input_string(char *str, size_t max_len, char *msg);
int input_len(size_t *array_len);

#endif
