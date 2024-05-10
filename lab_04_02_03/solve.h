#ifndef SOLVE_H
#define SOLVE_H

#include <string.h>
#include <stdbool.h>
#include "io.h"
#include "constants.h"

int separate_words(char words[][MAX_WORD_LEN + 1], char *string, size_t *word_count);
int make_words_unique(char matx[][MAX_WORD_LEN + 1], size_t len);
#endif
