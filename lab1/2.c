#include <stdio.h>
#include <math.h>

#define ERROR 1
// 24 variant

int main(void)
{
    int a, b, h;
    float x, bok, P;
    printf(">>Input integer lenghts of a, b and height: ");
    scanf("%d%d%d", &a, &b, &h);
    x = (a - b) / 2.0;
    bok = x;
    bok = sqrt(pow(x, 2) + pow(h, 2)); // Считаем боковую сторону
    P = a + b + 2 * bok;               // считаем периметр
    printf("%f\n", P);

    return 0;
}

/*  
(base) ypopov2005@Air-Urij lab1 % ./2.exe
>>Input integer lenghts of a, b and height: 1 1 1
4.000000

>>Input integer lenghts of a, b and height: 1 2 3
9.082763

>>Input integer lenghts of a, b and height: 10 10 10
40.000000

>>Input integer lenghts of a, b and height: 100000 10000 1
200000.000000
*/