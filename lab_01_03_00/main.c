#include <stdio.h>
#include <math.h>

int main(void)
{
    printf("Введите рост человека(см) Обхват грудной клетки(см) и вес(кг)\n");
    // Ввод
    float h, t, m;
    float mnormal, bmi;
    scanf("%f%f%f", &h, &t, &m);

    // Вычисления
    mnormal = h * t / 240.0f;
    float hh = h / 100.0f;
    bmi = m / (powf(hh, 2));

    printf("mnorml: %f BMI: %f\n", mnormal, bmi);
    return 0;
}
