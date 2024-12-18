#include "check_add.h"
#include "matrix.h"
#include <math.h>

int compare_matrix(matrix_t matrix_1, matrix_t matrix_2)
{
    if (matrix_1.row_count != matrix_2.row_count || matrix_1.column_count != matrix_2.column_count)
        return 1;

    for (size_t i = 0; i < matrix_1.row_count; i++)
    {
        for (size_t j = 0; j < matrix_1.column_count; j++)
        {
            if (fabs(matrix_1.ptrs[i][j] - matrix_2.ptrs[i][j]) > EPS)
                return 1;
        }
    }

    return 0;
}

/*Позитивный тест 1*/
// 1 - Сложении матрицы 1 на 1
START_TEST(pos_test_01)
{

    matrix_t matrix_1 = {0}, matrix_2 = {0}, output = {0}, expected = {0};
    matrix_1.row_count = 1;
    matrix_1.column_count = 1;
    allocate_matrix(&matrix_1);
    matrix_1.ptrs[0][0] = 0;

    matrix_2.row_count = 1;
    matrix_2.column_count = 1;
    allocate_matrix(&matrix_2);
    matrix_2.ptrs[0][0] = 2;

    expected.row_count = 1;
    expected.column_count = 1;
    allocate_matrix(&expected);
    expected.ptrs[0][0] = 2;

    int rc = add_matrix(matrix_1, matrix_2, &output);
    ck_assert_int_eq(rc, 0);

    int res = compare_matrix(output, expected);
    ck_assert_int_eq(res, 0);

    free_matrix(matrix_1);
    free_matrix(matrix_2);
    free_matrix(output);
    free_matrix(expected);
}
END_TEST

// 2 - Сложении матрицы 2 на 2
START_TEST(pos_test_02)
{

    matrix_t matrix_1 = {0}, matrix_2 = {0}, output = {0}, expected = {0};
    matrix_1.row_count = 2;
    matrix_1.column_count = 2;
    allocate_matrix(&matrix_1);
    matrix_1.ptrs[0][0] = 1;
    matrix_1.ptrs[0][1] = 2;
    matrix_1.ptrs[1][0] = 3;
    matrix_1.ptrs[1][1] = 4;

    matrix_2.row_count = 2;
    matrix_2.column_count = 2;
    allocate_matrix(&matrix_2);
    matrix_2.ptrs[0][0] = 5;
    matrix_2.ptrs[0][1] = 6;
    matrix_2.ptrs[1][0] = 7;
    matrix_2.ptrs[1][1] = 8;

    expected.row_count = 2;
    expected.column_count = 2;
    allocate_matrix(&expected);
    expected.ptrs[0][0] = 6;
    expected.ptrs[0][1] = 8;
    expected.ptrs[1][0] = 10;
    expected.ptrs[1][1] = 12;

    int rc = add_matrix(matrix_1, matrix_2, &output);
    ck_assert_int_eq(rc, 0);

    int res = compare_matrix(output, expected);
    ck_assert_int_eq(res, 0);

    free_matrix(matrix_1);
    free_matrix(matrix_2);
    free_matrix(output);
    free_matrix(expected);
}
END_TEST

// 3 - Сложение матриц с отрицательными числам
START_TEST(pos_test_03)
{
    matrix_t matrix_1 = {0}, matrix_2 = {0}, output = {0}, expected = {0};
    matrix_1.row_count = 2;
    matrix_1.column_count = 2;
    allocate_matrix(&matrix_1);
    matrix_1.ptrs[0][0] = -1;
    matrix_1.ptrs[0][1] = 2;
    matrix_1.ptrs[1][0] = -3;
    matrix_1.ptrs[1][1] = 4;

    matrix_2.row_count = 2;
    matrix_2.column_count = 2;
    allocate_matrix(&matrix_2);
    matrix_2.ptrs[0][0] = 5;
    matrix_2.ptrs[0][1] = -6;
    matrix_2.ptrs[1][0] = 7;
    matrix_2.ptrs[1][1] = -8;

    expected.row_count = 2;
    expected.column_count = 2;
    allocate_matrix(&expected);
    expected.ptrs[0][0] = 4;
    expected.ptrs[0][1] = -4;
    expected.ptrs[1][0] = 4;
    expected.ptrs[1][1] = -4;

    int rc = add_matrix(matrix_1, matrix_2, &output);
    ck_assert_int_eq(rc, 0);

    int res = compare_matrix(output, expected);
    ck_assert_int_eq(res, 0);

    free_matrix(matrix_1);
    free_matrix(matrix_2);
    free_matrix(output);
    free_matrix(expected);
}
END_TEST

// 4 - Сложение матриц с вещественными числами числам
START_TEST(pos_test_04)
{
    matrix_t matrix_1 = {0}, matrix_2 = {0}, output = {0}, expected = {0};
    matrix_1.row_count = 2;
    matrix_1.column_count = 2;
    allocate_matrix(&matrix_1);
    matrix_1.ptrs[0][0] = -1.23;
    matrix_1.ptrs[0][1] = 2.23;
    matrix_1.ptrs[1][0] = -3.23;
    matrix_1.ptrs[1][1] = 4.23;

    matrix_2.row_count = 2;
    matrix_2.column_count = 2;
    allocate_matrix(&matrix_2);
    matrix_2.ptrs[0][0] = 5.23;
    matrix_2.ptrs[0][1] = -6.23;
    matrix_2.ptrs[1][0] = 7.23;
    matrix_2.ptrs[1][1] = -8.23;

    expected.row_count = 2;
    expected.column_count = 2;
    allocate_matrix(&expected);
    expected.ptrs[0][0] = 4;
    expected.ptrs[0][1] = -4;
    expected.ptrs[1][0] = 4;
    expected.ptrs[1][1] = -4;

    int rc = add_matrix(matrix_1, matrix_2, &output);
    ck_assert_int_eq(rc, 0);

    int res = compare_matrix(output, expected);
    ck_assert_int_eq(res, 0);

    free_matrix(matrix_1);
    free_matrix(matrix_2);
    free_matrix(output);
    free_matrix(expected);
}
END_TEST

/*Негативный тест*/
// 1 - Сложение матриц разных по размеру
START_TEST(neg_test_01)
{
    matrix_t matrix_1 = {0}, matrix_2 = {0}, output = {0};
    matrix_1.row_count = 1;
    matrix_1.column_count = 2;
    allocate_matrix(&matrix_1);
    matrix_1.ptrs[0][0] = -1.23;
    matrix_1.ptrs[0][1] = 2.23;

    matrix_2.row_count = 2;
    matrix_2.column_count = 2;
    allocate_matrix(&matrix_2);
    matrix_2.ptrs[0][0] = 5.23;
    matrix_2.ptrs[0][1] = -6.23;
    matrix_2.ptrs[1][0] = 7.23;
    matrix_2.ptrs[1][1] = -8.23;

    int rc = add_matrix(matrix_1, matrix_2, &output);
    ck_assert_int_eq(rc, 7);

    free_matrix(matrix_1);
    free_matrix(matrix_2);
    free_matrix(output);
}
END_TEST

Suite *get_add_suite(void)
{
    Suite *suite = suite_create("add matrix");
    TCase *tc = tcase_create("add pos tests");

    tcase_add_test(tc, pos_test_01);
    tcase_add_test(tc, pos_test_02);
    tcase_add_test(tc, pos_test_03);
    tcase_add_test(tc, pos_test_04);
    tcase_add_test(tc, neg_test_01);

    suite_add_tcase(suite, tc);
    return suite;
}
