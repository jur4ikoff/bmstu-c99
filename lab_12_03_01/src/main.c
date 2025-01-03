#include "constants.h"
#include "errors.h"
#include "myarrlib.h"
#include <stdio.h>
#include <stdlib.h>

void print_error_message(int arg)
{
    printf("%s", RED);
    switch (arg)
    {
        case ERR_SIZE:
            printf("Размер массива слишком большой\n");
            break;
        case ERR_POINTER:
            printf("Ошибка при передаче аргументов\n");
            break;
    }
    printf("%s", RESET);
}

void print_arr(int *arr, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void)
{
    /*int a[MAX_SIZE] = { 1, 3, 0, 4 };
    int *dst = NULL;
    print_arr(a, sizeof(a) / sizeof(a[0]));
    int dst_len = 0;
    filter(dst, a, 4, &dst_len);
    printf("res %d\n", dst_len);
    dst = malloc(sizeof(int) * dst_len);
    filter(dst, a, 4, &dst_len);
    print_arr(dst, dst_len);
    free(dst);*/
    return 0;
}
