#include <stdio.h>
#include <math.h>

#define EXIT_SUCCESS 0
#define WRONG_INPUT 1


// Функция подсчета суммы
double update_sum(double sum, double el, int cnt)
{
    sum += el / cnt;
    return sum;
}

int main(void)
{
    // Ввод и объявление переменных
    double sum = 0.0, input_element;
    int count = 1;

    printf(" Input numbers: \n");
    int flag = 1;
    while (1)
    {
        if (scanf("%lf", &input_element) != 1)
        {
            printf("WRONG_INPUT\n");
            return WRONG_INPUT;
        }
        if (input_element < 0)
        {
            if (flag == 1)
            {
                printf("NO_SEQUENCE\n");
                return WRONG_INPUT;
            }
            break;
        }

        flag = 0;
        
        // подсчет значений
        sum = update_sum(sum, input_element, count);
        count++;
    }

    // Вывод
    double result = sqrt(sum);
    printf("Result: %f\n", result);
}
