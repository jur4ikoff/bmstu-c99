#include <stdio.h>
#include <math.h>

#define SUCCESS 0
#define WRONG_INPUT 1

// Подсчет значения
float calc(float a, int n)
{
    float res = 1;
    for (int i = 1; i <= n; i++)
    {
        res *= a;
    }

    return res;
}


//main функция
int main(void)
{
    //Ввод и объявление переменных
    float a;
    int n;
    float res;
    printf("Input integer a and integer positive n: ");
    if (scanf("%f%d", &a, &n) != 2)
    {
        printf("Wrong input\n");
        return WRONG_INPUT;
    }

    if (n <= 0)
    {
        printf("n must be positive\n");
        return 2;
    }

    // Calculate Result
    res = calc(a, n);
    printf("result of a^n = %f\n", res);

    return SUCCESS;
}
