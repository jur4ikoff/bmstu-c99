// Find sum of digits in letters

#include <stdio.h>
#include <stdlib.h>


int digits_sum(int num)
{
    num = abs(num);
    int summ = 0;
    while (num > 0)
    {
        summ += num % 10;
        num /= 10;

    }

    return summ;
}

int main(void)
{
    int a, b;
    printf("Введите 2 целых числа: \n");
    if (scanf("%d%d", &a, &b) != 2)
        return 1;
    
    int sum_a =  digits_sum(a);
    int sum_b = digits_sum(b);

    if (sum_a > sum_b)
        printf("Число А больше: sum = %d", sum_a);
    else if (sum_a < sum_b)
    {
        printf("Число А больше: sum = %d", sum_b);
    }
    else
    {
        printf("Сумма равна: sum = %d", sum_a);
    }


    return 0;
}