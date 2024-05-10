#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#ifndef MYSTRLIB_H
#define MYSTRLIB_H
#define STRING_LEN 16
#define WORD_LEN 16
#define SUCCESS_OUTPUT 0
#define ERROR 1

char const *my_strpbrk(char const *str, char const *find);
size_t my_strlen(char const *string);
size_t my_strspn(const char *str, const char *symbols);
size_t my_strcspn(char const *str, char const *symbols);
char const *my_strchr(char const *str, int symbol);
char const *my_strrchr(char const *str, int symbol);

#endif
