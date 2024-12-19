#include "check_insert.h"
#include "associative_array.h"
#include <check.h>
#include <stdio.h>

// Добавление в пустой массив
START_TEST(test_insert_empty_arr)
{
    assoc_array_t arr = assoc_array_create();
    int rc = ASSOC_ARRAY_OK;
    rc = assoc_array_insert(arr, "test", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *el_1 = NULL;
    rc = assoc_array_find(arr, "test", &el_1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = 1;
    if (el_1 && *el_1 == 1)
        rc = ASSOC_ARRAY_OK;
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    assoc_array_clear(arr);
    assoc_array_destroy(&arr);
}

END_TEST

// Добавление в массив из одного элемента
START_TEST(test_insert_1_el_arr)
{
    assoc_array_t arr = assoc_array_create();
    int rc = ASSOC_ARRAY_OK;
    rc = assoc_array_insert(arr, "test", 1);
    rc = assoc_array_insert(arr, "test_1", 2);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *el = NULL;
    rc = assoc_array_find(arr, "test_1", &el);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = 1;
    if (el && *el == 2)
        rc = ASSOC_ARRAY_OK;
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    assoc_array_clear(arr);
    assoc_array_destroy(&arr);
}

END_TEST

// Добавление в массив из нескольких элементов
START_TEST(test_insert_few_el_arr)
{
    assoc_array_t arr = assoc_array_create();
    int rc = ASSOC_ARRAY_OK;
    rc = assoc_array_insert(arr, "test", 1);
    rc = assoc_array_insert(arr, "test_1", 2);
    rc = assoc_array_insert(arr, "test_2", 3);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *el = NULL;
    rc = assoc_array_find(arr, "test_2", &el);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = 1;
    if (el && *el == 3)
        rc = ASSOC_ARRAY_OK;
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    assoc_array_clear(arr);
    assoc_array_destroy(&arr);
}

END_TEST

// Неверный указатель на массив
START_TEST(test_insert_err_pointer_arr)
{
    int rc = ASSOC_ARRAY_OK;
    rc = assoc_array_insert(NULL, "test", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}

END_TEST

// LДобавление элемента с существующим ключем
START_TEST(test_insert_existing_key)
{
    assoc_array_t arr = assoc_array_create();
    int rc = ASSOC_ARRAY_OK;
    rc = assoc_array_insert(arr, "test", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "test_1", 2);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "test_2", 3);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_insert(arr, "test_2", 3);
    ck_assert_int_eq(rc, ASSOC_ARRAY_KEY_EXISTS);

    assoc_array_clear(arr);
    assoc_array_destroy(&arr);
}

END_TEST

Suite *get_insert_suite(void)
{
    Suite *suite = suite_create("Insert Suite");
    TCase *tcase = tcase_create("insert test");

    tcase_add_test(tcase, test_insert_empty_arr);
    tcase_add_test(tcase, test_insert_1_el_arr);
    tcase_add_test(tcase, test_insert_few_el_arr);
    tcase_add_test(tcase, test_insert_err_pointer_arr);
    tcase_add_test(tcase, test_insert_existing_key);

    suite_add_tcase(suite, tcase);
    return suite;
}
