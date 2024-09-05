#include "io.h"

int input_size(size_t *count)
{
    if (scanf("%zu", count) != 1)
        return ERR_COUNT;

    if (*count == 0 || *count > MAX_SIZE)
        return ERR_COUNT;

    return ERR_OK;
}

int input_string(char *string)
{
    if (!fgets(string, MAX_STRING, stdin))
        return ERR_STRING;

    char *newline = strchr(string, '\n');

    if (!newline)
        return ERR_OVERFLOW;

    *newline = '\0';
    return ERR_OK;
}

int input_height(size_t *height)
{
    if (scanf("%zu", height) != 1)
        return ERR_NUMBER;

    if (*height <= 0 || *height > 1000)
        return ERR_NUMBER;

    return ERR_OK;
}

int input_to_struct(size_t count, struct Person persons[])
{
    int rc = ERR_OK;

    for (size_t i = 0; i < count; i++)
    {
        if ((rc = input_string(persons[i].name)) != ERR_OK)
            return rc;

        if ((rc = input_height(&persons[i].height)) != ERR_OK)
            return rc;
        fgetc(stdin);
    }

    return rc;
}

void print_struct_array(struct Person persons[], size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        printf("%s ", persons[i].name);
        printf("%zu\n", persons[i].height);
    }
}

void output(int arg)
{
    switch (arg)
    {
    case ERR_COUNT:
        printf("ERR_COUNT\n");
        break;
    case ERR_NUMBER:
        printf("ERR_NUMBER\n");
        break;
    case ERR_STRING:
        printf("ERR_STRING\n");
        break;
    case ERR_OVERFLOW:
        printf("ERR_OVERFLOW\n");
        break;
    case ERR_OUTPUT:
        printf("ERR_OUTPUT\n");
        break;
    }
}
