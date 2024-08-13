#include "io.h"

int input_string(char *string)
{
    if (!fgets(string, MAX_NAME_LEN, stdin))
        return ERR_STRING_INPUT;

    char *newline = strchr(string, '\n');
    if (!newline)
        return ERR_OVERFLOW;

    *newline = '\0';
    return ERR_OK;
}

int input_size(size_t *size)
{
    if (scanf("%zu", size) != 1)
        return ERR_INPUT;

    if (*size < 1 || *size > MAX_POINTS)
        return ERR_INPUT;
    fgetc(stdin);
    return ERR_OK;
}

int input_to_struct(Point points[], size_t count)
{
    int rc = ERR_OK;
    char name[MAX_NAME_LEN + 1];
    for (size_t i = 0; i < count; i++)
    {
        if ((rc = (input_string(name))) != ERR_OK)
        {
            output(rc);
            return rc;
        }
        // fgets(stdin);
        double x, y;
        if (scanf("%lf", &x) != 1)
            return ERR_INPUT;

        if (scanf("%lf", &y) != 1)
            return ERR_INPUT;
        fgetc(stdin);

        Point point;
        strcpy(point.name, name);
        point.x = x;
        point.y = y;
        memcpy(&points[i], &point, sizeof(point));
    }
    return rc;
}

void print_struct(Point points[], size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        printf("Name: %s, X: %.2lf, Y: %.2lf\n", points[i].name, points[i].x, points[i].y);
    }
}

void output(int arg)
{
    switch (arg)
    {
    case ERR_STRING_INPUT:
        printf("ERR_STRING_INPUT\n");
        break;
    case ERR_OVERFLOW:
        printf("ERR_OVERFLOW\n");
        break;
    case ERR_INPUT:
        printf("ERR_INPUT\n");
        break;
    case ERR_EMPTY:
        printf("ERR_EMPTY\n");
        break;
    }
}

double calc_square(Point point1, Point point2, Point point3)
{
    double square;
    square = 0.5 * fabs((point2.x - point1.x) * (point3.y - point1.y) - (point3.x - point1.x) * (point2.y) - point1.y);
    return square;
}

void find_max_square(Point points[], size_t count, size_t *index1, size_t *index2, size_t *index3)
{
    double max = -10e6;
    for (size_t i = 0; i < count; i++)
    {
        for (size_t j = i + 1; j < count; j++)
        {
            for (size_t k = j + 1; k < count; k++)
            {
                double square = calc_square(points[i], points[j], points[k]);
                if (square > max)
                {
                    *index1 = i;
                    *index2 = j;
                    *index3 = k;
                    max = square;
                }
            }
        }
    }
}