#include "check_sort.h"
#include "array_operations.h"
#include "errors.h"
#include "io.h"
#include <stdlib.h>

// Функция для удобной записи структуры
static product_t create_product(char *name, float weight, float volume)
{
    product_t p;
    p.name = name;
    p.weight = weight;
    p.volume = volume;
    return p;
}

// Сравнение массива структур
static int compare_products(product_t *first, product_t *second, size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        if (strcmp(first[i].name, second[i].name) != 0 || fabs(first[i].weight - second[i].weight) > EPS || fabs(first[i].volume - second[i].volume) > EPS)
            return ERR_NOT_EQ;
    }
    return ERR_OK;
}

// Позитиные тесты
// 1 - Сортировка массива одного элемента
START_TEST(pos_case_01)
{
    product_t source[] = {
        create_product("apple", 1.0f, 1.0f),
    };

    product_t excepted[] = {
        create_product("apple", 1.0f, 1.0f),
    };

    sort_products_by_density(source, sizeof(source) / sizeof(source[0]));
    int rc = compare_products(source, excepted, sizeof(source) / sizeof(source[0]));
    ck_assert_int_eq(rc, 0);
}

END_TEST

// 2 - Сортировка отсортированного массива
START_TEST(pos_case_02)
{
    product_t source[] = {
        create_product("a", 0.1f, 1.0),
        create_product("test", 0.5f, 1.0f),
        create_product("apple", 1.0f, 1.0f)
    };

    product_t excepted[] = {
        create_product("a", 0.1f, 1.0),
        create_product("test", 0.5f, 1.0f),
        create_product("apple", 1.0f, 1.0f)
    };

    sort_products_by_density(source, sizeof(source) / sizeof(source[0]));
    int rc = compare_products(source, excepted, sizeof(source) / sizeof(source[0]));
    ck_assert_int_eq(rc, 0);
}

END_TEST

// 3 - Сортировка обратно отсортированного массива
START_TEST(pos_case_03)
{
    product_t source[] = {
        create_product("apple", 1.0f, 1.0f),
        create_product("test", 0.5f, 1.0f),
        create_product("a", 0.1f, 1.0)
    };

    product_t excepted[] = {
        create_product("a", 0.1f, 1.0),
        create_product("test", 0.5f, 1.0f),
        create_product("apple", 1.0f, 1.0f)
    };

    sort_products_by_density(source, sizeof(source) / sizeof(source[0]));
    int rc = compare_products(source, excepted, sizeof(source) / sizeof(source[0]));
    ck_assert_int_eq(rc, 0);
}

END_TEST

// 4 - Сортировка случайного массива
START_TEST(pos_case_04)
{
    product_t source[] = {
        create_product("apple", 0.2f, 1.0f),
        create_product("c", 1.5f, 1.0f),
        create_product("b", 0.5f, 1.0f),
        create_product("test", 0.5f, 1.0f),
        create_product("a", 0.1f, 1.0)
    };

    product_t excepted[] = {
        create_product("a", 0.1f, 1.0),
        create_product("apple", 0.2f, 1.0f),
        create_product("b", 0.5f, 1.0f),
        create_product("test", 0.5f, 1.0f),
        create_product("c", 1.5f, 1.0f),
    };

    sort_products_by_density(source, sizeof(source) / sizeof(source[0]));
    int rc = compare_products(source, excepted, sizeof(source) / sizeof(source[0]));
    ck_assert_int_eq(rc, 0);
}

// 5 - Сортировка случайного массива (С отрицательными числами)
START_TEST(pos_case_05)
{
    product_t source[] = {
        create_product("apple", -1.0f, 1.0f),
        create_product("c", 1.5f, 1.0f),
        create_product("b", 0.5f, 1.0f),
        create_product("test", 0.5f, 1.0f),
        create_product("a", 0.1f, 1.0)
    };

    product_t excepted[] = {
        create_product("apple", -1.0f, 1.0f),
        create_product("a", 0.1f, 1.0),
        create_product("b", 0.5f, 1.0f),
        create_product("test", 0.5f, 1.0f),
        create_product("c", 1.5f, 1.0f),
    };

    sort_products_by_density(source, sizeof(source) / sizeof(source[0]));
    int rc = compare_products(source, excepted, sizeof(source) / sizeof(source[0]));
    ck_assert_int_eq(rc, 0);
}

END_TEST

// 1 - Негативный тест, вызов сортировки с размером 0
START_TEST(neg_case_01)
{
    product_t source[] = {
        create_product("apple", -1.0f, 1.0f),
        create_product("c", 1.5f, 1.0f),
        create_product("b", 0.5f, 1.0f),
        create_product("test", 0.5f, 1.0f),
        create_product("a", 0.1f, 1.0)
    };

    product_t excepted[] = {
        create_product("apple", -1.0f, 1.0f),
        create_product("c", 1.5f, 1.0f),
        create_product("b", 0.5f, 1.0f),
        create_product("test", 0.5f, 1.0f),
        create_product("a", 0.1f, 1.0)
    };

    sort_products_by_density(source, 0);
    int rc = compare_products(source, excepted, sizeof(source) / sizeof(source[0]));
    ck_assert_int_eq(rc, 0);
}

END_TEST

Suite *get_sort_suite(void)
{
    Suite *suite = suite_create("check sort");
    TCase *tc = tcase_create("sort");

    tcase_add_test(tc, pos_case_01);
    tcase_add_test(tc, pos_case_02);
    tcase_add_test(tc, pos_case_03);
    tcase_add_test(tc, pos_case_04);
    tcase_add_test(tc, pos_case_05);

    tcase_add_test(tc, neg_case_01);

    suite_add_tcase(suite, tc);

    return suite;
}
