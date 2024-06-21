#include "io.h"

// Функция обрабатывает поданные аргументы
int proccessing_args(int argc, char **argv)
{
    FILE *file;
    int rc = ERR_OK;
    if (argc < 3 || argc > 4)
        return ERR_UNKNOWN_ARGS;

    if (strcmp(argv[1], "import") == 0)
    {
        if (argc != 4)
            return ERR_UNKNOWN_ARGS;
        rc = import(argv[2], argv[3]);
    }
    else if (strcmp(argv[1], "export") == 0)
    {
        if (argc != 4)
            return ERR_UNKNOWN_ARGS;
        rc = export(argv[2], argv[3]);
    }
    else if (strcmp(argv[1], "c") == 0)
    {
        if (argc != 4)
            return ERR_UNKNOWN_ARGS;
        file = fopen(argv[3], "wb");
        if (file == NULL)
            return ERR_FILE;

        int count = strtol(argv[2], NULL, 10);
        if (count < 1)
            return ERR_COUNT;
        rc = fill_bin_file(file, count);
        fclose(file);
        if (rc != ERR_OK)
            return rc;
    }
    else if (strcmp(argv[1], "p") == 0)
    {
        if (argc != 3)
            return ERR_UNKNOWN_ARGS;
        file = fopen(argv[2], "rb");
        if (file == NULL)
            return ERR_FILE;

        rc = print_int_file(file);
        fclose(file);
        if (rc != ERR_OK)
            return rc;
    }
    else if (strcmp(argv[1], "s") == 0)
    {
        if (argc != 3)
            return ERR_UNKNOWN_ARGS;
        file = fopen(argv[2], "rb+");
        if (file == NULL)
            return ERR_FILE;

        rc = sort_int_file(file);
        fclose(file);
    }
    else
        rc = ERR_UNKNOWN_ARGS;

    return rc;
}

// Обработка ошибок
void processing_errors(int exitcode)
{
    if (exitcode == ERR_EMPTY_INPUT)
        printf("Error, run program: example.exe <flag> <source file>\n");
    else if (exitcode == ERR_WRONG_INPUT)
        printf("Error, run program: example.exe <flag> <source file>\n");
    else if (exitcode == ERR_FILE)
        printf("Error file not exist\n");
    else if (exitcode == ERR_WRITE)
        printf("Error, While Writing\n");
    else if (exitcode == ERR_READ)
        printf("Error, While Reading\n");
    else if (exitcode == ERR_COUNT)
        printf("Error, Count/File len Must be bigger then 0 \n");
    else if (exitcode == ERR_EMPTY_OUTPUT)
        printf("Error, Empty Output\n");
    else if (exitcode == ERR_UNKNOWN_ARGS)
        printf("Error, Unknown Arguments\n");
}

int import(const char *filename_txt, const char *filename_bin)
{
    FILE *file_txt = fopen(filename_txt, "r");
    FILE *file_bin = fopen(filename_bin, "wb");

    if (file_txt == NULL || file_bin == NULL)
        return ERR_FILE;

    int number;
    while ((fscanf(file_txt, "%d", &number)) == 1)
    {
        fwrite(&number, sizeof(int), 1, file_bin);
    }
    if (feof(file_txt) == 0)
        return ERR_FILE;

    fclose(file_txt);
    fclose(file_bin);

    return ERR_OK;
}

// Конвертирует бинарник в текстовик
int export(const char *filename_bin, const char *filename_txt)
{
    FILE *file_bin = fopen(filename_bin, "rb");
    FILE *file_txt = fopen(filename_txt, "w");

    if (file_txt == NULL || file_bin == NULL)
        return ERR_FILE;

    size_t size;
    int number, rc = ERR_OK;
    rc = file_size(file_bin, &size);
    if ((size % sizeof(int) != 0) || (rc != ERR_OK))
    {
        return ERR_FILE;
    }

    while (fread(&number, sizeof(int), 1, file_bin) == 1)
    {
        char str[20];
        sprintf(str, "%d", number);
        int write = fprintf(file_txt, "%s ", str);
        if (write != (int)strlen(str) + 1)
        {
            return ERR_WRITE;
        }
    }
    return rc;
}
