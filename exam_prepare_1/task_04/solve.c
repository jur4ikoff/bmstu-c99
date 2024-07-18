#include "solve.h"

int input_products_to_struct(size_t count)
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
        printf("string: %s number %d\n", string, product_price);
    }

    return rc;
}