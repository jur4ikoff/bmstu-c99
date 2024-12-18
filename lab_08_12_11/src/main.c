/*
ЛР 3 Обработка матриц вариант 12, файл обычный

Написать программу для работы с матрицами, которая реализует сложение матриц, умножение матриц и вычисление определителя с помощью разложения по строке
Память под матрицы выделяется динамически.
Исходные матрицы читаются из файла, Результирующая матрица записываются в файл.
Формат запуска приложения должен быть следующим
app.exe action mtr_1.txt [mtr_2.txt] res.txt
Возможные значения action:
1. a — сложение;
2. m — умножение;
3. o — операция по варианту

Выделения памяти:  данные хранятся единым блоком построчно. В памяти размещается, помимо данных, массив указателей на строки
*/

#include "constants.h"
#include "errors.h"
#include "matrix.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    // Объявление переменных
    int rc = ERR_OK;
    char action_buffer[MAX_OPER_LEN], filename_1[MAX_PATH_LEN + 1], filename_2[MAX_PATH_LEN + 1], filename_output[MAX_PATH_LEN + 1];
    char action;
    matrix_t matrix_1 = { 0 }, matrix_2 = { 0 }, output = { 0 };

    // Проверка корректности аргументов
    if (argc < MIN_ARGS_COUNT || argc > MAX_ARGS_COUNT)
    {
        print_err_message(ERR_ARG_COUNT);
        return ERR_ARG_COUNT;
    }

    if (strlen(argv[1]) < MAX_OPER_LEN)
    {
        strcpy(action_buffer, argv[1]);
        action = action_buffer[0];
    }
    else
    {
        print_err_message(ERR_ARG_LENGTH);
        return ERR_ARG_LENGTH;
    }

    for (size_t i = 2; i < (size_t)argc; i++)
    {
        if (strlen(argv[i]) > MAX_PATH_LEN)
        {
            print_err_message(ERR_ARG_LENGTH);
            return ERR_ARG_LENGTH;
        }
    }

    strcpy(filename_1, argv[2]);

    if (argc == 5)
    {
        strcpy(filename_2, argv[3]);
        strcpy(filename_output, argv[4]);
    }
    else
        strcpy(filename_output, argv[3]);

    // Обработка действия
    if (action == 'a')
    {
        // Сложение матриц
        // Чтение первой матрицы
        if ((rc = read_matrix(filename_1, &matrix_1)) != ERR_OK)
            goto full_exit;
        print_matrix(matrix_1);
        printf("\n");

        // Чтение второй матрицы
        if ((rc = read_matrix(filename_2, &matrix_2)) != ERR_OK)
            goto full_exit;

        print_matrix(matrix_2);
        printf("\n");

        // Сложение матриц
        if ((rc = add_matrix(matrix_1, matrix_2, &output)) != ERR_OK)
            goto full_exit;

        print_matrix(output);
        printf("\n");

        // print_matrix(output);
        // Запись ответа в файл
        if ((rc = write_matrix(filename_output, output)) != ERR_OK)
            goto full_exit;
    }
    else if (action == 'm')
    {
        // Умножение матриц
        // Чтение первой матрицы
        if ((rc = read_matrix(filename_1, &matrix_1)) != ERR_OK)
            goto full_exit;

        print_matrix(matrix_1);
        printf("\n");

        // Чтение второй матрицы
        if ((rc = read_matrix(filename_2, &matrix_2)) != ERR_OK)
            goto full_exit;

        print_matrix(matrix_2);
        printf("\n");

        // Умножекие матриц
        if ((rc = mult_matrix(matrix_1, matrix_2, &output)) != ERR_OK)
            goto full_exit;

        print_matrix(output);
        printf("\n");

        // Запись ответа в файл
        // print_matrix(output);
        if ((rc = write_matrix(filename_output, output)) != ERR_OK)
            goto full_exit;
    }
    else if (action == 'o')
    {
        // Вычисление определителя матрицы
        if (argc == 5)
        {
            rc = ERR_ARG_COUNT;
            goto full_exit;
        }

        // Чтение матрицы
        if ((rc = read_matrix(filename_1, &matrix_1)) != ERR_OK)
            goto full_exit;

        print_matrix(matrix_1);
        printf("\n");

        // Вычисление определителя матрицы
        double determinant;
        if ((rc = find_determinant(matrix_1, &determinant)) != ERR_OK)
            goto full_exit;

        printf("%f\n", determinant);

        // printf("%f\n", determinant);

        // Запись ответа в файл
        FILE *file = fopen(filename_output, "w");
        if (file == NULL)
        {
            rc = ERR_FILENAME;
            goto full_exit;
        }
        fprintf(file, "%f\n", determinant);
        fclose(file);
    }
    else
    {
        // Неправильное действие
        rc = ERR_WRONG_ACTION;
        goto full_exit;
    }

// Метка для выхода из программы
    full_exit:
    if (1)
    {
        free_matrix(matrix_1);
        free_matrix(matrix_2);
        free_matrix(output);
    }
    print_err_message(rc);
    return rc;
}
