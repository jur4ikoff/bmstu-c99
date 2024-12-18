#include "check_find.h"
#include "auto.h"
#include "linked_list.h"
#include <check.h>
#include <stdlib.h>

/* Функция для сравнения структуры данных auto_t с его содержимым. Выводит 0, если совпадает и 1 в другом случае*/
static int auto_t_comparator(void *data, char *name, int year, long long price)
{
    auto_t *auto_data = (auto_t *)data;
    if (strcmp(auto_data->model_name, name) == 0 && auto_data->year == year && auto_data->price == price)
        return 0;
    return 1;
}

// Поиск структуры, отсутствующей в листе
START_TEST(pos_find_01)
{
    node_t *head = NULL;
    auto_t *temp = create_auto("1", 1980, 10);
    add_to_list(&head, temp);
    temp = create_auto("2", 1980, 10);
    add_to_list(&head, temp);
    temp = create_auto("3", 1980, 10);
    add_to_list(&head, temp);
    temp = create_auto("4", 1980, 10);
    add_to_list(&head, temp);

    auto_t *data = create_auto("4", 1990, 10);
    node_t *found = find(head, data, comparator_by_year);

    int rc = 1;
    if (!found)
        rc = 0;

    free_auto(data);
    free_full(head);
    ck_assert_int_eq(rc, 0);
}

// Поиск структуры в списке из 1 элемента. Структура стоит первой
START_TEST(pos_find_02)
{
    node_t *head = NULL;
    auto_t *temp = create_auto("1", 1970, 10);
    add_to_list(&head, temp);

    auto_t *data = create_auto("2", 1970, 10);
    node_t *found = find(head, data, comparator_by_year);

    int rc = 1;
    if (found)
        rc = 0;

    free_auto(data);
    free_full(head);
    ck_assert_int_eq(rc, 0);
}

END_TEST

// Поиск структуры в списке из нескольких элементов. Структура стоит первой
START_TEST(pos_find_03)
{
    node_t *head = NULL;
    auto_t *temp = create_auto("1", 1970, 10);
    add_to_list(&head, temp);
    temp = create_auto("2", 1980, 10);
    add_to_list(&head, temp);
    temp = create_auto("3", 1990, 10);
    add_to_list(&head, temp);

    auto_t *data = create_auto("2", 1970, 10);
    node_t *found = find(head, data, comparator_by_year);

    int rc = 1;
    if (found)
        rc = 0;

    free_auto(data);
    free_full(head);
    ck_assert_int_eq(rc, 0);
}

END_TEST

// Поиск структуры в списке из нескольких элементов. Структура стоит в середине
START_TEST(pos_find_04)
{
    node_t *head = NULL;
    auto_t *temp = create_auto("1", 1970, 10);
    add_to_list(&head, temp);
    temp = create_auto("2", 1980, 10);
    add_to_list(&head, temp);
    temp = create_auto("3", 1990, 10);
    add_to_list(&head, temp);
    temp = create_auto("4", 2000, 10);
    add_to_list(&head, temp);

    auto_t *data = create_auto("2", 1990, 10);
    node_t *found = find(head, data, comparator_by_year);

    int rc = 1;
    if (found)
        rc = 0;

    free_auto(data);
    free_full(head);
    ck_assert_int_eq(rc, 0);
}

END_TEST

// Поиск структуры в списке из нескольких элементов. Структура стоит в конце
START_TEST(pos_find_05)
{
    node_t *head = NULL;
    auto_t *temp = create_auto("1", 1970, 10);
    add_to_list(&head, temp);
    temp = create_auto("2", 1980, 10);
    add_to_list(&head, temp);
    temp = create_auto("3", 1990, 30);
    add_to_list(&head, temp);
    temp = create_auto("4", 2000, 10);
    add_to_list(&head, temp);

    auto_t *data = create_auto("2", 2000, 10);
    node_t *found = find(head, data, comparator_by_year);

    int rc = auto_t_comparator(found->data, "4", 2000, 10);
    free_auto(data);
    free_full(head);
    ck_assert_int_eq(rc, 0);
}

END_TEST

// Поиск структуры в списке из нескольких элементов. Подходит несколько элементов. Моя функция выводит только первый подходящий элемент
START_TEST(pos_find_06)
{
    node_t *head = NULL;
    auto_t *temp = create_auto("1", 1970, 10);
    add_to_list(&head, temp);
    temp = create_auto("2", 1980, 10);
    add_to_list(&head, temp);
    temp = create_auto("3", 1980, 10);
    add_to_list(&head, temp);
    temp = create_auto("4", 2000, 10);
    add_to_list(&head, temp);

    auto_t *data = create_auto("2", 1980, 10);
    node_t *found = find(head, data, comparator_by_year);
    int rc = auto_t_comparator(found->data, "2", 1980, 10);

    free_auto(data);
    free_full(head);
    ck_assert_int_eq(rc, 0);
}

END_TEST

// Проверка работы функции с другим компаратором. Компаратор по году и цене
START_TEST(pos_find_07)
{
    node_t *head = NULL;
    auto_t *temp = create_auto("1", 1970, 10);
    add_to_list(&head, temp);
    temp = create_auto("2", 1980, 10);
    add_to_list(&head, temp);
    temp = create_auto("3", 2000, 10);
    add_to_list(&head, temp);
    temp = create_auto("4", 2000, 20);
    add_to_list(&head, temp);

    auto_t *data = create_auto("2", 2000, 20);
    node_t *found = find(head, data, comparator_by_price_and_year);
    int rc = auto_t_comparator(found->data, "4", 2000, 20);

    free_auto(data);
    free_full(head);
    ck_assert_int_eq(rc, 0);
}

END_TEST

// Указатель на список равен NULL
START_TEST(pos_find_08)
{
    node_t *head = NULL;

    auto_t *data = create_auto("2", 2000, 20);
    node_t *found = find(head, data, comparator_by_price_and_year);

    int rc = 1;
    if (found == NULL)
        rc = 0;

    free_auto(data);
    free_full(head);
    ck_assert_int_eq(rc, 0);
}

END_TEST

// Указатель на данные равен NULL
START_TEST(pos_find_09)
{
    node_t *head = NULL;
    auto_t *temp = create_auto("2", 1980, 10);
    add_to_list(&head, temp);
    temp = create_auto("3", 2000, 10);
    add_to_list(&head, temp);
    temp = create_auto("4", 2000, 20);
    add_to_list(&head, temp);
    node_t *found = find(head, NULL, comparator_by_price_and_year);

    int rc = 1;
    if (found == NULL)
        rc = 0;

    free_full(head);
    ck_assert_int_eq(rc, 0);
}

END_TEST

// Указатель на компаратор равен NULL
START_TEST(pos_find_10)
{
    node_t *head = NULL;
    auto_t *temp = create_auto("2", 1980, 10);
    add_to_list(&head, temp);
    temp = create_auto("3", 2000, 10);
    add_to_list(&head, temp);
    temp = create_auto("4", 2000, 20);
    add_to_list(&head, temp);

    auto_t *data = create_auto("2", 2000, 20);
    node_t *found = find(head, data, NULL);

    int rc = 1;
    if (found == NULL)
        rc = 0;

    free_auto(data);
    free_full(head);
    ck_assert_int_eq(rc, 0);
}

END_TEST

Suite *get_find_suite(void)
{
    Suite *suite = suite_create("Find");

    TCase *test_find = tcase_create("find");
    tcase_add_test(test_find, pos_find_01);
    tcase_add_test(test_find, pos_find_02);
    tcase_add_test(test_find, pos_find_03);
    tcase_add_test(test_find, pos_find_04);
    tcase_add_test(test_find, pos_find_05);
    tcase_add_test(test_find, pos_find_06);
    tcase_add_test(test_find, pos_find_07);
    tcase_add_test(test_find, pos_find_08);
    tcase_add_test(test_find, pos_find_09);
    tcase_add_test(test_find, pos_find_10);

    suite_add_tcase(suite, test_find);

    return suite;
}
