#include "io.h"

// Функция считывает имя *name продукта из файла *file
int input_name(char *name, FILE *file)
{
    if (!fgets(name, MAX_STRING_LEN, file))
        return ERR_NAME;

    char *newline = strchr(name, '\n');
    if (!newline)
        return ERR_OVERFLOW;
    *newline = '\0';

    if (strlen(name) == 0)
        return ERR_NAME;
    return ERR_OK;
}

// Выводит на экран массив продуктов
void print_products(product_struct products[], size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        printf("%s\n%f\n%f\n", products[i].name, products[i].weight, products[i].volume);
    }
}

int read_struct(FILE *file, product_struct products[], size_t count)
{
    int rc = ERR_OK;
    if ((rc = input_name(products[count].name, file)) != ERR_OK)
        return rc;
    if (fscanf(file, "%f %f", &products[count].weight, &products[count].volume) != 2)
        return ERR_NUMBER;
    if (products[count].weight - 0 <= EPS || products[count].volume - 0 <= EPS)
        return ERR_NUMBER;
    fgetc(file);

    return rc;
}

// Читает файл со структурами и записывает его в массив.
int read_structs_from_file(FILE *file, product_struct products[], size_t *count)
{
    *count = 0;
    int rc = ERR_OK;
    do
    {
        if ((rc = read_struct(file, products, *count)) != ERR_OK)
            return rc;

        (*count)++;
        if (feof(file))
            return ERR_OK;

        // Проверка на переполнения массива структур
        if (*count == MAX_PRODUCTS)
            return ERR_OVERFLOW;
    } while (rc == 0);

    return ERR_STRUCT;
}

// Вывод сообщения об ошибке
void print_error_message(int arg)
{
#if 0
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
#else
    if (arg)
        return;
#endif
}
