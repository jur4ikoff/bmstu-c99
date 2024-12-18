// #define _GNU_SOURCE

#include "io.h"
#include "array_operations.h"
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
static int input_name(product_t *product, FILE *file)
{
    ssize_t read = 0;
    size_t len = 0;

    if ((read = getline(&product->name, &len, file)) == -1)
        return ERR_NAME;

    char *newline = strchr(product->name, '\n');
    if (!newline)
        return ERR_OVERFLOW;
    *newline = 0;

    return ERR_OK;
}

/**
 * @brief Функция считает количество структур в файле
 * @param file Указатель на файловую переменую
 *  * @param count Указатель на количество структур
 * @return Код возврата
 */
int count_structs_in_file(FILE *file, size_t *count)
{
    *count = 0;
    char buffer[MAX_STRING_LEN];
    float buffer_1, buffer_2;
    int rc = ERR_OK;
    while (rc == ERR_OK)
    {
        if (!fscanf(file, "%s", buffer))
            return ERR_NAME;
        if (fscanf(file, "%f %f", &buffer_1, &buffer_2) != 2)
            return ERR_NUMBER;
        fgetc(file);

        (*count)++;
        if (feof(file))
        {
            rewind(file);
            return ERR_OK;
        }
    }

    return ERR_STRUCT;
}

/**
 * @brief Функция выводит на экран массив продуктов
 * @param products Массив продуктов
 *  * @param count количество элементов массива
 * @return Код возврата
 */
void print_products(product_t products[], size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        printf("%s\n%f\n%f\n", products[i].name, products[i].weight, products[i].volume);
    }
}

/**
 * @brief Функция читает одну структуру
 * @param file Файловый указатель
 * @param products Массив продуктов
 * @param index Индекс элемента в массиве
 * @return Код возврата
 */
static int read_struct(FILE *file, product_t products[], size_t index)
{
    int rc = ERR_OK;
    products[index].name = NULL;
    if ((rc = input_name(&products[index], file)) != ERR_OK)
        return rc;

    if (fscanf(file, "%f %f", &products[index].weight, &products[index].volume) != 2)
        return ERR_NUMBER;
    if (products[index].weight - 0 <= EPS || products[index].volume - 0 <= EPS)
        return ERR_NUMBER;

    fgetc(file);

    return rc;
}

/**
 * @brief Функция читает файл со структурами и записывает его в массив.
 * @param file Файловый указатель
 * @param products Массив сруктур
 * @param count Указатель на количество
 * @return Код возврата
 */
int read_structs_from_file(FILE *file, product_t *products, size_t *count)
{
    int rc = ERR_OK;
    for (size_t i = 0; i < *count; i++)
    {
        if ((rc = read_struct(file, products, i)) != ERR_OK)
        {
            *count = i + 1;
            return rc;
        }

        if (feof(file))
            return ERR_OK;
    }

    return ERR_STRUCT;
}

// Вывод сообщения об ошибке
void print_error_message(int arg)
{
#if IS_OUTPUT
    if (arg == ERR_NAME)
        printf("Error in the name of product\n");
    else if (arg == ERR_NUMBER)
        printf("Error in weight or volume of product\n");
    else if (arg == ERR_OVERFLOW)
        printf("Error, overflow\n");
    else if (arg == ERR_FILE)
        printf("Error with input file\n");
    else if (arg == ERR_ARGS_COUNT)
        printf("Error, wrong args count\n");
    else if (arg == ERR_EMPTY_OUTPUT)
        printf("Error, empty output\n");
    else if (arg == ERR_EMPTY_INPUT)
        printf("Error, empty input\n");
    else if (arg == ERR_STRUCT)
        printf("Error, while reading struct\n");
    else if (arg == ERR_MEMORY_ALLOCATION)
        printf("Ошибка при выделении памяти\n");
#else
    if (arg)
        return;
#endif
}

void free_products(product_t *products, const size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        free(products[i].name);
    }
    free(products);
}

void print_products_by_index(product_t *products, size_t *indexes, size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        if (indexes[i])
            printf("%s\n%f\n%f\n", products[i].name, products[i].weight, products[i].volume);
    }
}
