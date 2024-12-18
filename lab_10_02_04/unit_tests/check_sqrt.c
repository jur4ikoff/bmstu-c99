#include "check_sqrt.h"
#include "check_mul.h"
#include "list.h"
#include "number.h"
#include <check.h>

struct node_t_
{
    void *data;
    struct node_t_ *next;
};

// Возведение в квадрат единицы
START_TEST(test_sqrt_1)
{
    long long number = 1;

    node_t *convert_number_1 = NULL, *excepted = NULL;
    convert_to_list(&convert_number_1, number);

    node_t *res = sqrt_list(convert_number_1);
    convert_to_list(&excepted, 1);

    int rc = compare_lists(res, excepted);
    ck_assert_int_eq(rc, 0);
    free_full(res);
    free_full(excepted);
}

END_TEST

// Возведение в квадрат простого однозначного числа
START_TEST(test_sqrt_1bit_prime_digit)
{
    long long number = 7;

    node_t *convert_number_1 = NULL, *excepted = NULL;
    convert_to_list(&convert_number_1, number);

    node_t *res = sqrt_list(convert_number_1);
    convert_to_list(&excepted, 49);

    int rc = compare_lists(res, excepted);
    ck_assert_int_eq(rc, 0);
    free_full(res);
    free_full(excepted);
}

END_TEST

// Возведение в квадрат непростого однозначного числа
START_TEST(test_sqrt_1bit_nonprime_digit)
{
    long long number = 8;

    node_t *convert_number_1 = NULL, *excepted = NULL;
    convert_to_list(&convert_number_1, number);

    node_t *res = sqrt_list(convert_number_1);
    convert_to_list(&excepted, 64);

    int rc = compare_lists(res, excepted);
    ck_assert_int_eq(rc, 0);
    free_full(res);
    free_full(excepted);
}

END_TEST

// Возведение в квадрат простого числа
START_TEST(test_sqrt_prime_digit)
{
    long long number = 11;

    node_t *convert_number_1 = NULL, *excepted = NULL;
    convert_to_list(&convert_number_1, number);

    node_t *res = sqrt_list(convert_number_1);
    convert_to_list(&excepted, 121);

    int rc = compare_lists(res, excepted);
    ck_assert_int_eq(rc, 0);
    free_full(res);
    free_full(excepted);
}

END_TEST

// Возведение в квадрат непростого числа
START_TEST(test_sqrt_nonprime_digit)
{
    long long number = 12;

    node_t *convert_number_1 = NULL, *excepted = NULL;
    convert_to_list(&convert_number_1, number);

    node_t *res = sqrt_list(convert_number_1);
    convert_to_list(&excepted, 144);

    int rc = compare_lists(res, excepted);
    ck_assert_int_eq(rc, 0);
    free_full(res);
    free_full(excepted);
}

END_TEST

Suite *get_sqrt_suite(void)
{
    Suite *suite = suite_create("Sqrt");
    TCase *test_sqrt = tcase_create("sqrt");

    tcase_add_test(test_sqrt, test_sqrt_1);
    tcase_add_test(test_sqrt, test_sqrt_1bit_prime_digit);
    tcase_add_test(test_sqrt, test_sqrt_1bit_nonprime_digit);
    tcase_add_test(test_sqrt, test_sqrt_prime_digit);
    tcase_add_test(test_sqrt, test_sqrt_nonprime_digit);

    suite_add_tcase(suite, test_sqrt);

    return suite;
}
