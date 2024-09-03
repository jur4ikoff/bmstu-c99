#include "io.h"

int string_input(char *str, size_t max_len, FILE *filename)
{
    int rc = ERR_OK;
    if (!fgets(str, max_len, filename))
        return ERR_WRONG_INPUT;
    char *newline = strchr(str, '\n');
    if (newline)
        *newline = '\0';
    else
        rc = ERR_STRING_OWERFLOW;
    return rc;
}

int processing_args(int argc, char **argv)
{
    int rc = ERR_OK;
    if (argc < 3)
        return ERR_UNKNOWN_ARGUMENTS;

    if (strcmp(argv[1], "import") == 0)
    {
        if (argc != 4)
        {
            processing_errors(ERR_UNKNOWN_ARGUMENTS);
            return ERR_UNKNOWN_ARGUMENTS;
        }
        rc = import(argv[2], argv[3]);
    }
    else if (strcmp(argv[1], "export") == 0)
    {
        if (argc != 4)
        {
            processing_errors(ERR_UNKNOWN_ARGUMENTS);
            return ERR_UNKNOWN_ARGUMENTS;
        }
        rc = export(argv[2], argv[3]);
    }
    else if (strcmp(argv[1], "sb") == 0)
    {
        if (argc != 3)
        {
            processing_errors(ERR_UNKNOWN_ARGUMENTS);
            return ERR_UNKNOWN_ARGUMENTS;
        }
        rc = sort_students_in_file(argv[2]);
    }
    else if (strcmp(argv[1], "db") == 0)
    {
        if (argc != 3)
        {
            processing_errors(ERR_UNKNOWN_ARGUMENTS);
            return ERR_UNKNOWN_ARGUMENTS;
        }
        rc = delete_student_less_mean(argv[2]);
    }
    else
        rc = ERR_UNKNOWN_ARGUMENTS;

    return rc;
}

int file_size(FILE *f, size_t *size)
{
    long sz;

    if (fseek(f, 0L, SEEK_END))
        return 1;

    sz = ftell(f);
    if (sz < 0)
        return 1;

    *size = sz;

    return fseek(f, 0L, SEEK_SET);
}

// Обработка ошибок
void processing_errors(int exitcode)
{
    if (exitcode == ERR_EMPTY_INPUT)
        printf("Error, run program: example.exe <flag> <source file>\n");
    else if (exitcode == ERR_WRONG_INPUT)
        printf("Error, Wrong Input\n");
    else if (exitcode == ERR_FILE)
        printf("Error, Wrong File\n");
    else if (exitcode == ERR_WRITE)
        printf("Error, While Writing\n");
    else if (exitcode == ERR_READ)
        printf("Error, While Reading\n");
    else if (exitcode == ERR_COUNT)
        printf("Error, Count Must be bigger then 0 \n");
    else if (exitcode == ERR_CONVERT)
        printf("Error, While Convertation\n");
    else if (exitcode == ERR_STRING_OWERFLOW)
        printf("Error, String Overflow\n");
    else if (exitcode == ERR_EMPTY_LINE)
        printf("Error, Empty Line \n");
    else if (exitcode == ERR_WRONG_MARK)
        printf("Error, Wrong Mark \n");
    else if (exitcode == ERR_WRONG_FIELDS)
        printf("Error, Wrong_Field \n");
    else if (exitcode == ERR_WRONG_MARKS)
        printf("Error, Wrong Marks \n");
    else if (exitcode == ERR_EMPTY_OUTPUT)
        printf("Error, Empty Output\n");
    else if (exitcode == ERR_UNKNOWN_ARGUMENTS)
        printf("Error, Unknown Argument\n");
}

// Проверка строки
int check_string(const char *string)
{
    char *endline = strchr(string, '\n');
    if (strlen(string) <= 1)
        return ERR_EMPTY_LINE;

    if (endline)
    {
        *endline = '\0';
        return ERR_OK;
    }
    else
        return ERR_STRING_OWERFLOW;
}

// Конвертирует текстовик в бинарник
int import(const char *filename_txt, const char *filename_bin)
{
    FILE *file_txt = fopen(filename_txt, "r"), *file_bin = fopen(filename_bin, "wb");
    struct students_struct student;
    memset(&student, 0, sizeof(student));
    if (file_txt == NULL || file_bin == NULL)
        return ERR_FILE;
    size_t size = 0;
    int rc = file_size(file_txt, &size);
    if (rc != ERR_OK)
        return ERR_FILE;
    char surname[MAX_SURNAME_LEN + 1], name[MAX_NAME_LEN + 1];

    while (fgets(surname, MAX_SURNAME_LEN + 1, file_txt) != NULL)
    {
        rc = check_string(surname);
        if (rc != ERR_OK)
            return rc;

        strcpy(student.surname, surname);
        if (fgets(name, MAX_NAME_LEN + 1, file_txt) != NULL)
        {
            rc = check_string(name);
            if (rc == ERR_OK)
                strcpy(student.name, name);
            else
                return rc;
        }
        else
            return ERR_READ;

        for (size_t i = 0; i < MAX_MARKS_LEN; i++)
        {
            if (fscanf(file_txt, "%" SCNu32, &student.marks[i]) != 1)
                return ERR_READ;

            if (student.marks[i] > 4294967000)
                return ERR_READ;
        }
        fgetc(file_txt);
        fwrite(&student, sizeof(struct students_struct), 1, file_bin);
    }
    if (feof(file_txt) == 0)
        rc = ERR_FILE;

    fclose(file_txt);
    fclose(file_bin);
    return rc;
}

int print_bin_file(FILE *file)
{
    int rc = ERR_OK;
    if (file == NULL)
        return ERR_FILE;
    rewind(file);

    size_t size = 0, struct_size = sizeof(struct students_struct);
    rc = file_size(file, &size);
    if (rc != ERR_OK)
        return rc;
    if (size % struct_size != 0)
        return ERR_FILE;
    struct students_struct student;
    while (fread(&student, struct_size, 1, file) == 1)
    {
        printf("%s\n%s\n", student.surname, student.name);
        for (size_t i = 0; i < MAX_MARKS_LEN; i++)
        {
            printf("%d ", student.marks[i]);
        }
        printf("\n");
    }
    return ERR_OK;
}

// Реализация флага экспорт. Конвертирует текстовый файл в бинарный
int export(const char *filename_bin, const char *filename_txt)
{
    int rc = ERR_OK;
    FILE *bin_file = fopen(filename_bin, "rb");
    FILE *txt_file = fopen(filename_txt, "w");
    if (bin_file == NULL || txt_file == NULL)
        return ERR_FILE;
    struct students_struct student;
    memset(&student, 0, sizeof(student));
    while (fread(&student, sizeof(struct students_struct), 1, bin_file) == 1)
    {
        fprintf(txt_file, "%s\n%s\n", student.surname, student.name);
        for (int i = 0; i < MAX_MARKS_LEN; i++)
            fprintf(txt_file, "%u ", student.marks[i]);
        fprintf(txt_file, "\n");
    }
    if (feof(bin_file) == 0)
        return ERR_READ;
    fclose(bin_file);
    fclose(txt_file);
    return rc;
}
