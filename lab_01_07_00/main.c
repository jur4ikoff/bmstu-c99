#include <stdio.h>
#include <math.h>

#define EXIT_SUCCESS 0
#define PRECISION_OUT_LIMIT 1
#define WRONG_INPUT 2
#define EXP 2.718282f

// Подсчет ряда
float calc_row(float x, float e)
{
    float cur = 1.0;
    float res = 1.0;
    int i = 1;
    do
    {
        cur = cur * x / i;
        res = res + cur;
        i++;
    } while (fabs(cur) > e);
    return res;
}

float abs_error_rate(float f, float s)
{
    // Вычисление абсолютной погрешности
    float res;
    res = fabsf(f - s);
    return res;
}

float rel_error_rate(float f, float s)
{
    // Вычисление относительной погрешности
    float res;
    res = (fabsf(f - s) / fabsf(f));
    return res;
}

int main(void)
{
    float x, e;
    printf("Input x and e from zero to one: ");
    if (scanf("%f%f", &x, &e) != 2)
    {
        printf("WRONG INPUT\n");
        return WRONG_INPUT;
    }
    if (e <= 0 || e > 1)
    {
        printf("WRONG INPUT\n");
        return PRECISION_OUT_LIMIT;
    }

    // Запускаем фнкцию подсчета ряда
    float s = calc_row(x, e);

    float f = powf(EXP, x); // Вычисляем истинное значение

    // Ищем точность
    float errt1 = abs_error_rate(f, s);
    float errt2 = rel_error_rate(f, s);

    // Вывод
    printf("s(x) = %f f(x) = %f abs_error = %f rel_error = %f \n", s, f, errt1, errt2);
    return EXIT_SUCCESS;
}
