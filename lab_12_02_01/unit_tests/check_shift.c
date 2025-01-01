#include "check_shift.h"
#include "check.h"
#include "myarrlib.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_EL_COUNT 5

static int compare_arr(int *arr_1, int *arr_2, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (arr_1[i] != arr_2[i])
            return 1;
    }
    return 0;
}

void print_arr(int *arr, size_t size)
{

    for (size_t i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Сдвиг на ноль элементов
START_TEST(test_shift_null)
{
    int arr[MAX_EL_COUNT] = { 1, 2, 3, 4, 5 };
    shift_arr(arr, sizeof(arr) / sizeof(arr[0]), 5);
    int excepted[MAX_EL_COUNT] = { 1, 2, 3, 4, 5 };
    int rc = compare_arr(arr, excepted, sizeof(arr) / sizeof(arr[0]));
    ck_assert_int_eq(rc, 0);
}

// Сдвиг на 1 элемент влево
START_TEST(test_shift_one)
{
    int arr[MAX_EL_COUNT] = { 1, 2, 3, 4, 5 };
    shift_arr(arr, sizeof(arr) / sizeof(arr[0]), 1);
    int excepted[MAX_EL_COUNT] = { 2, 3, 4, 5, 1 };
    int rc = compare_arr(arr, excepted, sizeof(arr) / sizeof(arr[0]));
    ck_assert_int_eq(rc, 0);
}

// Сдвиг на размер массива - 1
START_TEST(test_shift_size_1)
{
    int arr[MAX_EL_COUNT] = { 1, 2, 3, 4, 5 };
    shift_arr(arr, sizeof(arr) / sizeof(arr[0]), 4);
    int excepted[MAX_EL_COUNT] = { 5, 1, 2, 3, 4 };
    int rc = compare_arr(arr, excepted, sizeof(arr) / sizeof(arr[0]));
    ck_assert_int_eq(rc, 0);
}

// Сдвиг на размер массива
START_TEST(test_shift_eq_size)
{
    int arr[MAX_EL_COUNT] = { 1, 2, 3, 4, 5 };
    shift_arr(arr, sizeof(arr) / sizeof(arr[0]), 5);
    int excepted[MAX_EL_COUNT] = { 1, 2, 3, 4, 5 };
    int rc = compare_arr(arr, excepted, sizeof(arr) / sizeof(arr[0]));
    ck_assert_int_eq(rc, 0);
}

// Сдвиг больше размера массива
START_TEST(test_shift_bigger_size)
{
    int arr[MAX_EL_COUNT] = { 1, 2, 3, 4, 5 };
    shift_arr(arr, sizeof(arr) / sizeof(arr[0]), 7);
    int excepted[MAX_EL_COUNT] = { 3, 4, 5, 1, 2 };
    int rc = compare_arr(arr, excepted, sizeof(arr) / sizeof(arr[0]));
    ck_assert_int_eq(rc, 0);
}

// Сдвиг отрицательный
START_TEST(test_shift_negative)
{
    int arr[MAX_EL_COUNT] = { 1, 2, 3, 4, 5 };
    shift_arr(arr, sizeof(arr) / sizeof(arr[0]), -1);
    int excepted[MAX_EL_COUNT] = { 5, 1, 2, 3, 4 };
    int rc = compare_arr(arr, excepted, sizeof(arr) / sizeof(arr[0]));
    ck_assert_int_eq(rc, 0);
}

// Сдвиг отрицательный на размер массива
START_TEST(test_shift_negative_size)
{
    int arr[MAX_EL_COUNT] = { 1, 2, 3, 4, 5 };
    shift_arr(arr, sizeof(arr) / sizeof(arr[0]), -5);
    int excepted[MAX_EL_COUNT] = { 1, 2, 3, 4, 5 };
    int rc = compare_arr(arr, excepted, sizeof(arr) / sizeof(arr[0]));
    ck_assert_int_eq(rc, 0);
}

// Сдвиг отрицательный на размер массива - 1
START_TEST(test_shift_negative_size_minus_one)
{
    int arr[MAX_EL_COUNT] = { 1, 2, 3, 4, 5 };
    shift_arr(arr, sizeof(arr) / sizeof(arr[0]), -4);
    int excepted[MAX_EL_COUNT] = { 2, 3, 4, 5, 1 };
    int rc = compare_arr(arr, excepted, sizeof(arr) / sizeof(arr[0]));
    ck_assert_int_eq(rc, 0);
}

// Размер меньше актуального
START_TEST(test_shift_err_count)
{
    int arr[MAX_EL_COUNT] = { 1, 2, 3, 4, 5 };
    shift_arr(arr, 3, 1);
    int excepted[MAX_EL_COUNT] = { 2, 3, 1 };
    int rc = compare_arr(arr, excepted, 3);
    ck_assert_int_eq(rc, 0);
}

// Размер ноль
START_TEST(test_shift_err_count_null)
{
    int arr[MAX_EL_COUNT] = { 1, 2, 3, 4, 5 };
    int rc = shift_arr(arr, 0, 1);
    ck_assert_int_eq(rc, 1);
}

// Размер отрицательный
START_TEST(test_shift_err_count_neg)
{
    int arr[MAX_EL_COUNT] = { 1, 2, 3, 4, 5 };
    int rc = shift_arr(arr, -10, 1);
    ck_assert_int_eq(rc, 1);
}

// неверный указатель на массив
START_TEST(test_shift_err_arr_pointer)
{
    int *arr = NULL;
    int rc = shift_arr(arr, 4, 4);
    ck_assert_int_eq(rc, 2);
}

// Тестирование на динамическом массиве
START_TEST(test_shift_dyn_arr)
{
    int *arr = calloc(5, sizeof(int));
    arr[0] = 1;
    int rc = shift_arr(arr, 5, 1);
    ck_assert_int_eq(rc, 0);
    
    int excepted[MAX_EL_COUNT] = { 0, 0, 0, 0, 1 };
    rc = compare_arr(arr, excepted, 5);
    ck_assert_int_eq(rc, 0);
    free(arr);
}

Suite *get_shift_suite(void)
{
    Suite *suite = suite_create("shift suite");
    TCase *tc = tcase_create("shift");

    tcase_add_test(tc, test_shift_null);
    tcase_add_test(tc, test_shift_one);
    tcase_add_test(tc, test_shift_size_1);
    tcase_add_test(tc, test_shift_eq_size);
    tcase_add_test(tc, test_shift_bigger_size);

    tcase_add_test(tc, test_shift_negative);
    tcase_add_test(tc, test_shift_negative_size);
    tcase_add_test(tc, test_shift_negative_size_minus_one);

    tcase_add_test(tc, test_shift_err_count);
    tcase_add_test(tc, test_shift_err_count_null);
    tcase_add_test(tc, test_shift_err_count_neg);
    tcase_add_test(tc, test_shift_err_arr_pointer);
    tcase_add_test(tc, test_shift_dyn_arr);

    suite_add_tcase(suite, tc);

    return suite;
}
