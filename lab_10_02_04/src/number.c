#include "number.h"
#include "errors.h"
#include "list.h"
#include <math.h>
#include <stdlib.h>

int convert_string_to_int(char *string, long long *number)
{
    int rc = ERR_OK;
    char *endptr;
    *number = strtoll(string, &endptr, 10); // 10 - основание системы счисления (десятичная)

    // Проверяем на ошибки
    if (*endptr != '\0')
        return ERR_NUMBER;

    return rc;
}

/**
 * @brief Функция возвращает массив простых чисел от 0 до n;
 * @param n
 * @param count Указатель на количество простых чисел из диапазона
 */
static int *find_prime_numbers(long long n, size_t *count)
{
    *count = 0;
    if (n < 1)
        return NULL;

    int *primes = malloc(n * sizeof(int));
    if (primes == NULL)
        return NULL;
    primes[(*count)++] = 2;

    if (n == 0)
        return primes;

    for (size_t i = 3; (long long)i < n + 1; i++)
    {
        int flag = 0;
        if (i > 10 && i % 10 == 5)
            continue;

        for (size_t j = 0; j < *count; j++)
        {
            if (primes[j] * primes[j] - 1 > (int)i)
            {
                primes[(*count)++] = i;
                break;
            }
            if ((int)i % primes[j] == 0)
            {
                break;
            }
            if (j == *count - 1)
                flag = 1;
        }
        if (flag)
            primes[(*count)++] = i;
    }

    return primes;
}

number_t *create_data(int prime, int exp)
{
    number_t *number = malloc(sizeof(number_t));
    if (number == NULL)
        return NULL;

    number->prime_number = prime;
    number->exponentiation = exp;

    return number;
}

int convert_to_list(node_t **head, long long number)
{
    if (number < 0)
        return ERR_NUMBER;
    size_t count = 0;
    int rc = ERR_OK;

    int *primes = find_prime_numbers(number, &count);
    if (primes == NULL)
        return ERR_MEMORY_ALLOCATION;

    number_t *data = NULL;

    int i = count - 1;
    while (i >= 0 && number > 0)
    {
        if (number % primes[i] == 0)
        {
            int exp = 0;
            while (number % primes[i] == 0 && number > 0)
            {
                exp++;
                number /= primes[i];
            }
            data = create_data(primes[i], exp);
            add_to_list(head, data);
        }
        i--;
    }

    free(primes);
    if (number != 1)
    {
        return ERR_CONVERTATION;
    }

    data = create_data(1, 0);
    add_to_list(head, data);
    return rc;
}

void print_number(void *data)
{
    number_t *number = (number_t *)data;
    if (number->exponentiation != 0)
        printf("%d %d ", number->prime_number, number->exponentiation);
    else
        printf("1\n");
}

int compare_by_prime(const void *l, const void *r)
{
    number_t *a = (number_t *)l;
    number_t *b = (number_t *)r;

    return b->prime_number - a->prime_number;
}

// Функция для объединения двух списков
static node_t *combine_lists(const node_t *a, const node_t *b)
{
    node_t *combined = NULL;

    const node_t *current_a = a;
    const node_t *current_b = b;

    while (current_a != NULL)
    {
        add_to_list(&combined, pop_front((node_t **)&current_a));
    }
    while (current_b != NULL)
    {
        add_to_list(&combined, pop_front((node_t **)&current_b));
    }

    return combined;
}

/**
 * @brief Функция для умножения двух списков. Списки должны быть отсортированы
 * @param a Первый список
 * @param b Второй список
 * @return Указатель на новый список
 */
node_t *mult_number(const node_t *a, const node_t *b, comparator_t comparator)
{
    if (a == NULL || b == NULL)
        return NULL;
    node_t *combined = combine_lists(a, b);
    if (combined == NULL)
        return NULL;

    // Сортируем комбинированный список
    combined = sort(combined, comparator);

    // Создаем новый список для результата
    node_t *result = NULL;
    number_t *previous_data = NULL;

    while (combined != NULL)
    {
        number_t *current_data = pop_front(&combined);

        if (previous_data == NULL || current_data->prime_number != previous_data->prime_number)
        {
            add_to_list(&result, current_data);
            previous_data = current_data;
        }
        else
        {
            previous_data->exponentiation += current_data->exponentiation;
            free(current_data);
        }
    }

    return result;
}

node_t *sqrt_list(node_t *head)
{
    if (head == NULL)
        return NULL;

    node_t *new_head = NULL;

    while (head)
    {
        number_t *data = pop_front(&head);
        data->exponentiation *= 2;
        add_to_list(&new_head, data);
    }

    return new_head;
}

node_t *div_list(long long a, long long b)
{
    if (b == 0)
        return NULL;
    long long convert = a / b;

    if (convert == 0)
        return NULL;
    node_t *result = NULL;

    int rc = ERR_OK;
    if ((rc = convert_to_list(&result, convert)) != ERR_OK)
    {
        return NULL;
    }
    return result;
}
