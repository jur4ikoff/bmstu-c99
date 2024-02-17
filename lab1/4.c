#include <stdio.h>

int main(void)
{
    printf("Введите баланс: ");
    int count=0, balance; // Задаем переменные
    scanf("%d", &balance); // Считываем
    count = (balance - 20) / (45-20); // Расчеты
    printf("%d Бутылок\n", count); // Вывод

    

    return 0;
}