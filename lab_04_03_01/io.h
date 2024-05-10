#include <stdio.h>
#include <string.h>
#include "constants.h"

#ifndef IO_H
#define IO_H

int string_input(char *str, size_t max_len);
void print_line(char matx[MAX_WORDS][MAX_WORD_LEN + 1], size_t n);
void processing_errors(int exitcode);
#endif
