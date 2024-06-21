#ifndef IO_H
#define IO_H
#include "inttypes.h"
#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "args_realization.h"
void processing_errors(int exitcode);
int string_input(char *str, size_t max_len, FILE *filename);
int processing_args(int argc, char **argv);
int file_size(FILE *f, size_t *size);
int import(const char *filename_txt, const char *filename_bin);
int export(const char *filename_bin, const char *filename_txt);
int check_string(const char *string);
#endif
