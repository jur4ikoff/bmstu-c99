#include "array_operations.h"
#include "constants.h"
#include "errors.h"
#include "io.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    // Инициализация переменных
    int rc = ERR_OK;
    size_t count = 0;
    product_t *products = NULL;
    size_t *indexes = NULL;

    // Обработка аргументов
    if (argc <= 1 || argc > 3)
    {
        rc = ERR_ARGS_COUNT;
        goto full_exit;
    }

    // Обработка первого аргумента, открытие файла
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        rc = ERR_FILE;
        goto full_exit;
    }

    // Подсчет количества элементов в файле
    if ((rc = count_structs_in_file(file, &count)) != ERR_OK)
    {
        fclose(file);
        print_error_message(rc);
        return rc;
    }

    // Выделение памяти под массив структур
    products = malloc(count * sizeof(product_t));
    if (!products)
    {
        fclose(file);
        rc = ERR_MEMORY_ALLOCATION;
        print_error_message(rc);
        return rc;
    }

    // Чтение из файла со структурами в массив
    if ((rc = read_structs_from_file(file, products, &count)) != ERR_OK)
    {
        fclose(file);
        goto full_exit;
    }
    fclose(file);

    if (argc == 3)
    {
        // Проверка на слишком длинную строку в аргументне
        if (strlen(argv[2]) > MAX_STRING_LEN)
        {
            rc = ERR_OVERFLOW;
            goto full_exit;
        }

        if (strcmp(argv[2], "ALL") == 0)
        {
            // Если флаг == ALL, происходит вывод всех продуктов
            print_products(products, count);
        }
        else
        {
            // Если флаг не ALL, происходит поиск продуктов с таким же токеном
            // Выделение памяти под динамический массив индексов
            indexes = calloc(count, sizeof(size_t));
            if (indexes == NULL)
            {
                rc = ERR_MEMORY_ALLOCATION;
                print_error_message(rc);
                return rc;
            }

            // Ищет продукты, начинающиеся с такой же подстроки и записываем их индексы
            if ((rc = find_same_beginning_string(products, count, argv[2], indexes)) != ERR_OK)
                goto full_exit;

            // Вывод из массива структур по индексам
            print_products_by_index(products, indexes, count);
        }
    }
    else
    {
        // Сортировка продуктов по возрастанию
        sort_products_by_density(products, count);
        print_products(products, count);
    }

    full_exit:
    if (1)
    {
        // Освобождение памяти
        free_products(products, count);
        free(indexes);
    }
    print_error_message(rc);
    return rc;
}
