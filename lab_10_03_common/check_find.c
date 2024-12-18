#include "check_find.h"
#include "associative_array.h"
#include <check.h>

// Поиску в пустом массиве
START_TEST(test_clear_empty_arr)
{
    assoc_array_t arr = assoc_array_create();
    int rc = ASSOC_ARRAY_OK;

    int *el_1 = NULL;
    rc = assoc_array_find(arr, "test", &el_1);

    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    assoc_array_clear(arr);
    assoc_array_destroy(&arr);
}

END_TEST

// Поиск в массиве из одного элемента
START_TEST(test_clear_1_el_arr)
{
    assoc_array_t arr = assoc_array_create();
    int rc = ASSOC_ARRAY_OK;
    rc = assoc_array_insert(arr, "test", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *el = NULL;
    rc = assoc_array_find(arr, "test", &el);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = 1;
    if (*el == 1)
        rc = ASSOC_ARRAY_OK;
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    assoc_array_clear(arr);
    assoc_array_destroy(&arr);
}
END_TEST

// Поиск первого элемента в массиве из нескольких элементов
START_TEST(test_find_first_el_arr)
{
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

    int *el = NULL;
    rc = assoc_array_find(arr, "test", &el);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = 1;
    if (*el == 0)
        rc = ASSOC_ARRAY_OK;
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    assoc_array_clear(arr);
    assoc_array_destroy(&arr);
}

END_TEST

// Поиск элемента в середине массива из нескольких элементов
START_TEST(test_find_middle_el_arr)
{
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

    int *el = NULL;
    rc = assoc_array_find(arr, "test_2", &el);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = 1;
    if (*el == 2)
        rc = ASSOC_ARRAY_OK;
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    assoc_array_clear(arr);
    assoc_array_destroy(&arr);
}

END_TEST

// Поиск последнего элемента в массиве из нескольких элементов
START_TEST(test_find_last_el_arr)
{
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

    int *el = NULL;
    rc = assoc_array_find(arr, "test_3", &el);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = 1;
    if (*el == 3)
        rc = ASSOC_ARRAY_OK;
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    assoc_array_clear(arr);
    assoc_array_destroy(&arr);
}

END_TEST

// Поиск элемента, которого нет в массиве
START_TEST(test_find_not_found)
{
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

    int *el = NULL;
    rc = assoc_array_find(arr, "test_4", &el);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    (void)el;
    assoc_array_clear(arr);
    assoc_array_destroy(&arr);
}

END_TEST

// Неверный указатель на массив
START_TEST(test_find_err_arr_pointer)
{
    int *el = NULL;
    int rc = assoc_array_find(NULL, "test_4", &el);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    (void)el;
}

END_TEST


// Неверный указатель на элемент
START_TEST(test_find_err_num_pointer)
{
    assoc_array_t arr = assoc_array_create();
    int rc = assoc_array_find(NULL, "test_4", 0);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    
    assoc_array_destroy(&arr);
}

END_TEST


Suite *get_find_suite(void)
{
    Suite *suite = suite_create("Find Suite");
    TCase *tcase = tcase_create("find test");

    tcase_add_test(tcase, test_clear_empty_arr);
    tcase_add_test(tcase, test_clear_1_el_arr);
    tcase_add_test(tcase, test_find_first_el_arr);
    tcase_add_test(tcase, test_find_middle_el_arr);
    tcase_add_test(tcase, test_find_last_el_arr);
    tcase_add_test(tcase, test_find_not_found);
    tcase_add_test(tcase, test_find_err_arr_pointer);
    tcase_add_test(tcase, test_find_err_num_pointer);

    suite_add_tcase(suite, tcase);
    return suite;
}
