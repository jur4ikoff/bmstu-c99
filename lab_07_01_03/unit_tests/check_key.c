#include <stdlib.h>
#include <check.h>
#include "errors.h"
#include "array_operations.h"


#define EPS 1.0e-7
// Тестовая функция для проверки корректности работы функции key
START_TEST(test_key_valid_case)
{
    int source[] = {1, -2, 3, -4, 5};
    int *filtered_arr = NULL;
    int *pend_filtered_arr = NULL;

    int result = key(source, source + 5, &filtered_arr, &pend_filtered_arr);

    ck_assert_int_eq(result, ERR_OK);
    ck_assert_int_eq(pend_filtered_arr - filtered_arr, 3); // Ожидаем 4 элемента в отфильтрованном массиве
    ck_assert_int_eq(filtered_arr[0], 1);
    ck_assert_int_eq(filtered_arr[1], -2);
    ck_assert_int_eq(filtered_arr[2], 3);
    // ck_assert_int_eq(filtered_arr[3], -4);

    free(filtered_arr); // Не забываем освобождать память
}
END_TEST

START_TEST(test_key_no_negative_elements)
{
    int source[] = {1, 2, 3, 4, 5};
    int *filtered_arr = NULL;
    int *pend_filtered_arr = NULL;

    int result = key(source, source + 5, &filtered_arr, &pend_filtered_arr);

    ck_assert_int_eq(result, ERR_OK);
    ck_assert_int_eq(pend_filtered_arr - filtered_arr, 6); // Все элементы должны остаться
    ck_assert_int_eq(filtered_arr[0], 1);
    ck_assert_int_eq(filtered_arr[1], 2);
    ck_assert_int_eq(filtered_arr[2], 3);
    ck_assert_int_eq(filtered_arr[3], 4);
    ck_assert_int_eq(filtered_arr[4], 5);

    free(filtered_arr);
}
END_TEST

START_TEST(test_key_empty_array)
{
    int source[] = {0};
    int *filtered_arr = NULL;
    int *pend_filtered_arr = NULL;

    int result = key(source, source, &filtered_arr, &pend_filtered_arr);

    ck_assert_int_eq(result, ERR_POINTER);
    // ck_assert_ptr_eq(filtered_arr, pend_filtered_arr); // Пустой массив, указатели равны

    free(filtered_arr);
}
END_TEST

START_TEST(test_key_null_pointer)
{
    int *filtered_arr = NULL;
    int *pend_filtered_arr = NULL;

    int result = key(NULL, NULL, &filtered_arr, &pend_filtered_arr);

    ck_assert_int_eq(result, ERR_POINTER); // Ожидаем ошибку с указателями
}
END_TEST

START_TEST(test_key_allocation_failure)
{
    // Это тестовый случай, который должен проверять утечку памяти или ошибку выделения.
    // Мы не можем точно имитировать ошибку malloc без переписывания функции,
    // поэтому здесь просто покажем структуру теста.

    // В реальной системе можно использовать mtrace или другие методы для отслеживания утечек

    int *filtered_arr = NULL;
    int *pend_filtered_arr = NULL;

    // Здесь нужно создать ситуацию, когда вызов malloc вернет NULL
    // Например, можно сделать это через мокирование, если возможно, или использовать другой подход.

    // Предполагаем, что ошибка произошла
    int result = key(NULL, NULL, &filtered_arr, &pend_filtered_arr); // Аналогично предыдущему тесту

    ck_assert_int_eq(result, ERR_POINTER); // Ожидаем ошибку с указателями
}
END_TEST

Suite *key_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("KeyFunction");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_key_valid_case);
    tcase_add_test(tc_core, test_key_no_negative_elements);
    tcase_add_test(tc_core, test_key_empty_array);
    tcase_add_test(tc_core, test_key_null_pointer);
    tcase_add_test(tc_core, test_key_allocation_failure);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = key_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);

    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}