#include <stdlib.h>
#include "errors.h"
#include "array_operations.h"
#include "check_sort.h"

// Функция фильтр копирует в новый массив все до последнего отрицательного элемента
// Позитивные тесты

/**
 * @brief Позитивный тест. Тестирования фильтра, без отрицательных элементов
 */
START_TEST(pos_test_1)
{
    int arr[] = {1, 2, 3, 4, 5};
    int *start_filter = NULL, *end_filter = NULL;
    start_filter = malloc(5 * sizeof(int));

    int rc = key(arr, arr + 5, start_filter, &end_filter);
    ck_assert_int_eq(rc, ERR_OK);

    ck_assert(start_filter != NULL);
    ck_assert(end_filter != NULL);

    ck_assert_int_eq(end_filter - start_filter, 5);
    ck_assert_int_eq(*(start_filter + 0), 1);
    ck_assert_int_eq(*(start_filter + 1), 2);
    ck_assert_int_eq(*(start_filter + 2), 3);
    ck_assert_int_eq(*(start_filter + 3), 4);
    ck_assert_int_eq(*(start_filter + 4), 5);
    free(start_filter);
}
END_TEST

/**
 * @brief Позитивный тест. Тестирования фильтра, отрицательный элемент последний
 */
START_TEST(pos_test_2)
{
    int arr[] = {1, 2, 3, 4, -5};
    int *start_filter = NULL, *end_filter = NULL;
    start_filter = malloc(4 * sizeof(int));

    int rc = key(arr, arr + 5, start_filter, &end_filter);
    ck_assert_int_eq(rc, ERR_OK);

    ck_assert(start_filter != NULL);
    ck_assert(end_filter != NULL);

    ck_assert_int_eq(end_filter - start_filter, 4);
    ck_assert_int_eq(*(start_filter + 0), 1);
    ck_assert_int_eq(*(start_filter + 1), 2);
    ck_assert_int_eq(*(start_filter + 2), 3);
    ck_assert_int_eq(*(start_filter + 3), 4);
    free(start_filter);
}
END_TEST

/**
 * @brief Позитивный тест. отрицательный элемент в середине
 */
START_TEST(pos_test_3)
{
    int arr[] = {1, 2, 3, -4, 5};
    int *start_filter = NULL, *end_filter = NULL;
    start_filter = malloc(3 * sizeof(int));

    int rc = key(arr, arr + 5, start_filter, &end_filter);
    ck_assert_int_eq(rc, ERR_OK);

    ck_assert(start_filter != NULL);
    ck_assert(end_filter != NULL);

    ck_assert_int_eq(end_filter - start_filter, 3);
    ck_assert_int_eq(*(start_filter + 0), 1);
    ck_assert_int_eq(*(start_filter + 1), 2);
    ck_assert_int_eq(*(start_filter + 2), 3);
    free(start_filter);
}
END_TEST

/**
 * @brief Позитивный тест. отрицательный элемент - второй
 */
START_TEST(pos_test_4)
{
    int arr[] = {1, -2, 3, 4, 5};
    int *start_filter = NULL, *end_filter = NULL;
    start_filter = malloc(1 * sizeof(int));

    int rc = key(arr, arr + 5, start_filter, &end_filter);
    ck_assert_int_eq(rc, ERR_OK);

    ck_assert(start_filter != NULL);
    ck_assert(end_filter != NULL);

    ck_assert_int_eq(end_filter - start_filter, 1);
    ck_assert_int_eq(*(start_filter + 0), 1);
    free(start_filter);
}
END_TEST

/**
 * @brief Позитивный тест. Несколько отрицательных тестов
 */
START_TEST(pos_test_5)
{
    int arr[] = {1, -2, 3, 4, -5};
    int *start_filter = NULL, *end_filter = NULL;
    start_filter = malloc(4 * sizeof(int));

    int rc = key(arr, arr + 5, start_filter, &end_filter);
    ck_assert_int_eq(rc, ERR_OK);

    ck_assert(start_filter != NULL);
    ck_assert(end_filter != NULL);

    ck_assert_int_eq(end_filter - start_filter, 4);
    ck_assert_int_eq(*(start_filter + 0), 1);
    ck_assert_int_eq(*(start_filter + 1), -2);
    ck_assert_int_eq(*(start_filter + 2), 3);
    ck_assert_int_eq(*(start_filter + 3), 4);
    free(start_filter);
}
END_TEST

/**
 * @brief Позитивный тест. Все элементы отрицательные
 */
START_TEST(pos_test_6)
{
    int arr[] = {-1, -2, -3, -4, -5};
    int *start_filter = NULL, *end_filter = NULL;
    start_filter = malloc(4 * sizeof(int));

    int rc = key(arr, arr + 5, start_filter, &end_filter);
    ck_assert_int_eq(rc, ERR_OK);

    ck_assert(start_filter != NULL);
    ck_assert(end_filter != NULL);

    ck_assert_int_eq(end_filter - start_filter, 4);
    ck_assert_int_eq(*(start_filter + 0), -1);
    ck_assert_int_eq(*(start_filter + 1), -2);
    ck_assert_int_eq(*(start_filter + 2), -3);
    ck_assert_int_eq(*(start_filter + 3), -4);
    free(start_filter);
}
END_TEST

// НЕГАТИВНЫЙ ТЕСТ
/**
 * @brief Негативный тест. только первый элемент отрицательный
 */
START_TEST(neg_test_1)
{
    int arr[] = {-1, 2, 3, 4};
    int *start_filter = NULL, *end_filter = NULL;

    int rc = key(arr, arr + 4, start_filter, &end_filter);
    ck_assert_int_eq(rc, ERR_POINTER);
}
END_TEST

/**
 * @brief Негативный тест. Неверный указатель на массив
 */
START_TEST(neg_test_2)
{
    int *arr = NULL;
    int *start_filter = NULL, *end_filter = NULL;

    int rc = key(arr, arr + 4, start_filter, &end_filter);
    ck_assert_int_eq(rc, ERR_POINTER);
}
END_TEST

/**
 * @brief Негативный тест. Указатель на начало больше указателя на конец
 */
START_TEST(neg_test_3)
{
    int arr[] = {-1, 2, 3, 4};
    int *start_filter = NULL, *end_filter = NULL;

    int rc = key(arr + 4, arr, start_filter, &end_filter);
    ck_assert_int_eq(rc, ERR_POINTER);
}
END_TEST

Suite *get_key_suite(void)
{
    Suite *suite = suite_create("Key tests");
    TCase *tc = tcase_create("Key");

    tcase_add_test(tc, pos_test_1);
    tcase_add_test(tc, pos_test_2);
    tcase_add_test(tc, pos_test_3);
    tcase_add_test(tc, pos_test_4);
    tcase_add_test(tc, pos_test_5);
    tcase_add_test(tc, pos_test_6);

    tcase_add_test(tc, neg_test_1);
    tcase_add_test(tc, neg_test_2);
    tcase_add_test(tc, neg_test_3);

    suite_add_tcase(suite, tc);
    return suite;
}
