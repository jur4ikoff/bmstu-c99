#include "solve.h"

int main(void)
{
    int rc = ERR_OK, max_len = 0;
    rc = process(stdin, &max_len);
    if (rc != ERR_OK)
    {
        printf("Wrong Input\n");
        return rc;
    }
    if (max_len < 0)
    {
        printf("Error");
        return ERR_SEQ;
    }
    printf("%d\n", max_len);
    return rc;
}
