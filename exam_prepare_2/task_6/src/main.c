#include <stdio.h>
#define TO_STRING(x) (#x)
#define INT(x) int number##x

int main(void)
{
    INT(1);
    number1 = 10;
    printf("string = %s\n", TO_STRING(number1));
    (void)number1;
    return 0;
}
