// структура, описывает точку, содержит имя и две координаты. нужно найти 3 точки, образующие треугольнк максимальной площади
#include "constants.h"
#include "io.h"

int main(void)
{
    int rc = ERR_OK;
    Point points[MAX_POINTS];
    size_t count = 0;

    if ((rc = input_size(&count) != ERR_OK))
    {
        output(rc);
        return rc;
    }

    if (count < 3)
    {
        output(ERR_EMPTY);
        return ERR_EMPTY;
    }

    if ((rc = input_to_struct(points, count)) != ERR_OK)
    {
        output(rc);
        return rc;
    }
    print_struct(points, count);

    size_t index1 = 0, index2 = 0, index3 = 0;
    find_max_square(points, count, &index1, &index2, &index3);
    printf("%s, %s, %s\n", points[index1].name, points[index2].name, points[index3].name);
    return rc;
}
