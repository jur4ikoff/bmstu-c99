#ifndef SOLVE_H
#define SOLVE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "ctype.h"

struct subscriber_struct
{
    char surname[MAX_SURNAME_LEN + 1];
    char phone_number[MAX_STRING_LEN - MAX_SURNAME_LEN + 1];
};
int split_string(char *line, struct subscriber_struct *subscriber);
int read_struct_from_file(char *filename, struct subscriber_struct *subscribers, size_t *count);
#endif
