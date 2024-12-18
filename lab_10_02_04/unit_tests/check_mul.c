#include "check_mul.h"
#include "list.h"
#include "number.h"
#include <check.h>

struct node_t_
{
    void *data;
    struct node_t_ *next;
};

int compare_data(const void *a, const void *b)
{
    number_t *num1 = (number_t *)a;
    number_t *num2 = (number_t *)b;

    return num1->prime_number - num2->prime_number + num1->exponentiation - num2->exponentiation;
}

int compare_lists(const void *first, const void *second)
{
    const node_t *list1 = (const node_t *)first;
    const node_t *list2 = (const node_t *)second;

    while (list1 != NULL && list2 != NULL)
    {
        if (compare_data(list1->data, list2->data) != 0)
        {
            return 1; // Списки не равны
        }
        list1 = list1->next;
        list2 = list2->next;
    }

    // Если один список закончился, а другой все еще имеет элементы
    if (list1 != NULL || list2 != NULL)
    {
        return 0; // Списки не равны
    }

    return 0; // Списки равны
}

// Умножение 1 на 1
START_TEST(mult_1_on_1)
{
    long long number_1 = 1;
    long long number_2 = 1;

    node_t *convert_number_1 = NULL, *convert_number_2 = NULL, *excepted = NULL;
    convert_to_list(&convert_number_1, number_1);
    convert_to_list(&convert_number_2, number_2);

    node_t *res = mult_number(convert_number_1, convert_number_2, compare_by_prime);
    convert_to_list(&excepted, 1);

    int rc = compare_lists(res, excepted);
    ck_assert_int_eq(rc, 0);
    free_full(res);
    free_full(excepted);
}

END_TEST

// Умнеожение 1 на число
START_TEST(mult_1_on_number)
{
    long long number_1 = 1;
    long long number_2 = 2;

    node_t *convert_number_1 = NULL, *convert_number_2 = NULL, *excepted = NULL;
    convert_to_list(&convert_number_1, number_1);
    convert_to_list(&convert_number_2, number_2);

    node_t *res = mult_number(convert_number_1, convert_number_2, compare_by_prime);
    convert_to_list(&excepted, 2);

    int rc = compare_lists(res, excepted);
    ck_assert_int_eq(rc, 0);
    free_full(res);
    free_full(excepted);
}

END_TEST

// Умнеожение число на 1
START_TEST(mult_number_on_1)
{
    long long number_1 = 2;
    long long number_2 = 1;

    node_t *convert_number_1 = NULL, *convert_number_2 = NULL, *excepted = NULL;
    convert_to_list(&convert_number_1, number_1);
    convert_to_list(&convert_number_2, number_2);

    node_t *res = mult_number(convert_number_1, convert_number_2, compare_by_prime);
    convert_to_list(&excepted, 2);

    int rc = compare_lists(res, excepted);
    ck_assert_int_eq(rc, 0);
    free_full(res);
    free_full(excepted);
}

END_TEST

// Умножение простого на простое
START_TEST(mult_prim_on_prim)
{
    long long number_1 = 3;
    long long number_2 = 2;

    node_t *convert_number_1 = NULL, *convert_number_2 = NULL, *excepted = NULL;
    convert_to_list(&convert_number_1, number_1);
    convert_to_list(&convert_number_2, number_2);

    node_t *res = mult_number(convert_number_1, convert_number_2, compare_by_prime);
    convert_to_list(&excepted, 6);

    int rc = compare_lists(res, excepted);
    ck_assert_int_eq(rc, 0);
    free_full(res);
    free_full(excepted);
}

END_TEST

// Умножение простого на непростое
START_TEST(mult_prim_on_nonprim)
{
    long long number_1 = 3;
    long long number_2 = 8;

    node_t *convert_number_1 = NULL, *convert_number_2 = NULL, *excepted = NULL;
    convert_to_list(&convert_number_1, number_1);
    convert_to_list(&convert_number_2, number_2);

    node_t *res = mult_number(convert_number_1, convert_number_2, compare_by_prime);
    convert_to_list(&excepted, 24);

    int rc = compare_lists(res, excepted);
    ck_assert_int_eq(rc, 0);
    free_full(res);
    free_full(excepted);
}

END_TEST

// Умножение непростого на непростое
START_TEST(mult_nonprim_on_nonprim)
{
    long long number_1 = 6;
    long long number_2 = 8;

    node_t *convert_number_1 = NULL, *convert_number_2 = NULL, *excepted = NULL;
    convert_to_list(&convert_number_1, number_1);
    convert_to_list(&convert_number_2, number_2);

    node_t *res = mult_number(convert_number_1, convert_number_2, compare_by_prime);
    convert_to_list(&excepted, 48);

    int rc = compare_lists(res, excepted);
    ck_assert_int_eq(rc, 0);
    free_full(res);
    free_full(excepted);
}

END_TEST

// Умножение 1-разрядного числа на 2-разрядное
START_TEST(test_mult_1_bit_on_2_bit)
{
    long long number_1 = 9;
    long long number_2 = 10;

    node_t *convert_number_1 = NULL, *convert_number_2 = NULL, *excepted = NULL;
    convert_to_list(&convert_number_1, number_1);
    convert_to_list(&convert_number_2, number_2);

    node_t *res = mult_number(convert_number_1, convert_number_2, compare_by_prime);
    convert_to_list(&excepted, 90);

    int rc = compare_lists(res, excepted);
    ck_assert_int_eq(rc, 0);
    free_full(res);
    free_full(excepted);
}

END_TEST

// Умножение 2-разрядного числа на 2-разрядное
START_TEST(test_mult_2_bit_on_2_bit)
{
    long long number_1 = 12;
    long long number_2 = 10;

    node_t *convert_number_1 = NULL, *convert_number_2 = NULL, *excepted = NULL;
    convert_to_list(&convert_number_1, number_1);
    convert_to_list(&convert_number_2, number_2);

    node_t *res = mult_number(convert_number_1, convert_number_2, compare_by_prime);
    convert_to_list(&excepted, 120);

    int rc = compare_lists(res, excepted);
    ck_assert_int_eq(rc, 0);
    free_full(res);
    free_full(excepted);
}

END_TEST

Suite *get_mult_suite(void)
{
    Suite *suite = suite_create("Mult");
    TCase *test_mult = tcase_create("multiply");

    tcase_add_test(test_mult, mult_1_on_1);
    tcase_add_test(test_mult, mult_1_on_number);
    tcase_add_test(test_mult, mult_number_on_1);
    tcase_add_test(test_mult, mult_prim_on_prim);
    tcase_add_test(test_mult, mult_prim_on_nonprim);
    tcase_add_test(test_mult, mult_nonprim_on_nonprim);
    tcase_add_test(test_mult, test_mult_1_bit_on_2_bit);
    tcase_add_test(test_mult, test_mult_2_bit_on_2_bit);

    suite_add_tcase(suite, test_mult);

    return suite;
}
