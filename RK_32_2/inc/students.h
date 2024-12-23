#ifndef STUDENTS_H__
#define STUDENTS_H__

typedef struct student_t_
{
    char *second_name;
    char *group;
    int year;
} student_t;

void print_student(void *data);
student_t *create_student(char *name, int year, char *group);
int input_string(char **string, FILE *file);
#endif
