#include <stdio.h>
#include <math.h>

#define EXIT_SUCCESS 0
#define PRECISION_OUT_LIMIT 1
#define WRONG_INPUT 2
#define EPS 2.71828
#define ABS(x) ((x) < 0? -(x): (x))
 

 int factorial(int n)
 // Подсчет факториала
{
    int result = 1;
    for (int i = 1; i <= n; i++)
    {
        result *= i;
    }
    return result;
}

float calc_row(float x, float e)
// Подсчет ряда
{
    float cur = pow(10, 8);
    float res = 1.0;
    int i = 1;
    while (cur > e)
    {
        cur = ((pow(x, i)) / factorial(i));
        res = res + cur;
        i++;
    }
    return res;
}

float abs_error_rate(float f, float s)
{
    // Вычисление абсолютной погрешности
    float res;
    res = ABS(f - s);
    return res;
}

float rel_error_rate(float f, float s)
{
    // Вычисление относительной погрешности
    float res;
    res = (ABS(f - s) / ABS(f));
    return res;
}

int main(void)
{
    float x, e;
    printf(">> Input x and e in (0, 1]: ");
    if (scanf("%f%f", &x, &e) != 2) // Ввод + обработка ошибок
        return WRONG_INPUT;
    if (e <= 0 || e > 1)
        return PRECISION_OUT_LIMIT;
    
    // Запускаем фнкцию подсчета ряда
    float s = calc_row(x, e);
    
    float f = pow(EPS, x); // Вычисляем истинное значение

    // Ищем точность
    float errt1 = abs_error_rate(f, s);
    float errt2 = rel_error_rate(f, s);
    
    // Вывод
    printf("f(x) = %f, s(x) = %f, abs_error = %f, rel_error = %f \n", f, s, errt1, errt2);
    return EXIT_SUCCESS;
}

/*
>> Input x and e in (0, 1]: 1 0.1
f(x) = 2.718280, s(x) = 2.708333, abs_error = 0.009947, rel_error = 0.003659
>> Input x and e in (0, 1]: 2 0.01
f(x) = 7.389046, s(x) = 7.387302, abs_error = 0.001744, rel_error = 0.000236
*/