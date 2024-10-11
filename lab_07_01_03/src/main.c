#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "constants.h"
#include <stdbool.h>
#include <string.h>
#include "file_operations.h"
#include "array_operations.h"
#include "profiling.h"
// Сортировка 5 вариант, фильтр - 3

int main(int argc, char **argv)
{
#if SORT_TIME_EXP
    if (run_profiling(1) != ERR_OK)
    {
        return ERR_FILENAME;
    }
    return ERR_OK;
#endif
    char file_input[MAX_STRING_LEN], file_output[MAX_STRING_LEN];
    int rc = ERR_OK, *arr = NULL;
    size_t size = 0;
    bool is_filter = false;
    // printf("%d\n", argc);
    if (argc < 3)
    {
        print_err_msg(ERR_ARGS);
        return ERR_ARGS;
    }

    strcpy(file_input, argv[1]);
    strcpy(file_output, argv[2]);

    if (argc == 4)
    {
        if (strcmp(argv[3], "f") == 0)
            is_filter = true;
        else
        {
            print_err_msg(ERR_ARGS);
            return ERR_ARGS;
        }
    }
    else if (argc > 4)
    {
        print_err_msg(ERR_ARGS);
        return ERR_ARGS;
    }

    if ((rc = file_read_int(file_input, &size)) != ERR_OK)
    {
        print_err_msg(rc);
        return rc;
    }
    if (size == 0)
    {
        print_err_msg(ERR_EMPTY_INPUT);
        return ERR_EMPTY_INPUT;
    }
    if (size > MAX_COUNT)
    {
        print_err_msg(ERR_EMPTY_INPUT);
        return ERR_EMPTY_INPUT;
    }

    if ((rc = create_array_from_file(file_input, &arr, size)) != ERR_OK)
    {
        free(arr);
        print_err_msg(rc);
        return rc;
    }

    int *arr_end = arr + size;
    // print_array(arr, arr_end);

    int *filter_arr = NULL;
    int *end_filter_arr = NULL;
    if (is_filter == 1)
    {
        if ((rc = key(arr, arr_end, &filter_arr, &end_filter_arr)) != ERR_OK)
        {
            free(arr);
            free(filter_arr);
            print_err_msg(rc);
            return rc;
        }
    }
    else
    {
        if ((rc = copy_array(arr, arr_end, &filter_arr, &end_filter_arr)) != ERR_OK)
        {
            free(arr);
            free(filter_arr);
            print_err_msg(rc);
            return rc;
        }
    }

    // print_array(filter_arr, end_filter_arr);
    // my_sort(filter_arr, end_filter_arr - filter_arr, sizeof(int), compare);
    qsort(filter_arr, end_filter_arr - filter_arr, sizeof(int), compare);
    // print_array(filter_arr, end_filter_arr);

    // print_array(filter_arr, end_filter_arr);

    if ((rc = file_write_int(file_output, filter_arr, end_filter_arr)) != ERR_OK)
    {
        free(arr);
        free(filter_arr);
        print_err_msg(rc);
        return rc;
    }

    free(arr);
    free(filter_arr);
    return rc;
}
