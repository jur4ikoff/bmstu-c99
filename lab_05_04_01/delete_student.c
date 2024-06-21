#include "args_realization.h"
#include <unistd.h>
#define EPS 1e-6

int array_sum(int *sum, uint32_t *marks)
{
    int rc = ERR_OK;
    int read_count = 0;
    for (size_t i = 0; i < MAX_MARKS_LEN; i++)
    {
        if (marks[i])
        {
            *sum += marks[i];
            read_count++;
        }
    }
    if (read_count != MAX_MARKS_LEN)
        rc = ERR_WRONG_MARK;
    return rc;
}
// Считает средний балл всех студентов в файле
int calcuate_mean_in_file(FILE *file, double *mean, size_t count, size_t struct_size)
{
    int rc = ERR_OK;
    rewind(file);
    size_t read_count = 0;
    int sum = 0;
    for (size_t i = 0; i < count; i++)
    {
        struct students_struct student;
        if (fread(&student, struct_size, 1, file) != 1)
            return ERR_READ;
        read_count++;
        rc = array_sum(&sum, student.marks);
        if (rc != ERR_OK)
            return rc;
    }
    if (read_count != count)
        return ERR_READ;

    *mean = (double)sum / (count * 4);
    rewind(file);
    return rc;
}

int delete_struct_from_file(FILE *file, size_t pos, size_t *count)
{
    int rc = ERR_OK;
    if (*count <= 1)
        return ERR_EMPTY_OUTPUT;
    if (pos >= *count)
        return ERR_FILE;
    size_t struct_size = sizeof(struct students_struct);
    for (size_t i = pos; i < *count; i++)
    {
        fseek(file, (i + 1) * struct_size, SEEK_SET);

        struct students_struct student;
        memset(&student, 0, sizeof(student));
        fread(&student, struct_size, 1, file);
        fseek(file, i * struct_size, SEEK_SET);
        fwrite(&student, struct_size, 1, file);
    }

    // if (rc != ERR_OK)
    //     return ERR_FILE;
    fflush(file);
    ftruncate(fileno(file), (*count - 1) * struct_size);
    (*count)--;
    return rc;
}

// Главная функция для удаления студеsнтов, у которых средний балл меньше среднего балла всех студентов в файле
int delete_student_less_mean(const char *filename)
{
    int rc = ERR_OK;
    size_t size = 0, struct_size = sizeof(struct students_struct);
    double file_mean = 0;
    // Открываем для чтения и записи
    FILE *file = fopen(filename, "rb+");
    if (file == NULL)
        return ERR_FILE;
    rc = file_size(file, &size);
    if (rc != ERR_OK)
        return rc;
    size_t count = size / struct_size;
    // Получение среднего по всему файлу
    rc = calcuate_mean_in_file(file, &file_mean, count, struct_size);
    if (rc != ERR_OK)
        return rc;
    struct students_struct student;
    size_t i = 0;
    while (fread(&student, struct_size, 1, file) == 1)
    {
        double cur_mean = 0;
        cur_mean = (student.marks[0] + student.marks[1] + student.marks[2] + student.marks[3]) / 4.0;
        if (file_mean - cur_mean > EPS)
        {
            delete_struct_from_file(file, i, &count);
            fseek(file, i * struct_size, SEEK_SET);
        }
        else
            i++;
    }

    fclose(file);
    return rc;
}
