#include "stdio.h"
#include "string.h"
#define ERR_OK 0

int main(int argc, char **argv)
{
    printf("%d\n", argc);
    if (argc < 2)
    {
        return 1;
    }
    if (argc == 2)
        printf("%s\n", argv[0]);
    else
        return 2;
    return 0;
}
