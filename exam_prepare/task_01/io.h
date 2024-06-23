#ifndef IO_H
#define IO_H
#include "constants.h"
int input_string(char *string, size_t len);
int split_string(char words[][MAX_WORD_LEN + 1], char *string, size_t *count);
void proccesing_errors(int arg);
int solve(char words[][MAX_WORD_LEN + 1], size_t word_count);
void print_words(char words[][MAX_WORD_LEN + 1], size_t word_count);
#endif