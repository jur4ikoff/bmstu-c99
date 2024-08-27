#include "io.h"

int input_from_file(FILE *filename, int number_array[], size_t *word_count)
{
    *word_count = 0;
    while (fscanf(filename, "%d", &number_array[*word_count]) == 1)
    {
        (*word_count)++;
    }
    if (!feof(filename))
        return ERR_FILE;
    return ERR_OK;
}

double calculate_average(int numbers[], size_t count)
{
    double sum = 0;
    for (size_t i = 0; i < count; i++)
    {
        sum += numbers[i];
    }
    return sum / (double)count;
}

void find_closest(int numbers[], size_t count, double average)
{
    size_t index = -1;
    double min = 10e6;
    for (size_t i = 0; i < count; i++)
    {
        if (fabs(numbers[i] - average) < min)
        {
            min = fabs(numbers[i] - average);
            index = i;
        }      
    }
    printf("index - %ld\nnumber - %d\n", index, numbers[index]);
}
void output(int arg)
{
    switch (arg)
    {
    case ERR_FILE:
        printf("Error opening the file.\n");
        break;
    case ERR_INPUT:
        printf("Error reading from the file.\n");
        break;
    case ERR_EMPTY:
        printf("The file is empty.\n");
        break;
    }
}
