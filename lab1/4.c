#include <stdio.h>


int main(void)
{
    printf("Введите баланс: ");
    int count=0, balance;
    scanf("%d", &balance);
    count = (balance - 20) / (45-20);
    printf("%d Бутылок\n", count);

    

    return 0;
}