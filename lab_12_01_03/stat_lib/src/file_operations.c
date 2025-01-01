#include "file_operations.h"
#include <stdio.h>
#include "errors.h"
#include "constants.h"

/**
 * @brief  Функция считает количество элементов в файле
 * @param filename Путь к файлу
 * @param size Указатель на количество элементов
 * @return Код ошибки
 * */
int file_elements_count(char *filename, size_t *size)
{
    *size = 0;
    FILE *file = fopen(filename, "r");

    if (file == NULL)
        return ERR_FILENAME;

    int buffer;
    while (fscanf(file, "%d", &buffer) == 1)
    {
        (*size)++;
    }
    if (feof(file) == 0)
        return ERR_READ;

    fclose(file);
    return ERR_OK;
}

/**
 * @brief Фцнкция записывает массив целых чисел в файл
 * @param filename Путь до файла
 * @param start Указатель на первый элемент массива
 * @param end Указатель на последний элемент массива 
 */
int file_write_int(char *filename, int *start, int *end)
{
    // Проверки
    FILE *file = fopen(filename, "w");
    if (file == NULL)
        return ERR_FILENAME;

    if (start == NULL)
        return ERR_ALLOCATION;

    // Запись
    for (int *cur = start; cur < end; cur++)
    {
        if (cur + 1 < end)
            fprintf(file, "%d ", *cur);
        else
            fprintf(file, "%d\n", *cur);
    }

    fclose(file);
    return ERR_OK;
}
