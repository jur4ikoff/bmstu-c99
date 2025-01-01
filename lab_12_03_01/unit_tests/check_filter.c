// Тесты для функции filter

#include "check_filter.h"
#include "check_shift.h"
#include "myarrlib.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#define ARR_SIZE 5

static int compare_arr(int *arr_1, int *arr_2, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (arr_1[i] != arr_2[i])
            return 1;
    }
    return 0;
}

// Неверный указатель на массив
START_TEST(test_filter_err_arr)
{
    int rc = filter(NULL, NULL, 10, NULL);
    ck_assert_int_eq(rc, 2);
}

// Тестирование размера ноль
START_TEST(test_filter_null_size)
{
    int arr[] = { 1, 2, 3, 4 };
    int rc = filter(NULL, arr, 0, NULL);
    ck_assert_int_eq(rc, 1);
}

END_TEST

// Тестирование на массиве из 1 элемента
START_TEST(test_filter_1_el)
{
    int src[] = { 1 };
    int dst_len = 0;
    int rc = filter(NULL, src, sizeof(src) / sizeof(src[0]), &dst_len);
    ck_assert_int_eq(rc, 0);
    ck_assert_int_eq(dst_len, 1);
    int *dst = malloc(sizeof(int) * dst_len);
    if (!dst)
        ck_abort();

    rc = filter(dst, src, sizeof(src) / sizeof(src[0]), &dst_len);
    ck_assert_int_eq(rc, 0);

    int excepted[] = { 1 };
    rc = compare_arr(dst, excepted, sizeof(excepted) / sizeof(excepted[0]));
    ck_assert_int_eq(rc, 0);
    free(dst);
}

END_TEST

// Тестирование на массиве из 2 элементов (подходят 2 элемента)
START_TEST(test_filter_2_el_appropriate)
{
    int src[] = { 1, 4 };
    int dst_len = 0;
    int rc = filter(NULL, src, sizeof(src) / sizeof(src[0]), &dst_len);
    ck_assert_int_eq(rc, 0);
    ck_assert_int_eq(dst_len, 2);
    int *dst = malloc(sizeof(int) * dst_len);
    if (!dst)
        ck_abort();

    rc = filter(dst, src, sizeof(src) / sizeof(src[0]), &dst_len);
    ck_assert_int_eq(rc, 0);

    int excepted[] = { 1, 4 };
    rc = compare_arr(dst, excepted, sizeof(excepted) / sizeof(excepted[0]));
    ck_assert_int_eq(rc, 0);
    free(dst);
}

END_TEST

// Тестирование на массиве из 2 элементов (подходит 1 элемент)
START_TEST(test_filter_1_el_appropriate)
{
    int src[] = { 1, 3 };
    int dst_len = 0;
    int rc = filter(NULL, src, sizeof(src) / sizeof(src[0]), &dst_len);
    ck_assert_int_eq(rc, 0);
    ck_assert_int_eq(dst_len, 1);
    int *dst = malloc(sizeof(int) * dst_len);
    if (!dst)
        ck_abort();

    rc = filter(dst, src, sizeof(src) / sizeof(src[0]), &dst_len);
    ck_assert_int_eq(rc, 0);

    int excepted[] = { 1 };
    rc = compare_arr(dst, excepted, sizeof(excepted) / sizeof(excepted[0]));
    ck_assert_int_eq(rc, 0);
    free(dst);
}

END_TEST

// пустой вывод
START_TEST(test_filter_empty_output)
{
    int src[] = { 5, 3 };
    int dst_len = 0;
    int rc = filter(NULL, src, sizeof(src) / sizeof(src[0]), &dst_len);
    ck_assert_int_eq(rc, 4);
    ck_assert_int_eq(dst_len, 0);
}

END_TEST

// несколько элементов, один из них ноль
START_TEST(test_filter_several_el)
{
    int src[] = { 13, 3, 0, 4 };
    int dst_len = 0;
    int rc = filter(NULL, src, sizeof(src) / sizeof(src[0]), &dst_len);
    ck_assert_int_eq(rc, 0);
    ck_assert_int_eq(dst_len, 2);
    int *dst = malloc(sizeof(int) * dst_len);
    if (!dst)
        ck_abort();

    rc = filter(dst, src, sizeof(src) / sizeof(src[0]), &dst_len);
    ck_assert_int_eq(rc, 0);

    int excepted[] = { 0, 4 };
    rc = compare_arr(dst, excepted, sizeof(excepted) / sizeof(excepted[0]));
    ck_assert_int_eq(rc, 0);
    free(dst);
}

END_TEST

// несколько элементов, все подходят
START_TEST(test_filter_all_appropriate)
{
    int src[] = { 49, 144, 0, 4 };
    int dst_len = 0;
    int rc = filter(NULL, src, sizeof(src) / sizeof(src[0]), &dst_len);
    ck_assert_int_eq(rc, 0);
    ck_assert_int_eq(dst_len, 4);
    int *dst = malloc(sizeof(int) * dst_len);
    if (!dst)
        ck_abort();

    rc = filter(dst, src, sizeof(src) / sizeof(src[0]), &dst_len);
    ck_assert_int_eq(rc, 0);

    int excepted[] = { 49, 144, 0, 4 };
    rc = compare_arr(dst, excepted, sizeof(excepted) / sizeof(excepted[0]));
    ck_assert_int_eq(rc, 0);
    free(dst);
}

END_TEST

Suite *get_filter_suite(void)
{
    Suite *suite = suite_create("Filter suite");
    TCase *tc = tcase_create("filter");

    tcase_add_test(tc, test_filter_err_arr);
    tcase_add_test(tc, test_filter_null_size);
    tcase_add_test(tc, test_filter_1_el);
    tcase_add_test(tc, test_filter_2_el_appropriate);
    tcase_add_test(tc, test_filter_1_el_appropriate);
    tcase_add_test(tc, test_filter_empty_output);
    tcase_add_test(tc, test_filter_several_el);
    tcase_add_test(tc, test_filter_all_appropriate);

    suite_add_tcase(suite, tc);

    return suite;
}
