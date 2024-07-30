#include "solve.h"
#include "math.h"

int input_products_to_struct(size_t count, struct product products[MAX_COUNT])
{
    int rc = ERR_OK;
    for (size_t i = 0; i < count; i++)
    {
        char string[MAX_STRING_LEN];
        if ((rc = input_string(string)) != ERR_OK)
            return rc;
        int product_price;
        if (scanf("%d", &product_price) != 1)
        {
            output(ERR_INPUT);
            return ERR_INPUT;
        }
        fgetc(stdin);
        struct product input_product;
        strcpy(input_product.name, string);
        input_product.price = product_price;
        products[i] = input_product;
    }

    return rc;
}

float get_mean(struct product products[MAX_COUNT], size_t count)
{
    float sum = 0;
    struct product *ptr = products;
    for (size_t i = 0; i < count; i++)
    {
        sum += (ptr + i)->price;
    }
    return sum / count;
}


size_t get_index_min_diff(struct product products[MAX_COUNT], size_t count, float mean)
{
    size_t index = 0;
    float min = 10e8f;
    struct product *ptr = products;

    for (size_t i = 0; i < count; i++)
    {
        if (fabs((ptr + i)->price - mean) < min)
        {
            min = (float)fabs((ptr + i)->price - mean);
            index = i;
        }     
    }

    return index;
}
