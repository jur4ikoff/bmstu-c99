#include "check_mult.h"
#include "check_add.h"

// 1 - Умножение матрицы целых чисел 1 на 1
START_TEST(pos_test_01)
{
    matrix_t matrix_1 = { 0 }, matrix_2 = { 0 }, output = { 0 }, expected = { 0 };
    matrix_1.row_count = 1;
    matrix_1.column_count = 1;
    allocate_matrix(&matrix_1);
    matrix_1.ptrs[0][0] = 1;

    matrix_2.row_count = 1;
    matrix_2.column_count = 1;
    allocate_matrix(&matrix_2);
    matrix_2.ptrs[0][0] = 5;

    expected.row_count = 1;
    expected.column_count = 1;
    allocate_matrix(&expected);
    expected.ptrs[0][0] = 5;

    int rc = mult_matrix(matrix_1, matrix_2, &output);
    ck_assert_int_eq(rc, 0);

    int res = compare_matrix(output, expected);
    ck_assert_int_eq(res, 0);

    free_matrix(matrix_1);
    free_matrix(matrix_2);
    free_matrix(output);
    free_matrix(expected);
}

END_TEST

// 2 - Умножение на 0
START_TEST(pos_test_02)
{
    matrix_t matrix_1 = { 0 }, matrix_2 = { 0 }, output = { 0 }, expected = { 0 };
    matrix_1.row_count = 1;
    matrix_1.column_count = 1;
    allocate_matrix(&matrix_1);
    matrix_1.ptrs[0][0] = 0;

    matrix_2.row_count = 1;
    matrix_2.column_count = 1;
    allocate_matrix(&matrix_2);
    matrix_2.ptrs[0][0] = 5;

    expected.row_count = 1;
    expected.column_count = 1;
    allocate_matrix(&expected);
    expected.ptrs[0][0] = 0;

    int rc = mult_matrix(matrix_1, matrix_2, &output);
    ck_assert_int_eq(rc, 0);

    int res = compare_matrix(output, expected);
    ck_assert_int_eq(res, 0);

    free_matrix(matrix_1);
    free_matrix(matrix_2);
    free_matrix(output);
    free_matrix(expected);
}

END_TEST

// 3 - Умножение квадратной матрицы 2 на 2 с положительными и отрицательным цифрами
START_TEST(pos_test_03)
{
    matrix_t matrix_1 = { 0 }, matrix_2 = { 0 }, output = { 0 }, expected = { 0 };
    matrix_1.row_count = 2;
    matrix_1.column_count = 2;
    allocate_matrix(&matrix_1);
    matrix_1.ptrs[0][0] = 0;
    matrix_1.ptrs[0][1] = 2;
    matrix_1.ptrs[1][0] = 3;
    matrix_1.ptrs[1][1] = 4;

    matrix_2.row_count = 2;
    matrix_2.column_count = 2;
    allocate_matrix(&matrix_2);
    matrix_2.ptrs[0][0] = 12;
    matrix_2.ptrs[0][1] = 4;
    matrix_2.ptrs[1][0] = -2;
    matrix_2.ptrs[1][1] = 4;

    expected.row_count = 2;
    expected.column_count = 2;
    allocate_matrix(&expected);
    expected.ptrs[0][0] = -4;
    expected.ptrs[0][1] = 8;
    expected.ptrs[1][0] = 28;
    expected.ptrs[1][1] = 28;

    int rc = mult_matrix(matrix_1, matrix_2, &output);
    ck_assert_int_eq(rc, 0);

    int res = compare_matrix(output, expected);
    ck_assert_int_eq(res, 0);

    free_matrix(matrix_1);
    free_matrix(matrix_2);
    free_matrix(output);
    free_matrix(expected);
}

// 4 - Умножение квадратной матрицы 2 на 2 только из положительных цифр
START_TEST(pos_test_04)
{
    matrix_t matrix_1 = { 0 }, matrix_2 = { 0 }, output = { 0 }, expected = { 0 };
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
    matrix_2.ptrs[0][0] = 12;
    matrix_2.ptrs[0][1] = 4;
    matrix_2.ptrs[1][0] = 2;
    matrix_2.ptrs[1][1] = 4;

    expected.row_count = 2;
    expected.column_count = 2;
    allocate_matrix(&expected);
    expected.ptrs[0][0] = 16;
    expected.ptrs[0][1] = 12;
    expected.ptrs[1][0] = 44;
    expected.ptrs[1][1] = 28;

    int rc = mult_matrix(matrix_1, matrix_2, &output);
    ck_assert_int_eq(rc, 0);

    int res = compare_matrix(output, expected);
    ck_assert_int_eq(res, 0);

    free_matrix(matrix_1);
    free_matrix(matrix_2);
    free_matrix(output);
    free_matrix(expected);
}

END_TEST

// 5 - Умножение квадратной матрицы 2 на 2 только из отрицательных цифр
START_TEST(pos_test_05)
{
    matrix_t matrix_1 = { 0 }, matrix_2 = { 0 }, output = { 0 }, expected = { 0 };
    matrix_1.row_count = 2;
    matrix_1.column_count = 2;
    allocate_matrix(&matrix_1);
    matrix_1.ptrs[0][0] = -1;
    matrix_1.ptrs[0][1] = -2;
    matrix_1.ptrs[1][0] = -3;
    matrix_1.ptrs[1][1] = -4;

    matrix_2.row_count = 2;
    matrix_2.column_count = 2;
    allocate_matrix(&matrix_2);
    matrix_2.ptrs[0][0] = -12;
    matrix_2.ptrs[0][1] = -4;
    matrix_2.ptrs[1][0] = -2;
    matrix_2.ptrs[1][1] = -4;

    expected.row_count = 2;
    expected.column_count = 2;
    allocate_matrix(&expected);
    expected.ptrs[0][0] = 16;
    expected.ptrs[0][1] = 12;
    expected.ptrs[1][0] = 44;
    expected.ptrs[1][1] = 28;

    int rc = mult_matrix(matrix_1, matrix_2, &output);
    ck_assert_int_eq(rc, 0);

    int res = compare_matrix(output, expected);
    ck_assert_int_eq(res, 0);

    free_matrix(matrix_1);
    free_matrix(matrix_2);
    free_matrix(output);
    free_matrix(expected);
}

END_TEST

// 6 - Умножение квадратной матрицы 2 на 2 из вещественных чисел
START_TEST(pos_test_06)
{
    matrix_t matrix_1 = { 0 }, matrix_2 = { 0 }, output = { 0 }, expected = { 0 };
    matrix_1.row_count = 2;
    matrix_1.column_count = 2;
    allocate_matrix(&matrix_1);
    matrix_1.ptrs[0][0] = 1.25;
    matrix_1.ptrs[0][1] = 2.25;
    matrix_1.ptrs[1][0] = -3.1;
    matrix_1.ptrs[1][1] = 4.32;

    matrix_2.row_count = 2;
    matrix_2.column_count = 2;
    allocate_matrix(&matrix_2);
    matrix_2.ptrs[0][0] = 12;
    matrix_2.ptrs[0][1] = 4.12;
    matrix_2.ptrs[1][0] = -2;
    matrix_2.ptrs[1][1] = 4.42;

    expected.row_count = 2;
    expected.column_count = 2;
    allocate_matrix(&expected);
    expected.ptrs[0][0] = 10.5;
    expected.ptrs[0][1] = 15.095;
    expected.ptrs[1][0] = -45.84;
    expected.ptrs[1][1] = 6.3224;

    int rc = mult_matrix(matrix_1, matrix_2, &output);
    ck_assert_int_eq(rc, 0);

    int res = compare_matrix(output, expected);
    ck_assert_int_eq(res, 0);

    free_matrix(matrix_1);
    free_matrix(matrix_2);
    free_matrix(output);
    free_matrix(expected);
}

END_TEST

// 7 - Умножение прямоугольных матриц
START_TEST(pos_test_07)
{
    matrix_t matrix_1 = { 0 }, matrix_2 = { 0 }, output = { 0 }, expected = { 0 };
    matrix_1.row_count = 2;
    matrix_1.column_count = 3;
    allocate_matrix(&matrix_1);
    matrix_1.ptrs[0][0] = 0;
    matrix_1.ptrs[0][1] = 1;
    matrix_1.ptrs[0][2] = 2;
    matrix_1.ptrs[1][0] = 3;
    matrix_1.ptrs[1][1] = 4;
    matrix_1.ptrs[1][2] = 5;

    matrix_2.row_count = 3;
    matrix_2.column_count = 2;
    allocate_matrix(&matrix_2);
    matrix_2.ptrs[0][0] = 6;
    matrix_2.ptrs[0][1] = 7;
    matrix_2.ptrs[1][0] = 8;
    matrix_2.ptrs[1][1] = 9;
    matrix_2.ptrs[2][0] = 10;
    matrix_2.ptrs[2][1] = 11;

    expected.row_count = 2;
    expected.column_count = 2;
    allocate_matrix(&expected);
    expected.ptrs[0][0] = 28;
    expected.ptrs[0][1] = 31;
    expected.ptrs[1][0] = 100;
    expected.ptrs[1][1] = 112;

    int rc = mult_matrix(matrix_1, matrix_2, &output);
    ck_assert_int_eq(rc, 0);

    int res = compare_matrix(output, expected);
    ck_assert_int_eq(res, 0);

    free_matrix(matrix_1);
    free_matrix(matrix_2);
    free_matrix(output);
    free_matrix(expected);
}

// 8 - Умножение прямоугольных матриц, в которой содержатся отрицательные числа.
START_TEST(pos_test_08)
{
    matrix_t matrix_1 = { 0 }, matrix_2 = { 0 }, output = { 0 }, expected = { 0 };
    matrix_1.row_count = 2;
    matrix_1.column_count = 3;
    allocate_matrix(&matrix_1);
    matrix_1.ptrs[0][0] = -23;
    matrix_1.ptrs[0][1] = -1;
    matrix_1.ptrs[0][2] = 2;
    matrix_1.ptrs[1][0] = 33;
    matrix_1.ptrs[1][1] = 4;
    matrix_1.ptrs[1][2] = -5;

    matrix_2.row_count = 3;
    matrix_2.column_count = 1;
    allocate_matrix(&matrix_2);
    matrix_2.ptrs[0][0] = 0;
    matrix_2.ptrs[1][0] = 1;
    matrix_2.ptrs[2][0] = -8;

    expected.row_count = 2;
    expected.column_count = 1;
    allocate_matrix(&expected);
    expected.ptrs[0][0] = -17;
    expected.ptrs[1][0] = 44;

    int rc = mult_matrix(matrix_1, matrix_2, &output);
    ck_assert_int_eq(rc, 0);

    int res = compare_matrix(output, expected);
    ck_assert_int_eq(res, 0);

    free_matrix(matrix_1);
    free_matrix(matrix_2);
    free_matrix(output);
    free_matrix(expected);
}

// 9 - Умножение прямоугольных матриц, в которой содержатся вещественные числа
START_TEST(pos_test_09)
{
    matrix_t matrix_1 = { 0 }, matrix_2 = { 0 }, output = { 0 }, expected = { 0 };
    matrix_1.row_count = 1;
    matrix_1.column_count = 3;
    allocate_matrix(&matrix_1);
    matrix_1.ptrs[0][0] = -2.3;
    matrix_1.ptrs[0][1] = -1.0;
    matrix_1.ptrs[0][2] = 2.5;

    matrix_2.row_count = 3;
    matrix_2.column_count = 1;
    allocate_matrix(&matrix_2);
    matrix_2.ptrs[0][0] = 0.2;
    matrix_2.ptrs[1][0] = 1.5;
    matrix_2.ptrs[2][0] = -8.12;

    expected.row_count = 1;
    expected.column_count = 1;
    allocate_matrix(&expected);
    expected.ptrs[0][0] = -22.26;

    int rc = mult_matrix(matrix_1, matrix_2, &output);
    ck_assert_int_eq(rc, 0);

    int res = compare_matrix(output, expected);
    ck_assert_int_eq(res, 0);

    free_matrix(matrix_1);
    free_matrix(matrix_2);
    free_matrix(output);
    free_matrix(expected);
}

END_TEST

// Негативные тесты
// 1 - Матрицы нельзя умножить
START_TEST(neg_test_01)
{
    matrix_t matrix_1 = { 0 }, matrix_2 = { 0 }, output = { 0 };
    matrix_1.row_count = 1;
    matrix_1.column_count = 3;
    allocate_matrix(&matrix_1);
    matrix_1.ptrs[0][0] = -2.3;
    matrix_1.ptrs[0][1] = -1.0;
    matrix_1.ptrs[0][2] = 2.5;

    matrix_2.row_count = 1;
    matrix_2.column_count = 3;
    allocate_matrix(&matrix_2);
    matrix_2.ptrs[0][0] = 0.2;
    matrix_2.ptrs[0][1] = 1.5;
    matrix_2.ptrs[0][2] = -8.12;


    int rc = mult_matrix(matrix_1, matrix_2, &output);
    ck_assert_int_eq(rc, 10);

    free_matrix(matrix_1);
    free_matrix(matrix_2);
    free_matrix(output);
}

END_TEST

Suite *get_mult_suite(void)
{
    Suite *suite = suite_create("test_mult");
    TCase *tc = tcase_create("mult_pos");

    tcase_add_test(tc, pos_test_01);
    tcase_add_test(tc, pos_test_02);
    tcase_add_test(tc, pos_test_03);
    tcase_add_test(tc, pos_test_04);
    tcase_add_test(tc, pos_test_05);
    tcase_add_test(tc, pos_test_06);
    tcase_add_test(tc, pos_test_07);
    tcase_add_test(tc, pos_test_08);
    tcase_add_test(tc, pos_test_09);

    tcase_add_test(tc, neg_test_01);

    suite_add_tcase(suite, tc);

    return suite;
}
