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
    printf("Result: ");
    printBinary(result);
    printf("\n");

    return EXIT_SUCCESS;
}


/*
jur4ik@jur4ik-1-2:~/Documents/BMSTU-C/lab1$ ./8.exe
>> Input a, n: 128 0
Result: 10000000

jur4ik@jur4ik-1-2:~/Documents/BMSTU-C/lab1$ ./8.exe
>> Input a, n: 128 1
Result: 1000000

jur4ik@jur4ik-1-2:~/Documents/BMSTU-C/lab1$ ./8.exe
>> Input a, n: 20527 0
Result: 101000000101111

jur4ik@jur4ik-1-2:~/Documents/BMSTU-C/lab1$ ./8.exe
>> Input a, n: 20527 1 
Result: 10000000000000000010100000010111

jur4ik@jur4ik-1-2:~/Documents/BMSTU-C/lab1$ ./8.exe
>> Input a, n: 20527 -1
Result: 101000000101111

jur4ik@jur4ik-1-2:~/Documents/BMSTU-C/lab1$ ./8.exe
>> Input a, n: 1 0
Result: 1

jur4ik@jur4ik-1-2:~/Documents/BMSTU-C/lab1$ ./8.exe
>> Input a, n: 1 1
Result: 10000000000000000000000000000000
*/