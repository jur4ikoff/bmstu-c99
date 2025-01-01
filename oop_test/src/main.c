#include <stdio.h>
#include "square.h"
#include "rectangle.h"

int main(void)
{
    rectangle_t *rect = NULL;
    class_rect_create(&rect, 1, 2);
    double area_rect = rect->method.calc_squre(rect);

    square_t *sqrt = NULL;
    class_square_create(&sqrt, 2);
    double area_sqrt = sqrt->method.calc_squre(sqrt);
    printf("area rect = %f area square = %f\n", area_rect, area_sqrt);

    class_rect_destroy(rect);
    class_square_destroy(sqrt);
    return 0;
}