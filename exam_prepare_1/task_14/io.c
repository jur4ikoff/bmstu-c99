#include "io.h"

void output(int arg)
{
    switch (arg)
    {
    case ERR_EMPTY:
        printf("ERR_EMPTY\n");
        break;
    case ERR_NAME:
        printf("ERR_NAME\n");
        break;
    case ERR_NUMBER:
        printf("ERR_NUMBER\n");
        break;
    case ERR_SIZE:
        printf("ERR_SIZE\n");
        break;
    }
}

int input_name(char *name)
{
    if (!fgets(name, MAX_NAME, stdin))
        return ERR_NAME;

    char *newline = strchr(name, '\n');

    if (!newline)
        return ERR_NAME;

    *newline = 0;
    return ERR_OK;
}

int input_size(size_t *count)
{
    if (scanf("%zu", count) != 1)
        return ERR_SIZE;

    fgetc(stdin);
    return ERR_OK;
}

int input_to_struct(Point points[], size_t count)
{
    int rc = ERR_OK;
    for (size_t i = 0; i < count; i++)
    {
        Point point;

        if (((rc = input_name(point.name)) != ERR_OK))
            return rc;

        if (!scanf("%le", &point.x))
            return ERR_NUMBER;
        fgetc(stdin);

        if (!scanf("%le", &point.y))
            return ERR_NUMBER;
        fgetc(stdin);

        memcpy(&points[i], &point, sizeof(point));
    }

    return ERR_OK;
}
