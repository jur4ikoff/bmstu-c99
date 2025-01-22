#include "constants.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int rc = ERR_OK;
    char *line = malloc(20);
    if (snprintf(line, 10, "%s_%d", "test", 1) == -1)
    {
        free(line);
        return -1;
    }
    printf("%s\n", line);
    free(line);
    return rc;
}
