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
    float hh = h / 100.0;
    BMI = m / (pow(hh, 2));

    printf("mnorml: %f BMI: %f\n", mnormal, BMI);
    return 0;
}


/*
>>Введите рост человека(см) Обхват грудной клетки(см) и вес(кг)
180 60 60
mnorml: 45.000000 BMI: 18.518520

(base) ypopov2005@Air-Urij lab1 % ./3.exe
>>Введите рост человека(см) Обхват грудной клетки(см) и вес(кг)
150 100 100
mnorml: 62.500000 BMI: 44.444443

(base) ypopov2005@Air-Urij lab1 % ./3.exe
>>Введите рост человека(см) Обхват грудной клетки(см) и вес(кг)
150 60 120
mnorml: 37.500000 BMI: 53.333332
*/