#include "solve.h"

// Заполняет бинарный файл случайными числами.
int fill_bin_file(FILE *file, size_t count)
{
    int num;
    if (count <= 0)
        return ERR_COUNT;

    srand(time(NULL));
    for (size_t i = 0; i < count; i++)
    {
        num = rand() % 1000;
        if (fwrite(&num, sizeof(int), 1, file) != 1)
            return ERR_WRITE;
    }

    return ERR_OK;
}

// Функция возвращает размер файла.
int file_size(FILE *f, size_t *size)
{
    long sz;
    if (fseek(f, 0L, SEEK_END))
        return 1;

    sz = ftell(f);
    if (sz < 0)
        return 1;

    *size = sz;

    return fseek(f, 0L, SEEK_SET);
}

// Функция выводит на экран содержимое бинарного файла.
int print_int_file(FILE *f)
{
    size_t size;
    int number, rc = ERR_OK;

    rc = file_size(f, &size);
    if (size % sizeof(int) != 0)
        return ERR_FILE;

    size_t count = size / sizeof(int);
    if (count < 1)
        rc = ERR_COUNT;

    if (rc == ERR_OK)
    {
        for (size_t i = 0; i < count; i++)
        {
            if (fread(&number, sizeof(int), 1, f) == 1)
                printf("%d ", number);
            else
                return ERR_READ;
        }
    }
    else
        return ERR_READ;
    printf("\n");
    return rc;
}

// Функция выводит на экран содержимое бинарного
int get_number_by_pos(FILE *file, size_t pos, int *num)
{
    int rc = ERR_OK;
    if (fseek(file, pos * sizeof(int), SEEK_SET))
        rc = ERR_READ;
    else
    {
        if (fread(num, sizeof(int), 1, file) != 1)
            rc = ERR_READ;
    }
    return rc;
}

// Функция записывает в бинарный файл число по позиции
int put_number_by_pos(FILE *file, size_t pos, int num)
{
    int rc = ERR_OK;
    if (fseek(file, pos * sizeof(int), SEEK_SET))
        rc = ERR_WRITE;
    else
    {
        if (fwrite(&num, sizeof(int), 1, file) != 1)
            rc = ERR_WRITE;
    }
    return rc;
}

// Сортировка бинарного файла внутри.
int sort_int_file(FILE *file)
{
    size_t size;
    int num1, num2;
    int rc = file_size(file, &size);
    if (size % sizeof(int) != 0)
        return ERR_FILE;

    size_t count = size / sizeof(int);
    if (count < 1)
        rc = ERR_COUNT;
    if (rc == ERR_OK)
    {
        for (size_t i = 0; i < count; i++)
        {
            for (size_t j = 0; j < count - 1; j++)
            {
                rc = get_number_by_pos(file, j, &num1);
                rc = rc + get_number_by_pos(file, j + 1, &num2);
                if (num1 > num2)
                {
                    rc = put_number_by_pos(file, j, num2);
                    rc = rc + put_number_by_pos(file, j + 1, num1);
                }
            }
        }
    }
    return rc;
}
