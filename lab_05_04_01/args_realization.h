#ifndef SOLVE_H
#define SOLVE_H
#include <math.h>
#include "io.h"
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include "constants.h"
#include "inttypes.h"

struct students_struct
{
    char surname[MAX_SURNAME_LEN + 1];
    char name[MAX_NAME_LEN + 1];
    uint32_t marks[MAX_MARKS_LEN];
};

int sort_students_in_file(const char *filename);
int delete_student_less_mean(const char *filename);
void swap_students(FILE *file, size_t pos1, size_t pos2);
#endif
