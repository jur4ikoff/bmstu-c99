#include <stdio.h>
#include <math.h>
#include <stdint.h>

#define EXIT_SUCCESS 0
#define WRONG_INPUT 1
#define A_NEGATIVE 2

// Перевод в двоичную сс
void print_binary(unsigned number)
{
    unsigned v;
    v = pow(2, 31);
    for (int i = 1; i <= 32; i++)
    {
        if (number >= v)
        {
            printf("1");
            number -= v;
        }
        else
            printf("0");

        v /= 2;
    }
}

// битовый сдиг
unsigned cyclic_rotate(unsigned number, int n)
{
    for (int i = 0; i < n; i++)
    {
        unsigned last_bit = number & 1;
        number >>= 1;
        number += last_bit << 31;
    }
    return number;
}


int main(void)
{
    // Ввод, объявленеи переменных и обработка ошибок
    unsigned a;
    int n;
    printf(">> Input a, n: ");
    if (scanf("%u%d", &a, &n) != 2)
    {
        printf("Error: IO error\n");
        return WRONG_INPUT;
    }
    if (n < 0)
    {
        printf("Error: n must be positive\n");
        return WRONG_INPUT;
    }
    
    // Подсчет
    unsigned result = cyclic_rotate(a, n);

    // Вывод
    printf("Result: ");
    print_binary(result);
    printf("\n");

    return EXIT_SUCCESS;
}

