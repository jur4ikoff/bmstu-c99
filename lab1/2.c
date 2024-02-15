#include <stdio.h>
#include <math.h>
// 24 variant

int main(void)
{
    int a, b, h;
    float x, bok, P;
    scanf("%d%d%d", &a, &b, &h);
    x = (a - b) / 2.0;
    bok = x;
    bok = sqrt(pow(x, 2) + pow(h, 2));
    P = a + b + 2 * bok;
    printf("%f\n", P);
    
    return 0;
}