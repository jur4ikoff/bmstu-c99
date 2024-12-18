#ifndef AUTO_H__
#define AUTO_H__

#include <stdio.h>

// Структура для записи авто
typedef struct auto_t_
{
    char *model_name; // название модели
    int year;         // год выпуска
    long long price;  // стоимость
} auto_t;

int input_string(char **name, FILE *file);
int comparator_by_price_and_year(const void *a, const void *b);
int comparator_by_price(const void *first, const void *second);
int comparator_by_year(const void *a, const void *b);
void print_auto(void *auto_info);
int input_auto_data(char **name, int *year, long long *price, int need_message);
void free_auto(auto_t *auto_data);
auto_t *create_auto(char *name, int year, long long price);
void write_auto(auto_t *auto_data, FILE *file);
#endif
