#include <stdio.h>
#include <math.h>

#define EXIT_SUCCESS 0
#define WRONG_INPUT 1
#define TRIANGLE_NOT_EXIST 2
#define UNEXPECTED_ERROR 3
#define EPS 0.0001

// считаем дистанцию по теореме пифагора
float distance(float x1, float y1, float x2, float y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
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
    if (a != 0)
        summ += 1;
    if (b != 0)
        summ += 1;
    if (c != 0)
        summ += 1;
    if (summ <= 1)
        return 3;

    if (a + b > c + EPS && b + c > a + EPS && a + c > b + EPS)
    {
        if (((a * a - b * b - c * c) > -EPS && (a * a - b * b - c * c) < EPS) || ((b * b - a * a - c * c) > -EPS && (b * b - a * a - c * c) < EPS) || ((c * c - a * a - c * c) > -EPS && (c * c - a * a - c * c) < EPS))
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
            return 0;
            // Треугольник острый
    }
    {
        return 3;
    }
    return 3;
}

int main(void)
{
    float xa, ya, xb, yb, xc, yc;
    printf(">> Input float coordinate of 3 points: \n");
    if (scanf("%f%f%f%f%f%f", &xa, &ya, &xb, &yb, &xc, &yc) != 6)
        return WRONG_INPUT;

    int a = solve(xa, ya, xb, yb, xc, yc);
    if (a == 3)
        {printf("TRIANGLE_NOT_EXIST");
        return TRIANGLE_NOT_EXIST;}

    else
        printf("%d\n", a);
    return EXIT_SUCCESS;
}




/*
>> Input float coordinate of 3 points: 
0 0 0 0 0 0
TRIANGLE_NOT_EXIST

>> Input float coordinate of 3 points: 
0 0 0 2 2 0
1

>> Input float coordinate of 3 points: 
0 0 0 3 4 0
1

>> Input float coordinate of 3 points: 
0 0 1.5 0.5 3 0
2

>> Input float coordinate of 3 points: 
0.0 0.0 1.0 4.0 2.0 0.0
0


*/