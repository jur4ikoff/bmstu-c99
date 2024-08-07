#ifndef IO_H
#define IO_H
#include "constants.h"

int input_string(char *string);
void output(int arg);
int split_string(char words[][MAX_WORD_LEN], char *string, size_t *word_count);
void to_upper_in_brackets(char words[][MAX_WORD_LEN], size_t word_count);
#endif
