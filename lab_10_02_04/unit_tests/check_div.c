#include "check_mul.h"
#include "check_sqrt.h"
#include "list.h"
#include "number.h"
#include <check.h>

struct node_t_
{
    void *data;
    struct node_t_ *next;
};

// Деление числа на 0
START_TEST(test_div_0)
{
    long long number_1 = 1;
    long long number_2 = 0;

    node_t *res = div_list(number_1, number_2);
    int rc = 1;
    if (res == NULL)
        rc = 0;
    // convert_to_list(&excepted, 120);

    // int rc = compare_lists(res, excepted);
    ck_assert_int_eq(rc, 0);
    free_full(res);
}

END_TEST

// Деление отрицательного на положительное
START_TEST(test_div_neg_pos)
{
    long long number_1 = -1;
    long long number_2 = 1;

    node_t *res = div_list(number_1, number_2);
    int rc = 1;
    if (res == NULL)
        rc = 0;
    // convert_to_list(&excepted, 120);

    // int rc = compare_lists(res, excepted);
    ck_assert_int_eq(rc, 0);
    free_full(res);
}

END_TEST

// Деление положительного на отрицательное
START_TEST(test_div_pos_neg)
{
    long long number_1 = 1;
    long long number_2 = -1;

    node_t *res = div_list(number_1, number_2);
    int rc = 1;
    if (res == NULL)
        rc = 0;

    ck_assert_int_eq(rc, 0);
    free_full(res);
}

END_TEST

// Деление на единицу
START_TEST(test_div_on_1)
{
    long long number_1 = 2;
    long long number_2 = 1;

    node_t *excepted = NULL;
    node_t *res = div_list(number_1, number_2);
    int rc = 1;
    if (res == NULL)
        rc = 0;

    convert_to_list(&excepted, 2);

    rc = compare_lists(res, excepted);
    ck_assert_int_eq(rc, 0);
    free_full(res);
    free_full(excepted);
}

END_TEST

// Деление на простое число
START_TEST(test_div_on_prim)
{
    long long number_1 = 7;
    long long number_2 = 3;

    node_t *excepted = NULL;
    node_t *res = div_list(number_1, number_2);
    int rc = 1;
    if (res == NULL)
        rc = 0;

    convert_to_list(&excepted, 2);

    rc = compare_lists(res, excepted);
    ck_assert_int_eq(rc, 0);
    free_full(res);
    free_full(excepted);
}

END_TEST

// Деление на простое число
START_TEST(test_div_on_nonprim)
{
    long long number_1 = 7;
    long long number_2 = 4;

    node_t *excepted = NULL;
    node_t *res = div_list(number_1, number_2);
    int rc = 1;
    if (res == NULL)
        rc = 0;

    convert_to_list(&excepted, 1);

    rc = compare_lists(res, excepted);
    ck_assert_int_eq(rc, 0);
    free_full(res);
    free_full(excepted);
}

END_TEST

// Деление нацело
START_TEST(test_div_full)
{
    long long number_1 = 8;
    long long number_2 = 4;

    node_t *excepted = NULL;
    node_t *res = div_list(number_1, number_2);
    int rc = 1;
    if (res == NULL)
        rc = 0;

    convert_to_list(&excepted, 2);

    rc = compare_lists(res, excepted);
    ck_assert_int_eq(rc, 0);
    free_full(res);
    free_full(excepted);
}

END_TEST

// Деление с остатоком
START_TEST(test_div_remains)
{
    long long number_1 = 12;
    long long number_2 = 5;

    node_t *excepted = NULL;
    node_t *res = div_list(number_1, number_2);
    int rc = 1;
    if (res == NULL)
        rc = 0;

    convert_to_list(&excepted, 2);

    rc = compare_lists(res, excepted);
    ck_assert_int_eq(rc, 0);
    free_full(res);
    free_full(excepted);
}

END_TEST


Suite *get_div_suite(void)
{
    Suite *suite = suite_create("Div");
    TCase *test_div = tcase_create("div");

    tcase_add_test(test_div, test_div_0);
    tcase_add_test(test_div, test_div_neg_pos);
    tcase_add_test(test_div, test_div_pos_neg);
    tcase_add_test(test_div, test_div_on_1);
    tcase_add_test(test_div, test_div_on_prim);
    tcase_add_test(test_div, test_div_on_nonprim);
    tcase_add_test(test_div, test_div_full);
    tcase_add_test(test_div, test_div_remains);

    suite_add_tcase(suite, test_div);

    return suite;
}
