#include "check_sort.h"
#include <string.h>
#include "errors.h"
#include "array_operations.h"

#define EPS 10e-6

typedef struct
{
    int first;
    int second;
} test_struct;

static int test_structs_compare(const void *a, const void *b)
{
    const test_struct *a_t = a;
    const test_struct *b_t = b;
    if (a_t->first != b_t->first)
        return a_t->first - b_t->first;
    else
        return a_t->second - b_t->second;
}

static int test_structs_arr_compare(test_struct first_arr[], test_struct second_arr[], size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        if (test_structs_compare(&first_arr[i], &second_arr[i]) != 0)
            return ERR_NOT_EQ;
    }

    return ERR_OK;
}

static int char_arr_compare(char first_arr[], char second_arr[], size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        if (char_compare(&first_arr[i], &second_arr[i]) != 0)
            return ERR_NOT_EQ;
    }

    return ERR_OK;
}

static int double_arr_compare(double first_arr[], double second_arr[], size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        if (double_compare(&first_arr[i], &second_arr[i]) != ERR_OK)
            return ERR_NOT_EQ;
    }

    return ERR_OK;
}

/*Начнем с позитивных тестов.*/

/**
 * @brief Позитивный тест, сортировка массива из 6 элементов, в случайном порядке
 */
START_TEST(pos_test_1)
{
    int arr[] = {19, 12, 32, 21, 1, 4};
    int arr_expected[] = {1, 4, 12, 19, 21, 32};
    mysort(arr, sizeof(arr) / sizeof(int), sizeof(int), int_compare);
    int rc = int_arr_compare(arr, arr_expected, sizeof(arr) / sizeof(arr[0]));
    ck_assert_int_eq(rc, ERR_OK);
}
END_TEST

/**
 * @brief Позитивный тест, сортировка массива из 1 элемента
 */
START_TEST(pos_test_2)
{
    int arr[] = {19};
    int arr_expected[] = {19};
    mysort(arr, sizeof(arr) / sizeof(arr[0]), sizeof(arr[0]), int_compare);
    int rc = int_arr_compare(arr, arr_expected, sizeof(arr) / sizeof(arr[0]));
    ck_assert_int_eq(rc, ERR_OK);
}
END_TEST

/**
 * @brief Позитивный тест, сортировка массива из нескольких отрицательных элементов, в случайном порядке
 */
START_TEST(pos_test_3)
{
    int arr[] = {-19, -5, -12, -4};
    int arr_expected[] = {-19, -12, -5, -4};
    mysort(arr, sizeof(arr) / sizeof(int), sizeof(int), int_compare);
    int rc = int_arr_compare(arr, arr_expected, sizeof(arr) / sizeof(arr[0]));
    ck_assert_int_eq(rc, ERR_OK);
}
END_TEST

/**
 * @brief Позитивный тест, сортировка массива из нескольких элементов разных по знаку, в случайном порядке
 */
START_TEST(pos_test_4)
{
    int arr[] = {-19, -5, 12, -4};
    int arr_expected[] = {-19, -5, -4, 12};
    mysort(arr, sizeof(arr) / sizeof(int), sizeof(int), int_compare);
    int rc = int_arr_compare(arr, arr_expected, sizeof(arr) / sizeof(arr[0]));
    ck_assert_int_eq(rc, ERR_OK);
}
END_TEST

/**
 * @brief Позитивный тест, сортировка отсортированного массива из положительных элементов.
 */
START_TEST(pos_test_5)
{
    int arr[] = {1, 5, 12, 14};
    int arr_expected[] = {1, 5, 12, 14};
    mysort(arr, sizeof(arr) / sizeof(int), sizeof(int), int_compare);
    int rc = int_arr_compare(arr, arr_expected, sizeof(arr) / sizeof(arr[0]));
    ck_assert_int_eq(rc, ERR_OK);
}
END_TEST

/**
 * @brief Позитивный тест, сортировка отсортированного в обратном порядке массива из положительных элементов.
 */
START_TEST(pos_test_6)
{
    int arr[] = {14, 12, 5, 1};
    int arr_expected[] = {1, 5, 12, 14};
    mysort(arr, sizeof(arr) / sizeof(arr[0]), sizeof(int), int_compare);
    int rc = int_arr_compare(arr, arr_expected, sizeof(arr) / sizeof(arr[0]));
    ck_assert_int_eq(rc, ERR_OK);
}
END_TEST

/**
 * @brief Позитивный тест, проверка работы на массиве структур.
 */
START_TEST(pos_test_7)
{
    test_struct a = {10, 2};
    test_struct b = {2, 2};
    test_struct c = {2, 3};
    test_struct arr[] = {a, b, c};
    test_struct arr_expected[] = {b, c, a};
    mysort(arr, sizeof(arr) / sizeof(arr[0]), sizeof(test_struct), test_structs_compare);
    int rc = test_structs_arr_compare(arr, arr_expected, sizeof(arr) / sizeof(arr[0]));
    ck_assert_int_eq(rc, ERR_OK);
}
END_TEST

/**
 * @brief Позитивный тест, сортировка массива символов
 */
START_TEST(pos_test_8)
{
    char arr[] = {'a', 'c', 'd', 'b'};
    char arr_expected[] = {'a', 'b', 'c', 'd'};
    mysort(arr, sizeof(arr) / sizeof(arr[0]), sizeof(char), char_compare);
    int rc = char_arr_compare(arr, arr_expected, sizeof(arr) / sizeof(arr[0]));
    ck_assert_int_eq(rc, ERR_OK);
}
END_TEST

/**
 * @brief Позитивный тест, сортировка массива вещественных чисел
 */
START_TEST(pos_test_9)
{
    double arr[] = {1.12, 2.3, 4.3, 1.1};
    double arr_expected[] = {1.1, 1.12, 2.3, 4.3};
    mysort(arr, sizeof(arr) / sizeof(arr[0]), sizeof(double), double_compare);
    int rc = double_arr_compare(arr, arr_expected, sizeof(arr) / sizeof(arr[0]));
    ck_assert_int_eq(rc, ERR_OK);
}
END_TEST

/*Отрицательные тесты*/

/**
 * @brief Отрицательный тест, введение размера 0
 */
START_TEST(neg_test_1)
{
    int arr[] = {14, 12, 5, 1};
    int arr_expected[] = {14, 12, 5, 1};
    mysort(arr, 0, sizeof(int), int_compare);
    int rc = int_arr_compare(arr, arr_expected, sizeof(arr) / sizeof(arr[0]));
    ck_assert_int_eq(rc, ERR_OK);
}
END_TEST

Suite *get_sort_suite(void)
{
    Suite *suite = suite_create("Sort tests");
    TCase *tc = tcase_create("Sort");

    tcase_add_test(tc, pos_test_1);
    tcase_add_test(tc, pos_test_2);
    tcase_add_test(tc, pos_test_3);
    tcase_add_test(tc, pos_test_4);
    tcase_add_test(tc, pos_test_5);
    tcase_add_test(tc, pos_test_6);
    tcase_add_test(tc, pos_test_7);
    tcase_add_test(tc, pos_test_8);
    tcase_add_test(tc, pos_test_9);
    tcase_add_test(tc, neg_test_1);

    suite_add_tcase(suite, tc);
    return suite;
}
