#include "solve.h"
#include "math.h"
double max_distance(Point *points, size_t count, size_t *index)
{
    *index = 0;
    double max_distace = -10e6;

    for (size_t i = 0; i < count; i++)
    {
        double cur_dist = sqrt(pow(points[i].x, 2) + pow(points[i].y, 2));
        if (cur_dist > max_distace)
        {
            max_distace = cur_dist;
            *index = i;
        }
    }

    return max_distace;
}