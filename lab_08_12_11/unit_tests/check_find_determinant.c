#include "check_find_determinant.h"
#include "matrix.h"
#include <string.h>

int compare_double(double a, double b)
{
    if (a - b < EPS)
        return 0;
    return 1;
}

/*Позитивные тесты*/
// 1 - Матрица из одного нуля
START_TEST(pos_test_01)
{
    matrix_t matrix_input = {0};
    matrix_input.row_count = 1;
    matrix_input.column_count = 1;
    allocate_matrix(&matrix_input);
    matrix_input.ptrs[0][0] = 0;

    double det;
    int rc = find_determinant(matrix_input, &det);
    ck_assert_int_eq(rc, 0);

    int res = compare_double(det, 0);
    ck_assert_int_eq(res, 0);

    free_matrix(matrix_input);
}

// 2 - Матрица из нулей
START_TEST(pos_test_02)
{
    matrix_t matrix_input = {0};
    matrix_input.row_count = 2;
    matrix_input.column_count = 2;
    allocate_matrix(&matrix_input);
    matrix_input.ptrs[0][0] = 0;
    matrix_input.ptrs[0][1] = 0;
    matrix_input.ptrs[1][0] = 0;
    matrix_input.ptrs[1][1] = 0;

    double det;
    int rc = find_determinant(matrix_input, &det);
    ck_assert_int_eq(rc, 0);

    int res = compare_double(det, 0);
    ck_assert_int_eq(res, 0);

    free_matrix(matrix_input);
}

// 3 - Матрица из единиц по главной диагонали
START_TEST(pos_test_03)
{
    matrix_t matrix_input = {0};
    matrix_input.row_count = 2;
    matrix_input.column_count = 2;
    allocate_matrix(&matrix_input);
    matrix_input.ptrs[0][0] = 1;
    matrix_input.ptrs[0][1] = 0;
    matrix_input.ptrs[1][0] = 0;
    matrix_input.ptrs[1][1] = 1;

    double det;
    int rc = find_determinant(matrix_input, &det);
    ck_assert_int_eq(rc, 0);

    int res = compare_double(det, 1);
    ck_assert_int_eq(res, 0);

    free_matrix(matrix_input);
}

// 4 - Определитель полностью заполненной матрицы равен нулю
START_TEST(pos_test_04)
{
    matrix_t matrix_input = {0};
    matrix_input.row_count = 3;
    matrix_input.column_count = 3;
    allocate_matrix(&matrix_input);
    matrix_input.ptrs[0][0] = 1;
    matrix_input.ptrs[0][1] = 2;
    matrix_input.ptrs[0][2] = 3;
    matrix_input.ptrs[1][0] = 4;
    matrix_input.ptrs[1][1] = 5;
    matrix_input.ptrs[1][2] = 6;
    matrix_input.ptrs[2][0] = 7;
    matrix_input.ptrs[2][1] = 8;
    matrix_input.ptrs[2][2] = 9;

    double det;
    int rc = find_determinant(matrix_input, &det);
    ck_assert_int_eq(rc, 0);

    int res = compare_double(det, 0);
    ck_assert_int_eq(res, 0);

    free_matrix(matrix_input);
}

END_TEST

// 5 - Определитель полностью заполненной матрицы положительный
START_TEST(pos_test_05)
{
    matrix_t matrix_input = {0};
    matrix_input.row_count = 3;
    matrix_input.column_count = 3;
    allocate_matrix(&matrix_input);
    matrix_input.ptrs[0][0] = 1;
    matrix_input.ptrs[0][1] = 2;
    matrix_input.ptrs[0][2] = 3;
    matrix_input.ptrs[1][0] = 4;
    matrix_input.ptrs[1][1] = -20;
    matrix_input.ptrs[1][2] = 6;
    matrix_input.ptrs[2][0] = 7;
    matrix_input.ptrs[2][1] = 8;
    matrix_input.ptrs[2][2] = 9;

    double det;
    int rc = find_determinant(matrix_input, &det);
    ck_assert_int_eq(rc, 0);

    int res = compare_double(det, 300);
    ck_assert_int_eq(res, 0);

    free_matrix(matrix_input);
}

END_TEST

// 6 - Определитель полностью заполненной матрицы отрицателен
START_TEST(pos_test_06)
{
    matrix_t matrix_input = {0};
    matrix_input.row_count = 3;
    matrix_input.column_count = 3;
    allocate_matrix(&matrix_input);
    matrix_input.ptrs[0][0] = 1;
    matrix_input.ptrs[0][1] = 2;
    matrix_input.ptrs[0][2] = 3;
    matrix_input.ptrs[1][0] = 4;
    matrix_input.ptrs[1][1] = 20;
    matrix_input.ptrs[1][2] = 6;
    matrix_input.ptrs[2][0] = 7;
    matrix_input.ptrs[2][1] = 8;
    matrix_input.ptrs[2][2] = 9;

    double det;
    int rc = find_determinant(matrix_input, &det);
    ck_assert_int_eq(rc, 0);

    int res = compare_double(det, -180);
    ck_assert_int_eq(res, 0);

    free_matrix(matrix_input);
}

END_TEST

// 7 - Определитель матрицы из одного элемента
START_TEST(pos_test_07)
{
    matrix_t matrix_input = {0};
    matrix_input.row_count = 1;
    matrix_input.column_count = 1;
    allocate_matrix(&matrix_input);
    matrix_input.ptrs[0][0] = 10;

    double det;
    int rc = find_determinant(matrix_input, &det);
    ck_assert_int_eq(rc, 0);

    int res = compare_double(det, 10);
    ck_assert_int_eq(res, 0);

    free_matrix(matrix_input);
}

END_TEST

// 8 - Тестирование на вещественных числах
START_TEST(pos_test_08)
{
    matrix_t matrix_input = {0};
    matrix_input.row_count = 3;
    matrix_input.column_count = 3;
    allocate_matrix(&matrix_input);
    matrix_input.ptrs[0][0] = 1.00;
    matrix_input.ptrs[0][1] = 2.23;
    matrix_input.ptrs[0][2] = 3.33;
    matrix_input.ptrs[1][0] = 4.5;
    matrix_input.ptrs[1][1] = 20.1;
    matrix_input.ptrs[1][2] = 6.0;
    matrix_input.ptrs[2][0] = 7.4;
    matrix_input.ptrs[2][1] = 8.8;
    matrix_input.ptrs[2][2] = 9.1;

    double det;
    int rc = find_determinant(matrix_input, &det);
    ck_assert_int_eq(rc, 0);

    int res = compare_double(det, -225.632700);
    ck_assert_int_eq(res, 0);

    free_matrix(matrix_input);
}

END_TEST

/*Негативные тесты*/
// 1 - На вход подается неквадратная матрица
START_TEST(neg_test_01)
{
    matrix_t matrix_input = {0};
    matrix_input.row_count = 1;
    matrix_input.column_count = 3;
    allocate_matrix(&matrix_input);
    matrix_input.ptrs[0][0] = 1;
    matrix_input.ptrs[0][1] = 2;
    matrix_input.ptrs[0][2] = 3;

    double det;
    int rc = find_determinant(matrix_input, &det);
    ck_assert_int_eq(rc, 12);

    free_matrix(matrix_input);
    // ck_assert_double_eq(det, );
}

END_TEST

Suite *get_determ_suite(void)
{
    Suite *suite = suite_create("determ_suite");
    TCase *tc = tcase_create("determ");

    tcase_add_test(tc, pos_test_01);
    tcase_add_test(tc, pos_test_02);
    tcase_add_test(tc, pos_test_03);
    tcase_add_test(tc, pos_test_04);
    tcase_add_test(tc, pos_test_05);
    tcase_add_test(tc, pos_test_06);
    tcase_add_test(tc, pos_test_07);
    tcase_add_test(tc, pos_test_08);

    tcase_add_test(tc, neg_test_01);
    suite_add_tcase(suite, tc);

    return suite;
}
