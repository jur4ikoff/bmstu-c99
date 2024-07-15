#ifndef SOLVE_H
#define SOLVE_H
#include "constants.h"
#include <ctype.h>
int split_words(char words[][MAX_WORD_LEN + 1], char *string, size_t *word_count);
int solve(char words[][MAX_WORD_LEN + 1], size_t count);
#endif