#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX_STRING_LEN 256
#define MAX_WORD_LEN MAX_STRING_LEN / 2
#define MAX_WORDS MAX_STRING_LEN / 2
#define SEPARATORS " .:;,"
#define ERR_OK 0
#define ERR_INPUT 1
#define ERR_STRING_OVERFLOW 2
#define ERR_LEN 3
#define ERR_MAX_MIN 4
#endif
