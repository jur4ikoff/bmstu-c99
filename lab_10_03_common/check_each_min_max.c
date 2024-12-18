#include "check_each_min_max.h"
#include "associative_array.h"
#include <check.h>

/**
 * @brief Функция умножает каждое значение ассоциативного массива на param
 * @param[in] key ключ
 * @param[in] num значение
 * @param[in] param Коээфициент
 */
void mull_num_in_assoc_arr(const char *key, int *num, void *param)
{
    int *coef = param;
    *num *= *coef;
    (void)key;
}

/**
 * @brief Функция делит каждое значение ассоциативного массива на значение param
 * @param[in] key ключ
 * @param[in] num значение
 * @param[in] param Коээфициент
 */
void div_num_in_assoc_arr(const char *key, int *num, void *param)
{
    int *coef = param;
    *num /= *coef;
    (void)key;
}

// Тестировании функции each на функции mull_num_in_assoc_arr. Умножение каждого числа на коэффициент
START_TEST(test_each)
{
    assoc_array_t arr = assoc_array_create();
    int rc = ASSOC_ARRAY_OK;

    rc = assoc_array_insert(arr, "test", 0);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "test_1", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "test_2", 2);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int koef = 2;
    int *pkoef = &koef;
    rc = assoc_array_each(arr, mull_num_in_assoc_arr, pkoef);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *el = NULL;
    rc = assoc_array_find(arr, "test", &el);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = 1;
    if (*el == 0)
        rc = ASSOC_ARRAY_OK;
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_find(arr, "test_1", &el);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = 1;
    if (*el == 2)
        rc = ASSOC_ARRAY_OK;
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_find(arr, "test_2", &el);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = 1;
    if (*el == 4)
        rc = ASSOC_ARRAY_OK;
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    assoc_array_clear(arr);
    assoc_array_destroy(&arr);
}

END_TEST

// Тестировании функции each на другой функции div_num_in_assoc_arr. Деление каждого числа на коэффициент
START_TEST(test_each_2)
{
    assoc_array_t arr = assoc_array_create();
    int rc = ASSOC_ARRAY_OK;

    rc = assoc_array_insert(arr, "test", 2);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "test_1", 4);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "test_2", 5);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int koef = 2;
    int *pkoef = &koef;
    rc = assoc_array_each(arr, div_num_in_assoc_arr, pkoef);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *el = NULL;
    rc = assoc_array_find(arr, "test", &el);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = 1;
    if (*el == 1)
        rc = ASSOC_ARRAY_OK;
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_find(arr, "test_1", &el);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = 1;
    if (*el == 2)
        rc = ASSOC_ARRAY_OK;
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

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

// Тестировании each на массиве из 1 элемента. Деление каждого числа на коэффициент
START_TEST(test_each_on_1_el)
{
    assoc_array_t arr = assoc_array_create();
    int rc = ASSOC_ARRAY_OK;

    rc = assoc_array_insert(arr, "test", 2);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int koef = 2;
    int *pkoef = &koef;
    rc = assoc_array_each(arr, div_num_in_assoc_arr, pkoef);
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

// Тестировании each на пустом массиве Деление каждого числа на коэффициент
START_TEST(test_each_on_empty_arr)
{
    assoc_array_t arr = assoc_array_create();
    int rc = ASSOC_ARRAY_OK;

    int koef = 2;
    int *pkoef = &koef;
    rc = assoc_array_each(arr, div_num_in_assoc_arr, pkoef);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    assoc_array_destroy(&arr);
}

END_TEST

// Тестирование с неверным указателем на массив
START_TEST(test_each_err_ptr_arr)
{
    int koef = 2;
    int *pkoef = &koef;
    int rc = assoc_array_each(NULL, div_num_in_assoc_arr, pkoef);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}

END_TEST

Suite *get_each_suite(void)
{
    Suite *suite = suite_create("Each Suite");
    TCase *tcase = tcase_create("each test");

    tcase_add_test(tcase, test_each);
    tcase_add_test(tcase, test_each_2);
    tcase_add_test(tcase, test_each_on_1_el);
    tcase_add_test(tcase, test_each_err_ptr_arr);
    tcase_add_test(tcase, test_each_on_empty_arr);

    suite_add_tcase(suite, tcase);
    return suite;
}

// Тестирование на пустом массиве
START_TEST(test_min_empty_arr)
{
    assoc_array_t arr = assoc_array_create();
    int rc = ASSOC_ARRAY_OK;

    int *num = NULL;
    rc = assoc_array_min(arr, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}

END_TEST

// Тестирование на массиве из одного элемента
START_TEST(test_min_1_el_arr)
{
    assoc_array_t arr = assoc_array_create();
    int rc = ASSOC_ARRAY_OK;

    rc = assoc_array_insert(arr, "b", 0);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *num = NULL;
    rc = assoc_array_min(arr, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = 1;
    if (*num == 0)
        rc = ASSOC_ARRAY_OK;
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    assoc_array_destroy(&arr);
}

END_TEST

// Тестирование на массиве из нескольких элементов. Минимальный ключ стоит в начале
START_TEST(test_min_first_arr)
{
    assoc_array_t arr = assoc_array_create();
    int rc = ASSOC_ARRAY_OK;

    rc = assoc_array_insert(arr, "a", 120);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "b", 12);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "c", 2);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *num = NULL;
    rc = assoc_array_min(arr, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = 1;
    if (*num == 120)
        rc = ASSOC_ARRAY_OK;
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    assoc_array_clear(arr);
    assoc_array_destroy(&arr);
}

END_TEST

// Тестирование на массиве из нескольких элементов. Минимальный ключ стоит в середине
START_TEST(test_min_middle_arr)
{
    assoc_array_t arr = assoc_array_create();
    int rc = ASSOC_ARRAY_OK;

    rc = assoc_array_insert(arr, "ccs", 120);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "abc", 12);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "bbbc", 2);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *num = NULL;
    rc = assoc_array_min(arr, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = 1;
    if (*num == 12)
        rc = ASSOC_ARRAY_OK;
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    assoc_array_clear(arr);
    assoc_array_destroy(&arr);
}

END_TEST

// Тестирование на массиве из нескольких элементов. Минимальный ключ стоит в конце
START_TEST(test_min_last_arr)
{
    assoc_array_t arr = assoc_array_create();
    int rc = ASSOC_ARRAY_OK;

    rc = assoc_array_insert(arr, "sd", 120);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "qw", 12);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "aa", 2);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *num = NULL;
    rc = assoc_array_min(arr, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = 1;
    if (*num == 2)
        rc = ASSOC_ARRAY_OK;
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    assoc_array_clear(arr);
    assoc_array_destroy(&arr);
}

END_TEST

// Неверный указатель на число
START_TEST(test_min_err_ptr_num)
{
    assoc_array_t arr = assoc_array_create();
    int rc = ASSOC_ARRAY_OK;

    rc = assoc_array_insert(arr, "sd", 120);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "qw", 12);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_min(arr, NULL);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_clear(arr);
    assoc_array_destroy(&arr);
}

END_TEST

// Неверный указатель на число
START_TEST(test_min_err_arr)
{
    int *num = NULL;
    int rc = assoc_array_min(NULL, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}

END_TEST

Suite *get_min_suite(void)
{
    Suite *suite = suite_create("Min Suite");
    TCase *tcase = tcase_create("min test");

    tcase_add_test(tcase, test_min_empty_arr);
    tcase_add_test(tcase, test_min_1_el_arr);
    tcase_add_test(tcase, test_min_first_arr);
    tcase_add_test(tcase, test_min_middle_arr);
    tcase_add_test(tcase, test_min_last_arr);
    tcase_add_test(tcase, test_min_err_ptr_num);
    tcase_add_test(tcase, test_min_err_arr);

    suite_add_tcase(suite, tcase);
    return suite;
}

// Тестирование на пустом массиве
START_TEST(test_max_empty_arr)
{
    assoc_array_t arr = assoc_array_create();
    int rc = ASSOC_ARRAY_OK;

    int *num = NULL;
    rc = assoc_array_max(arr, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}

END_TEST

// Тестирование на массиве из одного элемента
START_TEST(test_max_1_el_arr)
{
    assoc_array_t arr = assoc_array_create();
    int rc = ASSOC_ARRAY_OK;

    rc = assoc_array_insert(arr, "b", 0);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *num = NULL;
    rc = assoc_array_max(arr, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = 1;
    if (*num == 0)
        rc = ASSOC_ARRAY_OK;
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    assoc_array_destroy(&arr);
}

END_TEST

// Тестирование на массиве из нескольких элементов. Минимальный ключ стоит в начале
START_TEST(test_max_first_arr)
{
    assoc_array_t arr = assoc_array_create();
    int rc = ASSOC_ARRAY_OK;

    rc = assoc_array_insert(arr, "daaaaa", 120);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "b", 12);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "c", 2);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *num = NULL;
    rc = assoc_array_max(arr, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = 1;
    if (*num == 120)
        rc = ASSOC_ARRAY_OK;
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    assoc_array_clear(arr);
    assoc_array_destroy(&arr);
}

END_TEST

// Тестирование на массиве из нескольких элементов. Минимальный ключ стоит в середине
START_TEST(test_max_middle_arr)
{
    assoc_array_t arr = assoc_array_create();
    int rc = ASSOC_ARRAY_OK;

    rc = assoc_array_insert(arr, "ab", 120);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "bbbbb", 12);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "aa", 2);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *num = NULL;
    rc = assoc_array_max(arr, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = 1;
    if (*num == 12)
        rc = ASSOC_ARRAY_OK;
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    assoc_array_clear(arr);
    assoc_array_destroy(&arr);
}

END_TEST

// Тестирование на массиве из нескольких элементов. Минимальный ключ стоит в конце
START_TEST(test_max_last_arr)
{
    assoc_array_t arr = assoc_array_create();
    int rc = ASSOC_ARRAY_OK;

    rc = assoc_array_insert(arr, "bb", 120);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "aa", 12);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "qwwww", 2);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *num = NULL;
    rc = assoc_array_max(arr, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = 1;
    if (*num == 2)
        rc = ASSOC_ARRAY_OK;
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    assoc_array_clear(arr);
    assoc_array_destroy(&arr);
}

END_TEST

// Неверный указатель на число
START_TEST(test_max_err_ptr_num)
{
    assoc_array_t arr = assoc_array_create();
    int rc = ASSOC_ARRAY_OK;

    rc = assoc_array_insert(arr, "sd", 120);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "qw", 12);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_max(arr, NULL);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_clear(arr);
    assoc_array_destroy(&arr);
}

END_TEST

// Неверный указатель на число
START_TEST(test_max_err_arr)
{
    int *num = NULL;
    int rc = assoc_array_max(NULL, &num);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
}

END_TEST


Suite *get_max_suite(void)
{
    Suite *suite = suite_create("Max Suite");
    TCase *tcase = tcase_create("max test");

    tcase_add_test(tcase, test_max_empty_arr);
    tcase_add_test(tcase, test_max_1_el_arr);
    tcase_add_test(tcase, test_max_first_arr);
    tcase_add_test(tcase, test_max_middle_arr);
    tcase_add_test(tcase, test_max_last_arr);
    tcase_add_test(tcase, test_max_err_ptr_num);
    tcase_add_test(tcase, test_max_err_arr);

    suite_add_tcase(suite, tcase);
    return suite;
}
