#ifndef OPERATIONS_H__
#define OPERATIONS_H__

#include "constants.h"
#include <stdio.h>

void sort_products_by_density(product_t products[], size_t count);
int find_same_beginning_string(product_t products[], size_t count, char *token, size_t *indexes);
#endif
