#include "check_clear.h"
#include "associative_array.h"
#include <check.h>

// Очистка пустого массива
START_TEST(test_clear_empty_arr)
{
    assoc_array_t arr = assoc_array_create();

    int rc = assoc_array_clear(arr);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    assoc_array_destroy(&arr);
}

END_TEST

// Очистка массива из одного элемента
START_TEST(test_clear_1_el_arr)
{
    assoc_array_t arr = assoc_array_create();
    int rc = ASSOC_ARRAY_OK;
    rc = assoc_array_insert(arr, "test", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_clear(arr);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *el = NULL;
    rc = assoc_array_find(arr, "test", &el);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}

END_TEST

// Очистка массива из нескольких элементов
START_TEST(test_clear_few_el_arr)
{
    // Создание массива
    assoc_array_t arr = assoc_array_create();
    int rc = ASSOC_ARRAY_OK;
    rc = assoc_array_insert(arr, "test", 0);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "test_1", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "test_2", 2);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "test_3", 3);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_clear(arr);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    // Проверка что элементы отсутствуют
    int *el = NULL;
    rc = assoc_array_find(arr, "test", &el);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    rc = assoc_array_find(arr, "test_1", &el);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    rc = assoc_array_find(arr, "test_2", &el);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    rc = assoc_array_find(arr, "test_3", &el);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}

END_TEST

// Неверный указатель на массив
START_TEST(test_clear_err_pointer)
{
    int rc = assoc_array_clear(NULL);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}

END_TEST

Suite *get_clear_suite(void)
{
    Suite *suite = suite_create("Clear Suite");
    TCase *tcase = tcase_create("clear test");

    tcase_add_test(tcase, test_clear_empty_arr);
    tcase_add_test(tcase, test_clear_1_el_arr);
    tcase_add_test(tcase, test_clear_few_el_arr);
    tcase_add_test(tcase, test_clear_err_pointer);

    suite_add_tcase(suite, tcase);
    return suite;
}
