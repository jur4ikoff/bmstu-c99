#include "constants.h"
#include "io.h"
#include "solve.h"

int main(int argc, char **argv)
{
    int rc = ERR_OK, count = 0;
    double sum = 0, mean, qsum = 0;

    // Проверка количества аргументов
    if (argc != 2)
    {
        processing_errors(ERR_EMPTY_INPUT);
        return ERR_EMPTY_INPUT;
    }

    // Открытие файла
    FILE *file;
    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        processing_errors(ERR_FILE);
        return ERR_WRONG_INPUT;
    }
    // Считаем сумму и количнство для среднего
    rc = calculate_sum(file, &count, &sum, &qsum);
    if (rc != ERR_OK)
    {
        processing_errors(rc);
        return rc;
    }
    mean = sum / count;
    rewind(file);
    if (count <= 0)
    {
        processing_errors(ERR_EMPTY_FILE);
        return ERR_EMPTY_FILE;
    }

    // Проверяем каждое значение на правило
    int result = check_rule_of_three_sigma(file, mean, sum, qsum, count);
    printf("%d\n", result);
    fclose(file);
    return rc;
}
