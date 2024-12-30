#include <stdio.h>
#include "square.h"
#include "rectangle.h"

int main(void)
{
    rectangle_t *rect = NULL;
    class_rect_create(&rect, 1, 2);
    double area = rect->method.calc_squre(rect);
    printf("%f", area);
    return 0;
}