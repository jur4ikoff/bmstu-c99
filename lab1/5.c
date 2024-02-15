#include <stdio.h>
#include <math.h>

#define SUCCESS 0

int main(void)
{
    int res, a, n;
    printf("Input integer a and integer n > 0: ");
    if (scanf("%d%d", &a, &n) != 2)
    {
        printf("Wrong input\n");
        return 1;
    }

    if (n < 0)
    {
        printf("ERROR n < 0");
        return 2;
    }

    res = pow(a, n);
    printf("result of a^n = %d\n", res);

    return SUCCESS;
}

/*
jur4ik@jur4ik-1-2:~/Documents/BMSTU-C/lab1$ ./5.exe
Input integer a and integer n > 0: 10 2
result of a^n = 100

jur4ik@jur4ik-1-2:~/Documents/BMSTU-C/lab1$ ./5.exe
Input integer a and integer n > 0: -2 10
result of a^n = 1024

jur4ik@jur4ik-1-2:~/Documents/BMSTU-C/lab1$ ./5.exe
Input integer a and integer n > 0: -2 1
result of a^n = -2

jur4ik@jur4ik-1-2:~/Documents/BMSTU-C/lab1$ ./5.exe
Input integer a and integer n > 0: 
dsadas asdasda
Wrong input
*/