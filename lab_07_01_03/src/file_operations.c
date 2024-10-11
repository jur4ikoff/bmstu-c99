#include "file_operations.h"
#include <stdio.h>
#include "errors.h"
#include "constants.h"

int file_read_int(char *filename, size_t *size)
{
    *size = 0;
    FILE *file = fopen(filename, "r");

    if (file == NULL)
        return ERR_FILENAME;

    int buffer;
    while (fscanf(file, "%d", &buffer) == 1)
    {
        (*size)++;
    }
    if (feof(file) == 0)
        return ERR_READ;

    fclose(file);
    return ERR_OK;
}

/**
 *
 */
int file_write_int(char *filename, int *begin_arr, int *end_arr)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
        return ERR_FILENAME;

    while (begin_arr < end_arr)
    {
        if (begin_arr + 1 < end_arr)
            fprintf(file, "%d ", *begin_arr);
        else
            fprintf(file, "%d\n", *begin_arr);
        begin_arr++;
    }

    fclose(file);
    return ERR_OK;
}
