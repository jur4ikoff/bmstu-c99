#define _GNU_SOURCE

#include <stdio.h>
#include "students.h"
#include <stdlib.h>
#include "errors.h"
#include <string.h>
#include "constants.h"

int input_string(char **string, FILE *file)
{
    ssize_t read = 0;
    size_t len = 0;

    if ((read = getline(string, &len, file)) == -1)
        return ERR_STRING;

    char *newline = strchr(*string, '\n');
    if (!newline)
        return ERR_STRING;
    *newline = 0;

    if (strlen(*string) == 0)
        return ERR_STRING;

    return ERR_OK;
}

void print_student(void *data)
{
    student_t *student = (student_t *)data;
    printf("%s\n%d\n%s\n", student->second_name, student->year, student->group);
}

student_t *create_student(char *name, int year, char *group)
{
    student_t *student = NULL;
    student = malloc(sizeof(student_t));

    if (!student)
        return student;

    student->second_name = strdup(name);
    student->year = year;
    student->group = strdup(group);
    return student;
}
