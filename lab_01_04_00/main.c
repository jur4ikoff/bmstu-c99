#include <stdio.h>

int main(void)
{
    printf("Введите баланс: ");
    int count = 0, balance;             // Задаем переменные
    scanf("%d", &balance);              // Считываем
    count = (balance - 20) / (45 - 20); // Расчеты
    printf("%d Бутылок\n", count);      // Вывод

    return 0;
}

/*
Введите баланс: 10
0 Бутылок

(base) ypopov2005@Air-Urij lab1 % ./4.exe
Введите баланс: 20
0 Бутылок

(base) ypopov2005@Air-Urij lab1 % ./4.exe
Введите баланс: 40
0 Бутылок

(base) ypopov2005@Air-Urij lab1 % ./4.exe
Введите баланс: 50
1 Бутылок

(base) ypopov2005@Air-Urij lab1 % ./4.exe
Введите баланс: 60
1 Бутылок

(base) ypopov2005@Air-Urij lab1 % ./4.exe
Введите баланс: 65
1 Бутылок

(base) ypopov2005@Air-Urij lab1 % ./4.exe
Введите баланс: 70
2 Бутылок

(base) ypopov2005@Air-Urij lab1 % ./4.exe
Введите баланс: 75
2 Бутылок

(base) ypopov2005@Air-Urij lab1 % ./4.exe
Введите баланс: 85
2 Бутылок

(base) ypopov2005@Air-Urij lab1 % ./4.exe
Введите баланс: 90
2 Бутылок

(base) ypopov2005@Air-Urij lab1 % ./4.exe
Введите баланс: 95
3 Бутылок
*/
