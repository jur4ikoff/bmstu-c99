#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "io.h"

#ifndef SOLVE_H
#define SOLVE_H
int separate_words(char words[][MAX_WORD_LEN + 1], char *string, size_t *word_count);
void reverse_word(char words[][MAX_WORD_LEN + 1], size_t len);
void delete_repeat_letters(char arr[]);
void delete_words(char words[][MAX_WORD_LEN + 1], char word_to_delete[], size_t *word_count);
void solve(char words[][MAX_WORD_LEN + 1], char answer[MAX_STRING_LEN + 1], size_t word_count);
#endif
