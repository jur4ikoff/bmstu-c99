#include "check_remove.h"
#include "associative_array.h"
#include <check.h>

// Удаление из пустого массива
START_TEST(test_clear_empty_arr)
{
    assoc_array_t arr = assoc_array_create();
    int rc = ASSOC_ARRAY_OK;

    rc = assoc_array_remove(arr, "test");
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

    rc = assoc_array_remove(arr, "test");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    assoc_array_destroy(&arr);
}

END_TEST

// Удаление первого элемента из массива из нескольких элементов
START_TEST(test_clear_few_el_arr)
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
    rc = assoc_array_insert(arr, "test_4", 4);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_remove(arr, "test");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *el = NULL;
    rc = assoc_array_find(arr, "test", &el);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_clear(arr);
    assoc_array_destroy(&arr);
}

END_TEST

// Удаление элемента из середины массива из нескольких элементов
START_TEST(test_remove_middle_el_arr)
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
    rc = assoc_array_insert(arr, "test_4", 4);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_remove(arr, "test_2");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *el = NULL;
    rc = assoc_array_find(arr, "test_2", &el);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_clear(arr);
    assoc_array_destroy(&arr);
}

END_TEST

// Удаление элемента из середины массива из нескольких элементов
START_TEST(test_remove_last_el_arr)
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
    rc = assoc_array_insert(arr, "test_4", 4);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_remove(arr, "test_4");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *el = NULL;
    rc = assoc_array_find(arr, "test_4", &el);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_clear(arr);
    assoc_array_destroy(&arr);
}

END_TEST

// Удаление элемента, которого нет в массиве
START_TEST(test_remove_no_el)
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

    rc = assoc_array_remove(arr, "test_4");
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_clear(arr);
    assoc_array_destroy(&arr);
}

END_TEST

// Удаление элемента, неверный указатель на массив
START_TEST(test_remove_err_arr_pointer)
{
    int rc = assoc_array_remove(NULL, "test_4");
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}

END_TEST

// Удаление элемента, неверный указатель на ключ
START_TEST(test_remove_err_key_pointer)
{
    assoc_array_t arr = assoc_array_create();
    int rc = assoc_array_remove(arr, NULL);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    assoc_array_destroy(&arr);
}

END_TEST

Suite *get_remove_suite(void)
{
    Suite *suite = suite_create("Remove Suite");
    TCase *tcase = tcase_create("remove test");

    tcase_add_test(tcase, test_clear_empty_arr);
    tcase_add_test(tcase, test_clear_1_el_arr);
    tcase_add_test(tcase, test_clear_few_el_arr);
    tcase_add_test(tcase, test_remove_middle_el_arr);
    tcase_add_test(tcase, test_remove_last_el_arr);

    tcase_add_test(tcase, test_remove_no_el);
    tcase_add_test(tcase, test_remove_no_el);
    tcase_add_test(tcase, test_remove_err_arr_pointer);
    tcase_add_test(tcase, test_remove_err_key_pointer);

    suite_add_tcase(suite, tcase);
    return suite;
}
