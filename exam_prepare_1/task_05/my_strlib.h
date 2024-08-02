#ifndef MY_STR_H
#define MY_STR_H
#include "constants.h"
#include "errors.h"

int separate_words(char words[][MAX_WORD_LEN], char *string, size_t *word_count);
int check_is_number(char *string);
int sum_only_int(char words[][MAX_WORD_LEN], size_t word_count, int *sum);
// int to_int(char *string, int *number)
#endif
