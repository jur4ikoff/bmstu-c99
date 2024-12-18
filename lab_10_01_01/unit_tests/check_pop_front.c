#include "check_pop_front.h"
#include "auto.h"
#include "linked_list.h"
#include <check.h>
#include <stdlib.h>

/* Функция для сравнения структуры данных auto_t с его содержимым. Выводит 0, если совпадает и 1 в другом случае*/
int auto_t_comparator(void *data, char *name, int year, long long price)
{
    auto_t *auto_data = (auto_t *)data;
    if (strcmp(auto_data->model_name, name) == 0 && auto_data->year == year && auto_data->price == price)
        return 0;
    return 1;
}

int compare_data(const void *first, const void *second)
{
    const auto_t *data1 = (const auto_t *)first;
    const auto_t *data2 = (const auto_t *)second;

    if (strcmp(data1->model_name, data2->model_name) == 0 && data1->year == data2->year && data1->price == data2->price)
        return 0;

    return 1;
}

int compare_lists(const void *first, const void *second)
{
    const node_t *list1 = (const node_t *)first;
    const node_t *list2 = (const node_t *)second;

    while (list1 != NULL && list2 != NULL)
    {
        if (compare_data(list1->data, list2->data) != 0)
        {
            return 1; // Списки не равны
        }
        list1 = list1->next;
        list2 = list2->next;
    }

    // Если один список закончился, а другой все еще имеет элементы
    if (list1 != NULL || list2 != NULL)
    {
        return 0; // Списки не равны
    }

    return 0; // Списки равны
}

// Удаление из пустого списка
START_TEST(test_pop_01)
{
    node_t *head = NULL;
    auto_t *data = NULL;
    data = pop_front(&head);

    int rc = 1;
    if (data == NULL)
        rc = 0;

    free_auto(data);
    free_full(head);
    ck_assert_int_eq(rc, 0);
}

END_TEST

// Удаление из списка из одного элемента
START_TEST(test_pop_02)
{
    node_t *head = NULL;
    auto_t *temp = create_auto("1", 1980, 10);
    add_to_list(&head, temp);

    auto_t *data = NULL;
    data = pop_front(&head);

    int rc = auto_t_comparator(data, "1", 1980, 10);
    ck_assert_int_eq(rc, 0);

    if (head)
        rc = 1;

    free_auto(data);
    free_full(head);
    ck_assert_int_eq(rc, 0);
}

END_TEST

// Удаление из списка из двух элементов
START_TEST(test_pop_03)
{
    node_t *head = NULL;
    auto_t *temp = create_auto("1", 1980, 10);
    add_to_list(&head, temp);
    temp = create_auto("2", 1970, 20);
    add_to_list(&head, temp);

    auto_t *data = NULL;
    data = pop_front(&head);

    int rc = auto_t_comparator(data, "1", 1980, 10);
    ck_assert_int_eq(rc, 0);

    node_t *excepted_list = NULL;
    temp = create_auto("2", 1970, 20);
    add_to_list(&excepted_list, temp);

    rc = compare_lists(head, excepted_list);

    free_auto(data);
    free_full(excepted_list);
    free_full(head);
    ck_assert_int_eq(rc, 0);
}

END_TEST

// Удаление из списка из нескольких элементов
START_TEST(test_pop_04)
{
    node_t *head = NULL;
    auto_t *temp = create_auto("1", 1980, 10);
    add_to_list(&head, temp);
    temp = create_auto("2", 1970, 20);
    add_to_list(&head, temp);
    temp = create_auto("3", 1990, 30);
    add_to_list(&head, temp);

    auto_t *data = NULL;
    data = pop_front(&head);

    int rc = auto_t_comparator(data, "1", 1980, 10);
    ck_assert_int_eq(rc, 0);

    node_t *excepted_list = NULL;
    temp = create_auto("2", 1970, 20);
    add_to_list(&excepted_list, temp);
    temp = create_auto("3", 1990, 30);
    add_to_list(&head, temp);

    rc = compare_lists(head, excepted_list);

    free_auto(data);
    free_full(excepted_list);
    free_full(head);
    ck_assert_int_eq(rc, 0);
}

END_TEST
Suite *get_pop_front_suite(void)
{
    Suite *suite = suite_create("Pop");

    TCase *test_pop = tcase_create("pop");
    tcase_add_test(test_pop, test_pop_01);
    tcase_add_test(test_pop, test_pop_02);
    tcase_add_test(test_pop, test_pop_03);
    tcase_add_test(test_pop, test_pop_04);

    suite_add_tcase(suite, test_pop);

    return suite;
}
