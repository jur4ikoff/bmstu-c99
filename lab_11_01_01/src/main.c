#include "constants.h"
#include "my_realization.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARGS INT_MIN, INT_MAX, SHRT_MIN, SHRT_MAX

int main(void)
{
    int rc = ERR_OK;
    int n1, n2;
    char s1[MAX_SIZE], s2[MAX_SIZE];
    char format[] = "%+-+----+++10hd %--2hd %+10hd %-----hd";

    n1 = snprintf(s1, MAX_SIZE, format, ARGS); // Чтобы убрать ошибку компиляции
    n2 = my_snprintf(s2, MAX_SIZE, format, ARGS);
    printf("%s\n%s\n", s1, s2);
    printf("%d %d\n", n1, n2);

    if (rc < ERR_OK)
        return rc;
    return ERR_OK;
}
