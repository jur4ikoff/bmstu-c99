// Нужно удалить структуры, где рост меньше среднего
#include "const.h"
#include "io.h"
#include "solve.h"

int main(void)
{
    int rc = ERR_OK;
    size_t count;
    if ((rc = input_size(&count)) != ERR_OK)
    {
        output(rc);
        return rc;
    }

    if (count == 1)
    {
        output(ERR_OUTPUT);
        return ERR_OUTPUT;
    }

    fgetc(stdin);
    struct Person persons[MAX_SIZE];

    if ((rc = input_to_struct(count, persons)) != ERR_OK)
    {
        output(rc);
        return rc;
    }

    double mean = 0;
    find_mean(&mean, persons, count);
    run(persons, &count, mean);
    print_struct_array(persons, count);
    return rc;
}
