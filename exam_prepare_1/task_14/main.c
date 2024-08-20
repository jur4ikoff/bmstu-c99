/*
Структура, описывающая точку, содержит три поля: имя точки и две ее координаты. 
Найти такую точку из массива структур, которая
будет максимально удалена от начала координат. Если искомая точка не найдена, вывести
соответствующее сообщение и завершить программу с ненулевым кодом
*/
#include "constants.h"
#include "io.h"
#include "solve.h"

int main(void)
{
    Point points[MAX_POINTS];
    size_t count = 0;
    int rc = ERR_OK;
    if ((rc = input_size(&count)) != ERR_OK)
    {
        output(rc);
        return rc;
    }

    if ((rc = input_to_struct(points, count)) != ERR_OK)
    {
        output(rc);
        return rc;
    }

    size_t index = 0;
    double dist = max_distance(points, count, &index);
    printf("Max dist to point \"%s\". Dist - %le\n", points[index].name, dist);
    return ERR_OK;
}
