#include "matrix.h"
#include "errors.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Функция для выделения памяти для матрицы
 * @param matrix Указатель на матрицу
 * @return Код возврата
 */
int allocate_matrix(matrix_t *matrix)
{
    matrix->ptrs = malloc(matrix->row_count * sizeof(double *));
    if (!matrix->ptrs)
        return ERR_MEMORY_ALLOCATION;

    matrix->data = malloc(matrix->row_count * matrix->column_count * sizeof(double));
    if (!matrix->data)
    {
        free(matrix->ptrs);
        return ERR_MEMORY_ALLOCATION;
    }
    for (size_t i = 0; i < matrix->row_count; i++)
        matrix->ptrs[i] = matrix->data + i * matrix->column_count;
    return ERR_OK;
}

/**
 * @brief Освобождение вывделенной под матрицу памяти
 * @param matrix Указатель на матрицу
 */
void free_matrix(matrix_t matrix)
{
    if (matrix.ptrs && *matrix.ptrs)
    {
        free(matrix.ptrs[0]);
        free(matrix.ptrs);
    }
}

/**
 * @brief Чтение матрицы из файла
 * @param matrix Указатель на матрицу
 * @param filename Путь к файлу
 * @return Код возврата
 */
int read_matrix(const char *filename, matrix_t *matrix)
{
    int rc = ERR_OK;

    // Открываем файл
    FILE *file = fopen(filename, "r");
    if (!file)
        return ERR_FILENAME;

    // Читаем размер матрицы и проверяем его корректность
    int n, m;
    if (fscanf(file, "%d %d", &n, &m) != 2)
    {
        fclose(file);
        return ERR_WRONG_MATRIX_SIZE;
    }

    if (n < 0 || m < 0)
    {
        fclose(file);
        return ERR_WRONG_MATRIX_SIZE;
    }

    // Заполнение матрицы
    matrix->row_count = n;
    matrix->column_count = m;

    if ((rc = allocate_matrix(matrix)) != ERR_OK)
    {
        fclose(file);
        return rc;
    }

    for (size_t i = 0; i < matrix->row_count; i++)
    {
        for (size_t j = 0; j < matrix->column_count; j++)
        {
            if (fscanf(file, "%lf", &matrix->ptrs[i][j]) != 1)
            {
                fclose(file);
                return ERR_WRONG_MATRIX_ELEMENT;
            }
        }
    }

    fclose(file);
    return rc;
}

/**
 * @brief Чтение матрицы из файла
 * @param matrix матрица
 */
void print_matrix(matrix_t matrix)
{
    if (matrix.data == NULL)
        return;

    for (size_t i = 0; i < matrix.row_count; i++)
    {
        for (size_t j = 0; j < matrix.column_count; j++)
        {
            printf("%.2f ", matrix.ptrs[i][j]);
        }
        printf("\n");
    }
}

/**
 * @brief Функция реализует сложение двух матриц
 * @param matrix_1 Указатель на первую матрицу
 * @param matrix_2 Указатель на вторую матрицу
 * @param output Указатель на матрицу, для результата
 * @return Код возврата
 */
int add_matrix(const matrix_t matrix_1, const matrix_t matrix_2, matrix_t *output)
{
    int rc = ERR_OK;

    if (matrix_1.row_count != matrix_2.row_count || matrix_1.column_count != matrix_2.column_count)
        return ERR_MATRIX_HAVE_NOT_EQ_SIZE;

    if (matrix_1.row_count == 0 || matrix_2.row_count == 0 || matrix_1.column_count == 0 || matrix_2.column_count == 0)
        return ERR_EMPTY_MATRIX;

    output->row_count = matrix_1.row_count;
    output->column_count = matrix_1.column_count;
    if ((rc = allocate_matrix(output)) != ERR_OK)
        return rc;

    for (size_t i = 0; i < output->row_count; i++)
    {
        for (size_t j = 0; j < output->column_count; j++)
        {
            output->ptrs[i][j] = matrix_1.ptrs[i][j] + matrix_2.ptrs[i][j];
        }
    }

    return rc;
}

/**
 * @brief Функция реализует умножение двух матриц
 * @param matrix_1 Указатель на первую матрицу
 * @param matrix_2 Указатель на вторую матрицу
 * @param output Указатель на матрицу, для результата
 * @return Код возврата
 */
int mult_matrix(const matrix_t matrix_1, const matrix_t matrix_2, matrix_t *result)
{
    int rc = ERR_OK;

    // Обработка входных данных
    if (matrix_1.ptrs == NULL || matrix_2.ptrs == NULL)
        return ERR_EMPTY_MATRIX;

    if (matrix_1.column_count != matrix_2.row_count)
        return ERR_MATRIX_CANNOT_MULT;

    if (matrix_1.row_count == 0 || matrix_2.row_count == 0 || matrix_1.column_count == 0 || matrix_2.column_count == 0)
        return ERR_EMPTY_MATRIX;

    // Выделение памяти под результирующую матрицу
    result->row_count = matrix_1.row_count;
    result->column_count = matrix_2.column_count;
    if ((rc = allocate_matrix(result)) != ERR_OK)
        return rc;

    for (size_t i = 0; i < result->row_count; i++)
    {
        for (size_t j = 0; j < result->column_count; j++)
        {
            result->ptrs[i][j] = 0;
            for (size_t k = 0; k < matrix_1.column_count; k++)
            {
                result->ptrs[i][j] += matrix_1.ptrs[i][k] * matrix_2.ptrs[k][j];
            }
        }
    }

    return rc;
}

/**
 * @brief Запись матрицы в файл
 * @param filename Путь к файлу
 * @param matrix Матрица для записи
 * @return Код возврата
 */
int write_matrix(const char *filename, const matrix_t matrix)
{
    FILE *file = fopen(filename, "w");
    if (!file)
        return ERR_FILENAME;

    fprintf(file, "%zu %zu\n", matrix.row_count, matrix.column_count);

    for (size_t i = 0; i < matrix.row_count; i++)
    {
        for (size_t j = 0; j < matrix.column_count; j++)
        {
            if (j + 1 < matrix.column_count)
                fprintf(file, "%f ", matrix.ptrs[i][j]);
            else
                fprintf(file, "%f\n", matrix.ptrs[i][j]);
        }
    }

    fclose(file);
    return ERR_OK;
}

// Функция вычисляет определитель матрицы методом разложения на строки
static double calc_determinant(matrix_t matrix)
{
    // База рекурсии
    if (matrix.row_count == 1 && matrix.column_count == 1)
        return matrix.data[0];

    double determinant = 0.0;
    for (size_t j = 0; j < matrix.column_count; j++)
    {
        // Выделение памяти под субматрицы
        matrix_t submatrix;
        submatrix.row_count = matrix.row_count - 1;
        submatrix.column_count = matrix.column_count - 1;

        allocate_matrix(&submatrix);

        size_t sub_i = 0;
        size_t sub_j = 0;

        for (size_t i = 1; i < matrix.row_count; i++)
        {
            for (size_t k = 0; k < matrix.column_count; k++)
            {
                if (k != j)
                {
                    // Копирование значений из исходной матрицы в подматрицу
                    submatrix.data[sub_i * (matrix.column_count - 1) + sub_j] = matrix.data[i * matrix.column_count + k];
                    sub_j++;

                    if (sub_j == matrix.column_count - 1)
                    {
                        sub_j = 0;
                        sub_i++;
                    }
                }
            }
        }

        // Получение знака и умножение на определитель подматрицы
        double sign = (j % 2 == 0) ? 1.0 : -1.0;

        // Суммирование произведений элемента и определителя подматрицы (вызов рекурсии)
        determinant += sign * matrix.data[j] * calc_determinant(submatrix);

        // Освобождении памяти под подматрицы
        free_matrix(submatrix);
    }

    return determinant;
}

/**
 * @brief Функция вычисляет определитель матрицы методом разложения на строки
 * @param matrix Матрица
 * @param det Указатель на определитель
 * @return Код врзврата
 */
int find_determinant(matrix_t matrix, double *det)
{
    // Проверки на возможность вычисления
    if (matrix.row_count != matrix.column_count)
        return ERR_NOT_SQUARE_MATRIX;

    if (matrix.row_count == 0 || matrix.column_count == 0)
        return ERR_EMPTY_MATRIX;

    // Запуск функции
    *det = calc_determinant(matrix);
    return ERR_OK;
}
