#ifndef SOLVE_H
#define SOLVE_H
#include "constants.h"
#include "io.h"
#define SEPARATORS " ,.:;"
int solve(char words[][MAX_WORD_LEN + 1], size_t count);
int split_words(char words[][MAX_WORD_LEN + 1], char *string, size_t *count);
#endif