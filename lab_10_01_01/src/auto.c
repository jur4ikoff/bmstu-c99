#define _GNU_SOURCE

#include "auto.h"
#include "constants.h"
#include "errors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Функция считывает имя структуры из файла
 * @param product Указатель на структуры
 * @param file Указатель на файловую переменую
 * @return Код возврата
 */
int input_string(char **string, FILE *file)
{
    ssize_t read = 0;
    size_t len = 0;

    if ((read = getline(string, &len, file)) == -1)
        return ERR_STRING;

    if (read > MAX_NAME_LEN)
        return ERR_STRING;

    char *newline = strchr(*string, '\n');
    if (!newline)
        return ERR_STRING;
    *newline = 0;

    if (strlen(*string) == 0)
        return ERR_STRING;

    return ERR_OK;
}

/**
 * @brief Сравненение машин по параметрам цена и год
 * @param a Первый элемент
 * @param b Второй элемент
 * @return 0 - Если а = b
 **/
int comparator_by_price_and_year(const void *a, const void *b)
{
    const auto_t *l = (auto_t *)a;
    const auto_t *r = (auto_t *)b;
    if (l->price == r->price)
    {
        return l->year - r->year;
    }
    return l->price - r->price;
}

/**
 * @brief Сравненение машин по параметрам  год
 * @param a Первый элемент
 * @param b Второй элемент
 * @return 0 - Если а = b, иначе 1
 **/
int comparator_by_year(const void *first, const void *second)
{
    const auto_t *a = (auto_t *)first;
    const auto_t *b = (auto_t *)second;
    return a->year - b->year;
}

/**
 * @brief Компаратор для
 * @param a Первый элемент
 * @param b Второй элемент
 * @return 0 - Если а = b
 **/
int comparator_by_price(const void *first, const void *second)
{
    const auto_t *a = (auto_t *)first;
    const auto_t *b = (auto_t *)second;
    return (a->price - b->price);
}

// Вывод информации об авто
void print_auto(void *auto_info)
{
    auto_t *auto_data = (auto_t *)auto_info;
    printf("Model: %s  Year: %d  Price: %lld\n", auto_data->model_name, auto_data->year, auto_data->price);
}

// Запись информации об одном авто в файл
void write_auto(auto_t *auto_data, FILE *file)
{
    if (!file)
        return;
    fprintf(file, "%s\n%d\n%lld\n", auto_data->model_name, auto_data->year, auto_data->price);
}

/**
 * @brief Функция для получения данных об автомобиле
 * @param name Указатель на название автомобиля, уже выделенная память
 * @param year Год выпуска
 * @param price Цена
 * @param need_masage Флаг - нужен ли вывод сообщения
 * @return Код возврата
 */
int input_auto_data(char **name, int *year, long long *price, int need_message)
{
    int rc = ERR_OK;

    if (need_message)
        printf("Введите строку: ");
    if ((rc = input_string(name, stdin)) != ERR_OK)
        return rc;

    if (need_message)
        printf("Введите год и цену через пробел: ");
    if (scanf("%d %lld", year, price) != 2)
    {
        return ERR_NUMBER;
    }
    return rc;
}

/**
 * @brief Функция для создания структуры об автомобиле
 * @param name Указатель на название автомобиля, уже выделенная память
 * @param year Год выпуска
 * @param price Цена
 * @return Указатель на структуруz
 */
auto_t *create_auto(char *name, int year, long long price)
{
    auto_t *auto_data = NULL;
    auto_data = malloc(sizeof(auto_t));

    if (!auto_data)
        return auto_data;

    auto_data->model_name = strdup(name);
    auto_data->year = year;
    auto_data->price = price;
    return auto_data;
}

void free_auto(auto_t *auto_data)
{
    if (auto_data)
        free(auto_data->model_name);
    free(auto_data);
}
