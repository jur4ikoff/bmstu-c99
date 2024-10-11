#include "profiling.h"
#include <time.h>
#include "array_operations.h"
#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include <math.h>
#include <string.h>

// Генерация массива случайных чисел
static void generate_random_array(int array[], size_t len)
{
    srand(time(0));
    for (size_t i = 0; i < len; i++)
    {
        array[i] = rand() % 100;
        if (rand() % 2 == 1)
            array[i] *= -1;
    }
}

static void generate_sort_array(int array[], size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        array[i] = i;
    }
}

static void generate_reverse_sort_array(int array[], size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        array[i] = len - i;
    }
}

static double sum_time(double time_array[], size_t count)
{
    double sum = 0;
    for (size_t i = 0; i < count; i++)
    {
        sum += time_array[i];
    }
    return sum;
}

// Подсчет RSE
static int calc_rse(double time_array[], size_t count, double *rse)
{
    double t_avg, dispersion = 0;
    if (count <= 1)
        return -1;
    t_avg = sum_time(time_array, count) / count;

    for (size_t i = 0; i < count; i++)
    {
        dispersion += pow((time_array[i] - t_avg), 2);
    }
    dispersion /= (count - 1);
    double standard_deviation = sqrt(dispersion);
    double std_error = standard_deviation / sqrt(count);
    *rse = std_error * 100 / t_avg;
    return ERR_OK;
}

static double mean(double array[], size_t count)
{
    double mean = 0;
    for (size_t i = 0; i < count; i++)
    {
        mean += (array[i] - mean) / (i + 1);
        // printf("%f\n", mean);
    }
    return mean;
}

int run_profiling(int mode)
{
    // char default_filename[] = "./../calc_exex_time/random_arr.csv";
    char default_filename[MAX_PART_LEN];
    if (mode == 1)
        strcpy(default_filename, "./../calc_exec_time/random_arr.csv");
    else if (mode == 2)
        strcpy(default_filename, "./../calc_exec_time/sort_arr.csv");
    else
        strcpy(default_filename, "./../calc_exec_time/reverse_sort_arr.csv");

    FILE *file = fopen(default_filename, "w");
    fprintf(file, "size;qsort;mysort;bublesort\n");
    if (file == NULL)
        return ERR_FILENAME;

    struct timespec start_time, end_time;
    double cpu_time_qsort, cpu_time_my_sort, cpu_time_buble_sort, time;
    size_t size_cur = 1, itteration_count = 0;
    int number_arr[MAX_SIZE];
    double time_array[MAX_ITERATIONS], rse = 100;

    while (size_cur <= MAX_SIZE)
    {
        itteration_count = 0;
        rse = 100;
        // Прогон qsort
        while ((itteration_count < MAX_ITERATIONS) && (rse > 1 || itteration_count < MIN_ITERATIONS))
        {
            if (mode == 1)
                generate_random_array(number_arr, size_cur); // Генерация рандомного массива
            else if (mode == 2)
                generate_sort_array(number_arr, size_cur);
            else
                generate_reverse_sort_array(number_arr, size_cur);

            clock_gettime(CLOCK_REALTIME, &start_time);
            qsort(&number_arr, size_cur, sizeof(int), compare);
            clock_gettime(CLOCK_REALTIME, &end_time);

            time = (double)((end_time.tv_sec - start_time.tv_sec) * 1e9 + (end_time.tv_nsec - start_time.tv_nsec));

            time_array[itteration_count] = time;
            itteration_count++;
            calc_rse(time_array, itteration_count, &rse);
        }
        cpu_time_qsort = mean(time_array, itteration_count);

        // Запуск my_sort
        rse = 100;
        itteration_count = 0;
        while ((itteration_count < MAX_ITERATIONS) && (rse > 1 || itteration_count < MIN_ITERATIONS))
        {
            if (mode == 1)
                generate_random_array(number_arr, size_cur); // Генерация рандомного массива
            else if (mode == 2)
                generate_sort_array(number_arr, size_cur);
            else
                generate_reverse_sort_array(number_arr, size_cur);

            clock_gettime(CLOCK_REALTIME, &start_time);
            my_sort(&number_arr, size_cur, sizeof(int), compare);
            clock_gettime(CLOCK_REALTIME, &end_time);

            time = (double)((end_time.tv_sec - start_time.tv_sec) * 1e9 + (end_time.tv_nsec - start_time.tv_nsec));
            time_array[itteration_count] = time;
            itteration_count++;
            calc_rse(time_array, itteration_count, &rse);
            // printf("%.2f\n", rse);
        }
        cpu_time_my_sort = mean(time_array, itteration_count);

        rse = 100;
        itteration_count = 0;
        while ((itteration_count < MAX_ITERATIONS) && (rse > 1 || itteration_count < MIN_ITERATIONS))
        {
            if (mode == 1)
                generate_random_array(number_arr, size_cur); // Генерация рандомного массива
            else if (mode == 2)
                generate_sort_array(number_arr, size_cur);
            else
                generate_reverse_sort_array(number_arr, size_cur);

            clock_gettime(CLOCK_REALTIME, &start_time);
            buble_sort(&number_arr, size_cur, sizeof(int), compare);
            clock_gettime(CLOCK_REALTIME, &end_time);

            time = (double)((end_time.tv_sec - start_time.tv_sec) * 1e9 + (end_time.tv_nsec - start_time.tv_nsec));
            time_array[itteration_count] = time;
            itteration_count++;
            calc_rse(time_array, itteration_count, &rse);
            // printf("%.2f\n", rse);
        }
        cpu_time_buble_sort = mean(time_array, itteration_count);

        fprintf(file, "%zu;%.4f;%.4f;%.4f\n", size_cur, cpu_time_qsort, cpu_time_my_sort, cpu_time_buble_sort);
        size_cur += INCR_COEF;
    }
    fclose(file);
    return ERR_OK;
}
