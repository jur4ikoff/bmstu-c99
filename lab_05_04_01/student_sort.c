#include "args_realization.h"

int compare_students(struct students_struct *student1, struct students_struct *student2)
{
    int surname_compare = strcmp(student1->surname, student2->surname);
    // printf("%d\n", surname_compare);
    if (surname_compare != 0)
        return surname_compare;
    else
        return strcmp(student1->name, student2->name);
}

void swap_students(FILE *file, size_t pos1, size_t pos2)
{
    struct students_struct student1, student2;
    size_t struct_size = sizeof(struct students_struct);
    fseek(file, pos1, SEEK_SET);
    fread(&student1, struct_size, 1, file);

    fseek(file, pos2, SEEK_SET);
    fread(&student2, struct_size, 1, file);

    fseek(file, pos1, SEEK_SET);
    fwrite(&student2, struct_size, 1, file);

    fseek(file, pos2, SEEK_SET);
    fwrite(&student1, struct_size, 1, file);
}

int sort_students_in_file(const char *filename)
{
    int rc = ERR_OK;
    FILE *file = fopen(filename, "rb+");
    if (file == NULL)
        return ERR_FILE;

    size_t size = 0, struct_size = sizeof(struct students_struct), count = 0;
    rc = file_size(file, &size);
    if (rc != ERR_OK)
        return rc;
    if (size % struct_size != 0)
        return ERR_FILE;

    count = size / struct_size;
    for (size_t i = 0; i < count; i++)
    {
        for (size_t j = 0; j < count - 1; j++)
        {
            struct students_struct student1, student2;
            fseek(file, j * struct_size, SEEK_SET);
            fread(&student1, struct_size, 1, file);

            fseek(file, (j + 1) * struct_size, SEEK_SET);
            fread(&student2, struct_size, 1, file);

            if (compare_students(&student1, &student2) > 0)
                swap_students(file, j * struct_size, (j + 1) * struct_size);
        }
    }
    print_bin_file(file);
    fclose(file);
    return rc;
}
