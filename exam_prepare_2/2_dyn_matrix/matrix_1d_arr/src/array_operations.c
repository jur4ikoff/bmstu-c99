#include "array_operations.h"
#include "errors.h"
#include <string.h>

/**
 * @brief // Функция ищет индексы структур, в которых поле name начинается с подстроки *token
 * @param products Массив сруктур
 * @param count Количество элементов массива
 * @param token Строка поиска
 * @param indexes массив, в который будет записывать результат работы
 * @return Код возврата
 */
int find_same_beginning_string(product_t products[], size_t count, char *token, size_t *indexes)
{
    if (count == 0)
        return ERR_EMPTY_INPUT;
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
            indexes[i] = 1;
            print_count++;
        }
    }
    if (print_count == 0)
        return ERR_EMPTY_OUTPUT;

    return ERR_OK;
}

/**
 * @brief // Функция сортирует массив стрктур по возрастанию по плотности. Сортировка методом Insection sort
 * @param products Массив сруктур
 * @param count Количество элементов массива
 */
void sort_products_by_density(product_t products[], size_t count)
{
    if (count < 1)
        return;

    for (size_t i = 1; i < count; i++)
    {
        product_t key = products[i];
        int j = (int)i - 1;

        while (j >= 0 && (key.weight / key.volume) < (products[j].weight / products[j].volume))
        {
            products[j + 1] = products[j];
            j -= 1;
        }

        products[j + 1] = key;
    }
}
