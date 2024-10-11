#include "functions.h"

// Функция ищет структуру продукта, в которой поле name начинается с подстроки *token
int find_same_beginning_string(product_struct products[], size_t count, char *token)
{
    int token_len = strlen(token);
    int print_count = 0;
    for (size_t i = 0; i < count; i++)
    {
        // Копируем в буффер поле name. Длина ограничивает длиной *token
        char buffer[MAX_STRING_LEN + 1];
        strncpy(buffer, products[i].name, token_len);
        buffer[token_len] = '\0';
        
        if (strcmp(buffer, token) == 0)
        {
            printf("%s\n%f\n%f\n", products[i].name, products[i].weight, products[i].volume);
            print_count++;
        }
    }
    if (print_count == 0)
        return ERR_EMPTY_OUTPUT;

    return ERR_OK;
}

// Функция сортирует массив стрктур по возрастанию по ключу плотность.
// Insection sort
void sort_products_by_density(product_struct products[], size_t count)
{
    for (size_t i = 1; i < count; i++)
    {
        product_struct key = products[i];
        int j = (int)i - 1;

        while (j >= 0 && (key.weight / key.volume) < (products[j].weight / products[j].volume))
        {
            products[j + 1] = products[j];
            j -= 1;
        }

        products[j + 1] = key;
    }
}
