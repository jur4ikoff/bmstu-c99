#include "check_my_snprintf.h"
#include "my_realization.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 200

// Проверка %s одним спецификатором
START_TEST(test_s_1)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    n1 = snprintf(s1, sizeof(s1), "Hello, %s!", "World");
    n2 = my_snprintf(s2, sizeof(s2), "Hello, %s!", "World");

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

/// Проверка %s несколькими спецификаторами
START_TEST(test_s_2)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    n1 = snprintf(s1, sizeof(s1), "Hello, %s! My name is %s", "World", "Yurii");
    n2 = my_snprintf(s2, sizeof(s2), "Hello, %s! My name is %s", "World", "Yurii");

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// Проверка %s несколькими спецификаторами. Пустая строка вместо аргумента
START_TEST(test_s_3)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    n1 = snprintf(s1, sizeof(s1), "Hello, %s! My name is %s", "World", "");
    n2 = my_snprintf(s2, sizeof(s2), "Hello, %s! My name is %s", "World", "");

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// Проверка %s несколькими спецификаторами. Вывод пустой
START_TEST(test_s_4)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    n1 = snprintf(s1, sizeof(s1), "%s%s", "", "");
    n2 = my_snprintf(s2, sizeof(s2), "%s%s", "", "");

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// Два модификатора %s стоят слитно
START_TEST(test_s_5)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    n1 = snprintf(s1, sizeof(s1), "%s%s", "a", "b");
    n2 = my_snprintf(s2, sizeof(s2), "%s%s", "a", "b");

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// Проверяем работу ширины поля в спецификаторе %s. Ширина больше длинны аргумента
START_TEST(test_s_6)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    n1 = snprintf(s1, sizeof(s1), "a%20s%s", "b", "c");
    n2 = my_snprintf(s2, sizeof(s2), "a%20s%s", "b", "c");

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// Ширина поля равна длине аргумента
START_TEST(test_s_7)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    n1 = snprintf(s1, sizeof(s1), "a%2s %s", "bc", "def");
    n2 = my_snprintf(s2, sizeof(s2), "a%2s %s", "bc", "def");

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// Ширина поля меньше длины аргумента
START_TEST(test_s_8)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    n1 = snprintf(s1, sizeof(s1), "a%2s %s", "bc", "def");
    n2 = my_snprintf(s2, sizeof(s2), "a%2s %s", "bc", "def");

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// Пустая строка форматирования, аргументы есть
START_TEST(test_s_9)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    char format[] = "";
    n1 = snprintf(s1, sizeof(s1), format, "bc", "def");
    n2 = my_snprintf(s2, sizeof(s2), format, "bc", "def");

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// Нет аргументов, строка форматирования не пустая
START_TEST(test_s_10)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    // char format[] = " ";
    n1 = snprintf(s1, sizeof(s1), "test");
    n2 = my_snprintf(s2, sizeof(s2), "test");

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// Нет аргументов, строка форматирования спецсимвол
START_TEST(test_s_11)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    n1 = snprintf(s1, sizeof(s1), "\n");
    n2 = my_snprintf(s2, sizeof(s2), "\n");

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// Нет аргументов, строка форматирования пустая
// Чтобы запустить тест, нужно билдить без флагов -Wall -Werror
/*START_TEST(test_s_12)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

char format[] = "";
    n1 = snprintf(s1, sizeof(s1), format);
    n2 = my_snprintf(s2, sizeof(s2), format);

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}
END_TEST*/

// Аргумент терминальный символ
START_TEST(test_s_13)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    char format[] = "%s";
    n1 = snprintf(s1, sizeof(s1), format, "\0");
    n2 = my_snprintf(s2, sizeof(s2), format, "\0");

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// Аргумент строка + терминальный символ
START_TEST(test_s_14)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    char format[] = "%s";
    n1 = snprintf(s1, sizeof(s1), format, "abc\0");
    n2 = my_snprintf(s2, sizeof(s2), format, "abc\0");

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// Проверка с шириной поля, выравнивцание по левому краю
START_TEST(test_s_15)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    char format[] = "%-20s";
    n1 = snprintf(s1, sizeof(s1), format, "abc");
    n2 = my_snprintf(s2, sizeof(s2), format, "abc");

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

//  Негативные тесты и смешанные тесты

// Запуск функции с буффером NULL
START_TEST(test_all_1)
{
    int n1, n2;
    n1 = snprintf(NULL, 0, "a%2s %s", "bc", "def");
    n2 = my_snprintf(NULL, 0, "a%2s %s", "bc", "def");

    ck_assert_int_eq(n1, n2);
}

END_TEST

// Проверка спецификатором %%
START_TEST(test_all_2)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    n1 = snprintf(s1, MAX_SIZE, "%%%%");
    n2 = my_snprintf(s2, MAX_SIZE, "%%%%");

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// Запись в память, ограниченную размером 0
START_TEST(test_all_3)
{
    int n1, n2;
    char s1[MAX_SIZE], s2[MAX_SIZE];

    n1 = snprintf(s1, 0, "1234");
    n2 = my_snprintf(s2, 0, "1234");

    ck_assert_int_eq(n1, n2);
    // ck_assert_str_eq(s1, s2); snprintf портит память
}

END_TEST

// Запись в память, ограниченную размером 1 (Пустая строка)
START_TEST(test_all_4)
{
    int n1, n2;
    char s1[MAX_SIZE], s2[MAX_SIZE];
    char format[] = "1234";
    n1 = snprintf(s1, 1, format, ""); // Чтобы убрать ошибку компиляции
    n2 = my_snprintf(s2, 1, format, "");

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// Запись в память, ограниченную размером 2 (1 символ будет выведен на экран)
START_TEST(test_all_5)
{
    int n1, n2;
    char s1[MAX_SIZE], s2[MAX_SIZE];
    char format[] = "2345";
    n1 = snprintf(s1, 2, format, ""); // Чтобы убрать ошибку компиляции
    n2 = my_snprintf(s2, 2, format, "");

    ck_assert_int_eq(n1, n2);
    ck_assert_int_eq(0, strcmp(s1, s2));
}

END_TEST

// Запись в память, ограниченную размером, равным количеству символов строки
START_TEST(test_all_6)
{
    int n1, n2;
    char s1[MAX_SIZE], s2[MAX_SIZE];
    char format[] = "1234";
    n1 = snprintf(s1, 4, format, ""); // Чтобы убрать ошибку компиляции
    n2 = my_snprintf(s2, 4, format, "");

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// Запись в память, ограниченную размером, равным количеству символов строки - 1
START_TEST(test_all_7)
{
    int n1, n2;
    char s1[MAX_SIZE], s2[MAX_SIZE];
    char format[] = "1234";
    n1 = snprintf(s1, 3, format, ""); // Чтобы убрать ошибку компиляции
    n2 = my_snprintf(s2, 3, format, "");

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// Попытка запуска с указателем на NULL и ненулевым count
START_TEST(test_all_8)
{
    int n;
    n = my_snprintf(NULL, MAX_SIZE, "1234");
    ck_assert_int_eq(-1, n);
}

END_TEST

// Тест функции, если ей передать в виде буфера, указателя на динамический массив
START_TEST(test_all_9)
{
    int n1, n2;
    char *s1 = NULL, *s2 = NULL;
    char format[] = "1234";

    s1 = malloc(MAX_SIZE);
    s2 = malloc(MAX_SIZE);
    n1 = snprintf(s1, 3, format, ""); // Чтобы убрать ошибку компиляции
    n2 = my_snprintf(s2, 3, format, "");

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
    free(s1);
    free(s2);
}

END_TEST

/*
// Не работает на маке
// % Вместо спецификатора
START_TEST(test_all_10)
{
    int n1, n2;
    char s1[MAX_SIZE], s2[MAX_SIZE];
    char format[] = "%";

    n1 = snprintf(s1, MAX_SIZE, format, ""); // Чтобы убрать ошибку компиляции
    n2 = my_snprintf(s2, MAX_SIZE, format, "");
    ck_assert_int_lt(n2, 0);
    ck_assert_int_lt(n1, 0);
    ck_assert_str_eq(s1, s2);
}

END_TEST
*/

// Правильный спецификатор
START_TEST(test_all_11)
{
    int n1, n2;
    char s1[MAX_SIZE], s2[MAX_SIZE];
    char format[] = "%1%%%2";

    n1 = snprintf(s1, MAX_SIZE, format, "");
    n2 = my_snprintf(s2, MAX_SIZE, format, "");
    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

/*
Не работает на маке
// Неправильный спецификатор
START_TEST(test_all_12)
{
    int n1, n2;
    char s1[MAX_SIZE], s2[MAX_SIZE];
    char format[] = "%1%%2";

    n1 = snprintf(s1, MAX_SIZE, format, "");
    n2 = my_snprintf(s2, MAX_SIZE, format, "");
    ck_assert_int_lt(n1, 0);
    ck_assert_int_lt(n2, 0);
    ck_assert_str_eq(s1, s2);
}

END_TEST
*/

// Смешанный ввод спецификаторов
START_TEST(test_all_13)
{
    int n1, n2;
    char s1[MAX_SIZE], s2[MAX_SIZE];
    char format[] = "%10d %+-10d %10hd %+-10hd";

    n1 = snprintf(s1, MAX_SIZE, format, 20, 20, 20, 20); // Чтобы убрать ошибку компиляции
    n2 = my_snprintf(s2, MAX_SIZE, format, 20, 20, 20, 20);

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// Аргументы строки, при формате число
START_TEST(test_all_14)
{
    int n1, n2;
    char s1[MAX_SIZE], s2[MAX_SIZE];
    char format[] = "%10d %+-10d %10hd %+-10hd";

    n1 = snprintf(s1, MAX_SIZE, format, "20", "20", "20", "20"); // Чтобы убрать ошибку компиляции
    n2 = my_snprintf(s2, MAX_SIZE, format, "20", "20", "20", "20");

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// Аргументы строки, при формате число
START_TEST(test_all_15)
{
    int n1, n2;
    char s1[MAX_SIZE], s2[MAX_SIZE];
    char format[] = "%s---%+-10dsds%1ssds%s+-10hd";

    n1 = snprintf(s1, MAX_SIZE, format, "test1", 121212, "test2", "test3"); // Чтобы убрать ошибку компиляции
    n2 = my_snprintf(s2, MAX_SIZE, format, "test1", 121212, "test2", "test3");

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// Тестирование %d
// Вывод одного аргумента
START_TEST(test_d_1)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    char format[] = "%d";
    n1 = snprintf(s1, sizeof(s1), format, 1);
    n2 = my_snprintf(s2, sizeof(s2), format, 1);

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

// Вывод некскольких аргументов
START_TEST(test_d_2)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    char format[] = "%d %d";
    n1 = snprintf(s1, sizeof(s1), format, 1, 2);
    n2 = my_snprintf(s2, sizeof(s2), format, 1, 2);

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// Проверка реакции на спецификатор -
START_TEST(test_d_3)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    char format[] = "%d %-d %d";
    n1 = snprintf(s1, sizeof(s1), format, 1, 2, 3);
    n2 = my_snprintf(s2, sizeof(s2), format, 1, 2, 3);

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// Тестирования вывода знака +, при спецификаторе %+d
START_TEST(test_d_4)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    char format[] = "%+d %+d %+d %d %d %d";
    n1 = snprintf(s1, sizeof(s1), format, 0, 123, -3, 0, 123, -3);
    n2 = my_snprintf(s2, sizeof(s2), format, 0, 123, -3, 0, 123, -3);

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// тестирование выравнивания и ширины с использованием длинных чисел
START_TEST(test_d_5)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    char format[] = "%10d %10d %+10d %10d %-10d %10d";
    n1 = snprintf(s1, sizeof(s1), format, 0, 1232323, -3323232, 20090, 12233, -333333);
    n2 = my_snprintf(s2, sizeof(s2), format, 0, 1232323, -3323232, 20090, 12233, -333333);

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// тестирование только ширины поля (случай Ширина > длины числа)
START_TEST(test_d_6)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    // Выравнивнивание справа, выравнивание справа + вывод знака, выравнивание слева, выравнивание слева +выйвод знака
    char format[] = "%10d %+10d %-10d %+-10d";
    n1 = snprintf(s1, sizeof(s1), format, 30, 30, 30, 30);
    n2 = my_snprintf(s2, sizeof(s2), format, 30, 30, 30, 30);

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// тестирование только ширины поля (случай Ширина > длины числа). Отрицательные числа
START_TEST(test_d_7)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    // Выравнивнивание справа, выравнивание справа + вывод знака, выравнивание слева, выравнивание слева +выйвод знака
    char format[] = "%10d %+10d %-10d %+-10d";
    n1 = snprintf(s1, sizeof(s1), format, -30, -30, -30, -30);
    n2 = my_snprintf(s2, sizeof(s2), format, -30, -30, -30, -30);

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// тестирование только ширины поля (случай Ширина = длине числа)
START_TEST(test_d_8)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    char format[] = "%2d %+2d %3d %+3d";
    n1 = snprintf(s1, sizeof(s1), format, 30, 30, -30, -30);
    n2 = my_snprintf(s2, sizeof(s2), format, 30, 30, -30, -30);

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// тестирование только ширины поля (случай Ширина < длине числа)
START_TEST(test_d_9)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    char format[] = "%1d %+1d %+-1d %+-1d";
    n1 = snprintf(s1, sizeof(s1), format, 30, 30, -30, -30);
    n2 = my_snprintf(s2, sizeof(s2), format, 30, 30, -30, -30);

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// Переполнения инта (с двух сторон)
START_TEST(test_d_10)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    char format[] = "%d %d %d %d";
    n1 = snprintf(s1, sizeof(s1), format, INT_MIN, INT_MAX, INT64_MIN, INT64_MAX);
    n2 = my_snprintf(s2, sizeof(s2), format, INT_MIN, INT_MAX, INT64_MIN, INT64_MAX);

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// Манки тест
START_TEST(test_d_11)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    char format[] = "%+-+----+++20d %--10d %+22d %-----d";
    n1 = snprintf(s1, sizeof(s1), format, INT_MIN, INT_MAX, INT64_MIN, INT64_MAX);
    n2 = my_snprintf(s2, sizeof(s2), format, INT_MIN, INT_MAX, INT64_MIN, INT64_MAX);

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// много + и - в спецификаторе
START_TEST(test_d_12)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    char format[] = "%+-+-+-----+++++++d";
    n1 = snprintf(s1, sizeof(s1), format, 12345678);
    n2 = my_snprintf(s2, sizeof(s2), format, 12345678);

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

// Тестирование %hd
// Вывод одного аргумента
START_TEST(test_hd_1)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    char format[] = "%hd";
    n1 = snprintf(s1, sizeof(s1), format, 1);
    n2 = my_snprintf(s2, sizeof(s2), format, 1);

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

// Вывод некскольких аргументов
START_TEST(test_hd_2)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    char format[] = "%hd %hd";
    n1 = snprintf(s1, sizeof(s1), format, 1, 2);
    n2 = my_snprintf(s2, sizeof(s2), format, 1, 2);

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// Проверка реакции на спецификатор -
START_TEST(test_hd_3)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    char format[] = "%hd %-hd %hd";
    n1 = snprintf(s1, sizeof(s1), format, 1, 2, 3);
    n2 = my_snprintf(s2, sizeof(s2), format, 1, 2, 3);

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// Тестирования вывода знака +, при спецификаторе %+hd
START_TEST(test_hd_4)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    char format[] = "%+hd %+hd %+hd %hd %hd %hd";
    n1 = snprintf(s1, sizeof(s1), format, 0, 123, -3, 0, 123, -3);
    n2 = my_snprintf(s2, sizeof(s2), format, 0, 123, -3, 0, 123, -3);

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// тестирование выравнивания и ширины с использованием длинных чисел
START_TEST(test_hd_5)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    char format[] = "%10hd %10hd %+10hd %10hd %-10hd %10hd";
    n1 = snprintf(s1, sizeof(s1), format, 0, 1232323, -3323232, 20090, 12233, -333333);
    n2 = my_snprintf(s2, sizeof(s2), format, 0, 1232323, -3323232, 20090, 12233, -333333);

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// тестирование только ширины поля (случай Ширина > длины числа)
START_TEST(test_hd_6)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    // Выравнивнивание справа, выравнивание справа + вывод знака, выравнивание слева, выравнивание слева +выйвод знака
    char format[] = "%10hd %+10hd %-10hd %+-10hd";
    n1 = snprintf(s1, sizeof(s1), format, 30, 30, 30, 30);
    n2 = my_snprintf(s2, sizeof(s2), format, 30, 30, 30, 30);

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// тестирование только ширины поля (случай Ширина > длины числа). Отрицательные числа
START_TEST(test_hd_7)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    // Выравнивнивание справа, выравнивание справа + вывод знака, выравнивание слева, выравнивание слева +выйвод знака
    char format[] = "%10hd %+10hd %-10hd %+-10hd";
    n1 = snprintf(s1, sizeof(s1), format, -30, -30, -30, -30);
    n2 = my_snprintf(s2, sizeof(s2), format, -30, -30, -30, -30);

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// тестирование только ширины поля (случай Ширина = длине числа)
START_TEST(test_hd_8)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    char format[] = "%2hd %+2hd %3hd %+3hd";
    n1 = snprintf(s1, sizeof(s1), format, 30, 30, -30, -30);
    n2 = my_snprintf(s2, sizeof(s2), format, 30, 30, -30, -30);

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// тестирование только ширины поля (случай Ширина < длине числа)
START_TEST(test_hd_9)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    char format[] = "%1hd %+1hd %+-1hd %+-1hd";
    n1 = snprintf(s1, sizeof(s1), format, 30, 30, -30, -30);
    n2 = my_snprintf(s2, sizeof(s2), format, 30, 30, -30, -30);

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// Переполнения инта (с двух сторон)
START_TEST(test_hd_10)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    char format[] = "%hd %hd %hd %hd";
    n1 = snprintf(s1, sizeof(s1), format, INT_MIN, INT_MAX, SHRT_MIN, SHRT_MAX);
    n2 = my_snprintf(s2, sizeof(s2), format, INT_MIN, INT_MAX, SHRT_MIN, SHRT_MAX);

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// Манки тест
START_TEST(test_hd_11)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    char format[] = "%+-+----+++10hd %--2hd %+10hd %-----hd";
    n1 = snprintf(s1, sizeof(s1), format, INT_MIN, INT_MAX, SHRT_MIN, SHRT_MAX);
    n2 = my_snprintf(s2, sizeof(s2), format, INT_MIN, INT_MAX, SHRT_MIN, SHRT_MAX);

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

// много + и - в спецификаторе
START_TEST(test_hd_12)
{
    int n1, n2;
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    char format[] = "%+-+-+-----+++++++hd";
    n1 = snprintf(s1, sizeof(s1), format, 12345678);
    n2 = my_snprintf(s2, sizeof(s2), format, 12345678);

    ck_assert_int_eq(n1, n2);
    ck_assert_str_eq(s1, s2);
}

END_TEST

Suite *get_my_snprintf_suite(void)
{
    Suite *suite = suite_create("Test");

    TCase *test_s = tcase_create("s");
    if (1)
    {
        tcase_add_test(test_s, test_s_1);
        tcase_add_test(test_s, test_s_2);
        tcase_add_test(test_s, test_s_3);
        tcase_add_test(test_s, test_s_4);
        tcase_add_test(test_s, test_s_5);
        tcase_add_test(test_s, test_s_5);
        tcase_add_test(test_s, test_s_6);
        tcase_add_test(test_s, test_s_7);
        tcase_add_test(test_s, test_s_8);
        tcase_add_test(test_s, test_s_9);
        tcase_add_test(test_s, test_s_10);
        tcase_add_test(test_s, test_s_11);
        // tcase_add_test(test_s, test_s_12);
        tcase_add_test(test_s, test_s_13);
        tcase_add_test(test_s, test_s_14);
        tcase_add_test(test_s, test_s_15);
    }

    TCase *test_all = tcase_create("all");
    if (1)
    {
        tcase_add_test(test_all, test_all_1);
        tcase_add_test(test_all, test_all_2);
        tcase_add_test(test_all, test_all_3);
        tcase_add_test(test_all, test_all_4);
        tcase_add_test(test_all, test_all_5);
        tcase_add_test(test_all, test_all_6);
        tcase_add_test(test_all, test_all_7);
        tcase_add_test(test_all, test_all_8);
        tcase_add_test(test_all, test_all_9);
        // tcase_add_test(test_all, test_all_10);
        tcase_add_test(test_all, test_all_11);
        // tcase_add_test(test_all, test_all_12);
        tcase_add_test(test_all, test_all_13);
        tcase_add_test(test_all, test_all_14);
        tcase_add_test(test_all, test_all_15);
    }

    TCase *test_d = tcase_create("d");
    if (1)
    {
        tcase_add_test(test_d, test_d_1);
        tcase_add_test(test_d, test_d_2);
        tcase_add_test(test_d, test_d_3);
        tcase_add_test(test_d, test_d_4);
        tcase_add_test(test_d, test_d_5);
        tcase_add_test(test_d, test_d_6);
        tcase_add_test(test_d, test_d_7);
        tcase_add_test(test_d, test_d_8);
        tcase_add_test(test_d, test_d_9);
        tcase_add_test(test_d, test_d_10);
        tcase_add_test(test_d, test_d_11);
        tcase_add_test(test_d, test_d_12);
    }

    TCase *test_hd = tcase_create("hd");
    if (1)
    {
        tcase_add_test(test_hd, test_hd_1);
        tcase_add_test(test_hd, test_hd_2);
        tcase_add_test(test_hd, test_hd_3);
        tcase_add_test(test_hd, test_hd_4);
        tcase_add_test(test_hd, test_hd_5);
        tcase_add_test(test_hd, test_hd_6);
        tcase_add_test(test_hd, test_hd_7);
        tcase_add_test(test_hd, test_hd_8);
        tcase_add_test(test_hd, test_hd_9);
        tcase_add_test(test_hd, test_hd_10);
        tcase_add_test(test_hd, test_hd_11);
        tcase_add_test(test_hd, test_hd_12);
    }
    suite_add_tcase(suite, test_s);
    suite_add_tcase(suite, test_all);
    suite_add_tcase(suite, test_d);
    suite_add_tcase(suite, test_hd);

    return suite;
}
