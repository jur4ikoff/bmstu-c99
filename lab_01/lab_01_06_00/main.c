#include <stdio.h>
#include <math.h>

#define EXIT_SUCCESS 0
#define WRONG_INPUT 1
#define TRIANGLE_NOT_EXIST 2
#define UNEXPECTED_ERROR 3
#define EPS 0.000001

// считаем дистанцию по теореме пифагора
float distance(float x1, float y1, float x2, float y2)
{
    return sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

// Решение
int solve(float x1, float y1, float x2, float y2, float x3, float y3)
{
    // Считаем дистанциюю
    float a = distance(x1, y1, x2, y2);
    float b = distance(x2, y2, x3, y3);
    float c = distance(x3, y3, x1, y1);

    // Проверка на то что треугольник существует
    int summ = 0;
    if (fabsf(a) > EPS)
        summ += 1;
    if (fabsf(b) > EPS)
        summ += 1;
    if (fabsf(c) > EPS)
        summ += 1;
    if (summ <= 1)
        return 3;

    if (a + b > c + EPS && b + c > a + EPS && a + c > b + EPS)
    {
        if ((fabsf(a * a - b * b - c * c) < EPS) || (fabsf(b * b - a * a - c * c) < EPS) || (fabsf(c * c - a * a - c * c) < EPS))
        {
            // Треугольник прямоугольный
            return 1;
        }
        else if (a * a > b * b + c * c || b * b > a * a + c * c || c * c > a * a + b * b)
        {
            // треугольник тупоугольный
            return 2;
        }
        else
            // Треугольник острый
            return 0;
    }
    return 3;
}

int main(void)
{
    // Ввод
    float xa, ya, xb, yb, xc, yc;
    printf(">> Input float coordinate of three points: \n");
    if (scanf("%f%f%f%f%f%f", &xa, &ya, &xb, &yb, &xc, &yc) != 6)
    {
        printf("WRONG_INPUT");
        return WRONG_INPUT;
    }

    // Решение
    int a = solve(xa, ya, xb, yb, xc, yc);
    if (a == 3)
    {
        printf("TRIANGLE_NOT_EXIST\n");
        return TRIANGLE_NOT_EXIST;
    }
    else
        printf("Triangle_status: %d\n", a);
    return EXIT_SUCCESS;
}
