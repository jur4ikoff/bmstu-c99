#include "solve.h"

void find_mean(double *mean, struct Person persons[], size_t count)
{
    *mean = 0;
    size_t sum = 0;

    for (size_t i = 0; i < count; i++)
    {
        sum += persons[i].height;
    }

    *mean = (double)sum / count;
}

void delete_from_array(struct Person persons[], size_t *count, size_t index)
{
    for (size_t i = index; i < *count - 1; i++)
    {
        struct Person temp;
        temp = persons[i];
        persons[i] = persons[i + 1];
        persons[i + 1] = temp;
    }
    (*count)--;
}

void run(struct Person persons[], size_t *count, double mean)
{
    for (size_t i = 0; i < *count; i++)
    {
        if (persons[i].height < mean)
        {
            delete_from_array(persons, count, i);
            i--;
        }
    }
}
