#include "check_copy.h"
#include "array_operations.h"
#include "errors.h"
#include <stdlib.h>
#include "dlfcn.h"

/**
 * @brief Функция загружает функции из динамической библиотеки
 * @param handle Указатель на переменную для работы с dl. Должна быть после dlopen
 * @param[in] load Структура указателей на функцию
 * @return код возврата
 */
int load_test_functions_from_dyn_lib(void *handle, test_func_load_t *load)
{
    if (handle == NULL)
        return ERR_POINTER;

    void *cur = NULL;
    cur = dlsym(handle, "copy_array");
    if (cur == NULL)
    {
        return ERR_LOAD_LIB;
    }
    *(void **)&load->copy_array = cur;

    cur = dlsym(handle, "mysort");
    if (cur == NULL)
    {
        return ERR_LOAD_LIB;
    }
    *(void **)&load->mysort = cur;

    cur = dlsym(handle, "key");
    if (cur == NULL)
    {
        return ERR_LOAD_LIB;
    }
    *(void **)&load->key = cur;
    return ERR_OK;
}

// Функция фильтр копирует в новый массив все до последнего отрицательного элемента
// Позитивные тесты

static int arr_compare(int *first_arr, int *second_arr, size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        if (first_arr[i] != second_arr[i])
            return ERR_NOT_EQ;
    }

    return ERR_OK;
}

// Тестирование на обычным массиве
START_TEST(pos_test_01)
{
    int arr[] = {1, 2, 3, 4, 5};
    int *start_filter = NULL, *end_filter = NULL;
    start_filter = malloc(5 * sizeof(int));

    void *lib = dlopen("./out/libfilter.so", RTLD_LAZY);
    test_func_load_t load = {0};
    load_test_functions_from_dyn_lib(lib, &load);

    int rc = load.copy_array(arr, arr + 5, start_filter, &end_filter);
    ck_assert_int_eq(rc, ERR_OK);

    ck_assert(start_filter != NULL);
    ck_assert(end_filter != NULL);

    ck_assert_int_eq(end_filter - start_filter, 5);
    rc = arr_compare(arr, start_filter, 5);
    ck_assert_int_eq(rc, 0);

    free(start_filter);
    dlclose(lib);
}

END_TEST

// Тестирование на массиве из 1 элемента
START_TEST(pos_test_02)
{
    int arr[] = {1};
    int *start_filter = NULL, *end_filter = NULL;
    start_filter = malloc(1 * sizeof(int));

    void *lib = dlopen("./out/libfilter.so", RTLD_LAZY);
    test_func_load_t load = {0};
    load_test_functions_from_dyn_lib(lib, &load);

    int rc = load.copy_array(arr, arr + 1, start_filter, &end_filter);
    ck_assert_int_eq(rc, ERR_OK);

    ck_assert(start_filter != NULL);
    ck_assert(end_filter != NULL);

    ck_assert_int_eq(end_filter - start_filter, 1);
    rc = arr_compare(arr, start_filter, 1);
    ck_assert_int_eq(rc, 0);

    free(start_filter);
    dlclose(lib);
}

END_TEST

// Тестирование на пустом массиве
START_TEST(neg_test_01)
{
    void *lib = dlopen("./out/libfilter.so", RTLD_LAZY);
    test_func_load_t load = {0};
    load_test_functions_from_dyn_lib(lib, &load);
    int *start_filter = NULL, *end_filter = NULL;

    int rc = load.copy_array(NULL, NULL, start_filter, &end_filter);
    ck_assert_int_eq(rc, ERR_POINTER);
    dlclose(lib);
}

END_TEST

Suite *get_copy_suite(void)
{
    Suite *suite = suite_create("Copy tests");
    TCase *tc = tcase_create("copy");

    tcase_add_test(tc, pos_test_01);
    tcase_add_test(tc, pos_test_02);
    tcase_add_test(tc, neg_test_01);

    suite_add_tcase(suite, tc);
    return suite;
}
