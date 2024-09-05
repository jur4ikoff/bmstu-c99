#ifndef IO_H
#define IO_H
#include "const.h"

int input_size(size_t *count);
int input_string(char *string);
void output(int arg);
int input_to_struct(size_t count, struct Person persons[]);
void print_struct_array(struct Person persons[], size_t count);
#endif
