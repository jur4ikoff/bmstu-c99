#include "constants.h"
#include "io.h"
#include "functions.h"

int main(int argc, char **argv)
{
    int rc = ERR_OK;
    product_struct products[MAX_PRODUCTS];
    size_t count = 0;

    // Обработка аргументов
    if (argc <= 1 || argc > 3)
    {
        print_error_message(ERR_ARGS_COUNT);
        return ERR_ARGS_COUNT;
    }

    // Обработка первого аргумента, открытие файла
    FILE *filename = fopen(argv[1], "r");
    if (!filename)
    {
        print_error_message(ERR_FILE);
        return ERR_FILE;
    }

    // Чтение из файла со структурами в массив
    if ((rc = read_structs_from_file(filename, products, &count)) != ERR_OK)
    {
        print_error_message(rc);
        return rc;
    }

    if (argc == 3)
    {
        // Проверка на слишком длинную строку в аргументне
        if (strlen(argv[2]) > MAX_STRING_LEN)
        {
            print_error_message(ERR_OVERFLOW);
            return ERR_OVERFLOW;
        }

        if (strcmp(argv[2], "ALL") == 0)
        {
            // Если флаг == ALL, происходит вывод всех продуктов
            print_products(products, count);
        }
        else
        {
            // Ищет продукты, начинающиеся с такой же подстроки
            if ((rc = find_same_beginning_string(products, count, argv[2])) != ERR_OK)
            {
                print_error_message(rc);
                return rc;
            }
        }
    }
    else
    {
        // Сортировка продуктов по возрастанию
        sort_products_by_density(products, count);
        print_products(products, count);
    }
    return rc;
}
