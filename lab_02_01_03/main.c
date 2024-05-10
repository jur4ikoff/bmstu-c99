#include <stdio.h>
#include <math.h>
#define WRONG_INPUT 1
#define WRONG_ARRAY_LEN 2
#define ONLY_NEGATIVE 3
#define ARRAY_LEN 10

// Подсчет среднего геометрического
float calculate_average_geometric(int array[], int n)
{
    int count = 0, composition = 1;
    for (int i = 1; i <= n; i++)
    {
        int el = array[i];
        if (el > 0)
        {
            count++;
            composition *= el;
        }
    }
    // вычисление степени
    float degree = 1.0f / count;
    float res = powf(composition, degree);

    return res;
}
// Главная функция
int main(void)
{
    // Ввод
    int array_len;
    printf("Введите длину массива: ");
    if (scanf("%d", &array_len) != 1)
    {
        printf("WRONG INPUT\n");
        return WRONG_INPUT;
    }
    // Обработка результатов ввода
    if (array_len > 10 || array_len < 1)
    {
        printf("len must be less ten\n");
        return WRONG_ARRAY_LEN;
    }

    printf("Введите элементы списка по одному: \n");
    int array[ARRAY_LEN];
    int count = 0;
    // Ввод элементво списка
    for (int i = 1; i <= array_len; i++)
    {
        int input_el;
        if (scanf("%d", &input_el) != 1)
        {
            // Обработка ошибок
            printf("WRONG INPUT\n");
            return WRONG_INPUT;
        }
        // Получаем количество положительных элементов
        if (input_el > 0)
            count++;
        array[i] = input_el;
    }
    if (count == 0)
    {
        printf("No positive numbers \n");
        return ONLY_NEGATIVE;
    }
    // Получаем значение
    float res = calculate_average_geometric(array, array_len);
    printf("%f \n", res);
}
