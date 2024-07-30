#ifndef SOLVE_H
#define SOLVE_H
#include "constants.h"
#include "errors.h"
#include "io.h"

struct product
{
    char name[MAX_STRING_LEN];
    int price;
};


int input_products_to_struct(size_t count, struct product products[MAX_COUNT]);
float get_mean(struct product products[MAX_COUNT], size_t count);
size_t get_index_min_diff(struct product products[MAX_COUNT], size_t count, float mean);
#endif
