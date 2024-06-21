#include "solve.h"
#include "constants.h"

// Функция считает сумму чисел в файле и их количество
int calculate_sum(FILE *file, int *count, double *sum, double *qsum)
{
    double num;
    *count = 0;
    *sum = 0;
    *qsum = 0;

    while (fscanf(file, "%lf", &num) == 1)
    {
        *sum += num;
        *qsum += pow(num, 2);
        (*count)++;
    }

    if (feof(file) == 0)
        return ERR_WRONG_INPUT;

    if (count == 0)
        return ERR_WRONG_INPUT;

    return ERR_OK;
}

// Считаем дисперсию
int calculate_dispersion(FILE *file, int *count, double *dispersion, double mean)
{
    // Спросить нужно ли проверять на символы файлы
    double num;
    while (fscanf(file, "%lf", &num) == 1)
    {
        *dispersion += pow(num - mean, 2);
        (*count)++;
    }
    return ERR_OK;
}

// Проверка на правило трех сигм
int check_rule_of_three_sigma(FILE *file, double mean, double sum, double qsum, size_t count)
{
    double num;
    size_t n = 0;
    double sigma = sqrt((count * qsum - (sum * sum)) / (count * count));

    if (fabs(sigma) < 1e-7)
        return 0;

    // printf("count %zu, mean %lf sigma %lf\n", count, mean, sigma);
    while (fscanf(file, "%lf", &num) == 1)
    {
        if (fabs(num - mean) > 3 * sigma)
            n++;
    }
    // printf("count %zu, n %zu\n", count, n);
    if (((float)n / count) < (float)0.9973)
    {
        return 1;
    }
    else
        return 0;
}
