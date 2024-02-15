#include <stdio.h>
#include <math.h>

int main(void)
{
    printf("Введите рост человека(см) Обхват грудной клетки(см) и вес(кг)\n");
    int h, t, m;
    float mnormal, BMI;
    scanf("%d%d%d", &h, &t, &m);

    mnormal = h * t / 240.0;
    BMI = m / (pow(h, 2));
    printf("mnorml: %f BMI: %f\n", mnormal, BMI);

    return 0;
}