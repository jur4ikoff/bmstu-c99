#include <stdio.h>

#define EXIT_SUCCESS 0
#define WRONG_INPUT 1

void printBinary(unsigned number)
{
    char data[32];
    for (int i = 0; i < 32; i++)
    {
        data[i] = number % 2;
        number /= 2;
    }
    char el = 0;
    for (int i = 0; i < 32; i++)
    {   
        if (data[31 - i] != 0)
            el = 1;
        
        if (el)
            printf("%d", data[31 - i]);
    }
}

unsigned cyclicRotate(unsigned number, int n)
{
    for (int i = 0; i < n; i++)
    {
        unsigned lastBIt = number & 1;
        number >>= 1;
        number += lastBIt << 31;
    }
    return number;
}

int main(void)
{
    unsigned a;
    int n;
    printf(">> Input a, n: ");
    if (scanf("%u%d", &a, &n) != 2)
    {
        printf("Error: IO error\n");
        return WRONG_INPUT;
    }


    unsigned result = cyclicRotate(a, n);
    printBinary(result);
    printf("\n");

    return EXIT_SUCCESS;
}