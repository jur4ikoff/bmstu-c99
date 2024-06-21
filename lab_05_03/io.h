#ifndef IO_H
#define IO_H
#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "solve.h"
int import(const char *filename_txt, const char *filename_bin);
int export(const char *filename_bin, const char *filename_txt);
int proccessing_args(int argc, char **argv);
void processing_errors(int exitcode);
#endif
