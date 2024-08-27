/* Дан текстовый файл, содержащий целые числа, разделенные пробелами и символами разделителями.
Найти среднее арифметическое всех чисел и вывести ближайшее к нему целое число.
*/
#include "constants.h"
#include "io.h"

int main(void)
{
    int rc = ERR_OK, numbers[MAX_ARR_LEN];
    size_t count = 0;

    FILE *filename = fopen("test.txt", "r");
    if (!filename)
    {
        return ERR_FILE;
        output(ERR_FILE);
    }

    if (((rc = input_from_file(filename, numbers, &count)) != ERR_OK))
    {
        output(rc);
        return rc;
    }

    double average = calculate_average(numbers, count);
    printf("%lf\n", average);
    find_closest(numbers, count, average);
    return rc;
}
