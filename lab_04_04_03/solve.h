#ifndef SOLVE_H
#define SOLVE_H
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "io.h"
#include <ctype.h>
bool clear_spaces(char string[], size_t *index);
bool extraxt_country_code(char string[], size_t *index);
bool extract_operator_code(char string[], size_t *index);
bool check_number(char string[], size_t *index);
#endif
