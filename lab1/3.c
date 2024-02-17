#include <stdio.h>
#include <math.h>

int main(void)
{
    printf(">>Введите рост человека(см) Обхват грудной клетки(см) и вес(кг)\n");
    // Ввод
    int h, t, m;
    float mnormal, BMI;
    scanf("%d%d%d", &h, &t, &m);


    // Вычисления
    mnormal = h * t / 240.0;
    BMI = m / (pow(h, 2));

    printf("mnorml: %f BMI: %f\n", mnormal, BMI);
    return 0;
}


/*
(base) ypopov2005@Air-Urij lab1 % ./3.exe
Введите рост человека(см) Обхват грудной клетки(см) и вес(кг)
 1 1
1
mnorml: 0.004167 BMI: 1.000000


Введите рост человека(см) Обхват грудной клетки(см) и вес(кг)
10 10 10
mnorml: 0.416667 BMI: 0.100000


Введите рост человека(см) Обхват грудной клетки(см) и вес(кг)
180 60 65
mnorml: 45.000000 BMI: 0.002006

*/