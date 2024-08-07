#ifndef STRING_H
#define STRING_H
#include "constants.h"

int separate_words(char words[][MAX_WORD_LEN], char *string, size_t *word_count);
void reverse(char words[][MAX_WORD_LEN], size_t word_count);

#endif