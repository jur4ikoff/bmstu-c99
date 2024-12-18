#include "check_find_same_beginning_string.h"
#include "array_operations.h"
#include "errors.h"

// Функция для удобной записи в структуру
product_t create_product(char *name, float weight, float volume)
{
    product_t p;
    p.name = name;
    p.weight = weight;
    p.volume = volume;
    return p;
}

// Функция для сравнения массивов типа size_t
static int compare_array(size_t *first, size_t *second, size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        if (first[i] != second[i])
            return ERR_NOT_EQ;
    }
    return ERR_OK;
}

// Положительные тесты
// Тест 1 - Поиск в массиве структур из одного элемента
START_TEST(pos_case_01)
{
    product_t source[] = {
        create_product("apple", 0.3f, 0.4f),
    };
    char request[] = "apple";
    size_t excepted[] = { 1 };
    size_t output[MAX_ELEMENTS];

    int rc = find_same_beginning_string(source, 1, request, output);
    ck_assert_int_eq(rc, 0);

    rc = compare_array(output, excepted, sizeof(excepted) / sizeof(excepted[0]));
    ck_assert_int_eq(rc, 0);
}

END_TEST

// Тест 2 - Поиск одной структуры в массиве из нескольких элементов
START_TEST(pos_case_02)
{
    product_t source[] = {
        create_product("apple", 0.3f, 0.4f),
        create_product("test", 0.3f, 0.4f),
        create_product("ttt", 0.3f, 0.4f)
    };
    char request[] = "apple";
    size_t excepted[] = { 1, 0, 0 };
    size_t output[MAX_ELEMENTS] = { 0 };

    int rc = find_same_beginning_string(source, sizeof(source) / sizeof(source[0]), request, output);
    ck_assert_int_eq(rc, 0);

    rc = compare_array(output, excepted, sizeof(excepted) / sizeof(excepted[0]));
    ck_assert_int_eq(rc, 0);
}

END_TEST

// Тест 3 - Поиск нескольких структур в массиве из нескольких элементов
START_TEST(pos_case_03)
{
    product_t source[] = {
        create_product("apple", 0.3f, 0.4f),
        create_product("test", 0.3f, 0.4f),
        create_product("apple", 0.3f, 0.4f)
    };
    char request[] = "apple";
    size_t excepted[] = { 1, 0, 1 };
    size_t output[MAX_ELEMENTS] = { 0 };

    int rc = find_same_beginning_string(source, sizeof(source) / sizeof(source[0]), request, output);
    ck_assert_int_eq(rc, 0);

    rc = compare_array(output, excepted, sizeof(excepted) / sizeof(excepted[0]));
    ck_assert_int_eq(rc, 0);
}

END_TEST

// Тест 4 - Поиск всех структур в массиве из нескольких элементов
START_TEST(pos_case_04)
{
    product_t source[] = {
        create_product("apple", 0.3f, 0.4f),
        create_product("apple", 0.3f, 0.4f),
        create_product("apple", 0.3f, 0.4f)
    };
    char request[] = "apple";
    size_t excepted[] = { 1, 1, 1 };
    size_t output[MAX_ELEMENTS] = { 0 };

    int rc = find_same_beginning_string(source, sizeof(source) / sizeof(source[0]), request, output);
    ck_assert_int_eq(rc, 0);

    rc = compare_array(output, excepted, sizeof(excepted) / sizeof(excepted[0]));
    ck_assert_int_eq(rc, 0);
}

END_TEST

// Тест 5 - Поиск одной структуры по подстроке в массиве из нескольких элементов
START_TEST(pos_case_05)
{
    product_t source[] = {
        create_product("apple", 0.3f, 0.4f),
        create_product("test", 0.3f, 0.4f),
        create_product("testrr", 0.3f, 0.4f)
    };
    char request[] = "ap";
    size_t excepted[] = { 1, 0, 0 };
    size_t output[MAX_ELEMENTS] = { 0 };

    int rc = find_same_beginning_string(source, sizeof(source) / sizeof(source[0]), request, output);
    ck_assert_int_eq(rc, 0);

    rc = compare_array(output, excepted, sizeof(excepted) / sizeof(excepted[0]));
    ck_assert_int_eq(rc, 0);
}

END_TEST

// Негативные тесты
// Тест 1 - Искомой структуры нет в массиве
START_TEST(neg_case_01)
{
    product_t source[] = {
        create_product("apple", 0.3f, 0.4f),
        create_product("test", 0.3f, 0.4f),
        create_product("testrr", 0.3f, 0.4f)
    };
    char request[] = "p";
    size_t output[MAX_ELEMENTS] = { 0, 0, 0 };

    int rc = find_same_beginning_string(source, sizeof(source) / sizeof(source[0]), request, output);
    ck_assert_int_eq(rc, 6);
}

// Тест 2 - ввел нулевой размер
START_TEST(neg_case_02)
{
    product_t source[] = {
        create_product("apple", 0.3f, 0.4f),
        create_product("test", 0.3f, 0.4f),
        create_product("testrr", 0.3f, 0.4f)
    };
    char request[] = "p";
    size_t output[MAX_ELEMENTS] = { 0, 0, 0 };

    int rc = find_same_beginning_string(source, 0, request, output);
    ck_assert_int_eq(rc, 7);
}

END_TEST

Suite *get_check_same_beg_str(void)
{
    Suite *suite = suite_create("check_same_beg");
    TCase *tc = tcase_create("check_same_beg");

    tcase_add_test(tc, pos_case_01);
    tcase_add_test(tc, pos_case_02);
    tcase_add_test(tc, pos_case_03);
    tcase_add_test(tc, pos_case_04);
    tcase_add_test(tc, pos_case_05);

    tcase_add_test(tc, neg_case_01);
    tcase_add_test(tc, neg_case_02);

    suite_add_tcase(suite, tc);

    return suite;
}
