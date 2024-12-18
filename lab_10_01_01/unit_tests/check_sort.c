#include "check_sort.h"
#include "auto.h"
#include "check_pop_front.h"
#include "linked_list.h"
#include <check.h>

// Вместо указатель на компаратор передается указатель на NULL
START_TEST(sort_null_comparator)
{
    node_t *head = NULL;
    auto_t *temp = create_auto("test", 10, 10);
    add_to_list(&head, temp);
    node_t *new_head = sort(head, NULL);
    int rc = 1;
    

    if (new_head == NULL)
        rc = 0;

    ck_assert_int_eq(rc, 0);
    free_full(head);
    free_full(new_head);
}

END_TEST

// Вместо указатель на компаратор передается указатель на NULL
START_TEST(sort_null_head)
{
    node_t *head = NULL;
    head = sort(head, comparator_by_price);
    int rc = 1;

    if (head == NULL)
        rc = 0;

    ck_assert_int_eq(rc, 0);
    free_full(head);
}

// Сортировка списка из 1 элемента
START_TEST(sort_one_el)
{
    node_t *head = NULL;
    auto_t *temp = create_auto("test", 10, 10);
    add_to_list(&head, temp);
    head = sort(head, comparator_by_price);

    node_t *excepted_result = NULL;
    temp = create_auto("test", 10, 10);
    add_to_list(&head, temp);

    int rc = compare_lists(head, excepted_result);
    ck_assert_int_eq(rc, 0);
    free_full(head);
    free_full(excepted_result);
}

END_TEST

// Сортировка списка из 2 элементов
START_TEST(sort_couple_el)
{
    node_t *head = NULL;
    auto_t *temp = create_auto("test", 10, 10);
    add_to_list(&head, temp);
    temp = create_auto("2", 2, 100);
    add_to_list(&head, temp);
    head = sort(head, comparator_by_price);

    node_t *excepted_result = NULL;
    temp = create_auto("test", 10, 10);
    add_to_list(&head, temp);
    temp = create_auto("2", 2, 100);
    add_to_list(&head, temp);

    int rc = compare_lists(head, excepted_result);
    ck_assert_int_eq(rc, 0);
    free_full(head);
    free_full(excepted_result);
}

END_TEST

// Сортировка отсортированного списка из нескольких элементов
START_TEST(sort_sorted_list)
{
    node_t *head = NULL;
    auto_t *temp = create_auto("test", 2, 2);
    add_to_list(&head, temp);
    temp = create_auto("2", 10, 10);
    add_to_list(&head, temp);
    temp = create_auto("3", 100, 100);
    add_to_list(&head, temp);
    head = sort(head, comparator_by_price);

    node_t *excepted_result = NULL;
    temp = create_auto("test", 2, 2);
    add_to_list(&head, temp);
    temp = create_auto("3", 10, 10);
    add_to_list(&head, temp);
    temp = create_auto("2", 100, 100);
    add_to_list(&head, temp);

    int rc = compare_lists(head, excepted_result);
    ck_assert_int_eq(rc, 0);
    free_full(head);
    free_full(excepted_result);
}

END_TEST

// Сортировка отсортированного в обратном порядке списка из нескольких элементов
START_TEST(sort_reverse_list)
{
    node_t *head = NULL;
    auto_t *temp = create_auto("test", 100, 100);
    add_to_list(&head, temp);
    temp = create_auto("2", 10, 10);
    add_to_list(&head, temp);
    temp = create_auto("3", 2, 2);
    add_to_list(&head, temp);
    head = sort(head, comparator_by_price);

    node_t *excepted_result = NULL;
    temp = create_auto("test", 100, 100);
    add_to_list(&head, temp);
    temp = create_auto("3", 10, 10);
    add_to_list(&head, temp);
    temp = create_auto("2", 2, 2);
    add_to_list(&head, temp);

    int rc = compare_lists(head, excepted_result);
    ck_assert_int_eq(rc, 0);
    free_full(head);
    free_full(excepted_result);
}

END_TEST

// Сортировка случайного списка
START_TEST(sort_random_list)
{
    node_t *head = NULL;
    auto_t *temp = create_auto("test", 5, 5);
    add_to_list(&head, temp);
    temp = create_auto("2", 10, 10);
    add_to_list(&head, temp);
    temp = create_auto("3", 2, 2);
    add_to_list(&head, temp);
    head = sort(head, comparator_by_price);

    node_t *excepted_result = NULL;
    temp = create_auto("test", 5, 5);
    add_to_list(&head, temp);
    temp = create_auto("3", 10, 10);
    add_to_list(&head, temp);
    temp = create_auto("2", 2, 2);
    add_to_list(&head, temp);

    int rc = compare_lists(head, excepted_result);
    ck_assert_int_eq(rc, 0);
    free_full(head);
    free_full(excepted_result);
}

END_TEST

// Проверка на другом компораторе
START_TEST(sort_another_comparator)
{
    node_t *head = NULL;
    auto_t *temp = create_auto("test", 5, 5);
    add_to_list(&head, temp);
    temp = create_auto("2", 10, 10);
    add_to_list(&head, temp);
    temp = create_auto("3", 2, 2);
    add_to_list(&head, temp);
    head = sort(head, comparator_by_year);

    node_t *excepted_result = NULL;
    temp = create_auto("test", 5, 5);
    add_to_list(&head, temp);
    temp = create_auto("3", 10, 10);
    add_to_list(&head, temp);
    temp = create_auto("2", 2, 2);
    add_to_list(&head, temp);

    int rc = compare_lists(head, excepted_result);
    ck_assert_int_eq(rc, 0);
    free_full(head);
    free_full(excepted_result);
}

END_TEST

Suite *get_sort_suite(void)
{
    Suite *suite = suite_create("Sort");
    TCase *test_sort = tcase_create("sort");

    tcase_add_test(test_sort, sort_null_comparator);
    tcase_add_test(test_sort, sort_null_head);
    tcase_add_test(test_sort, sort_one_el);
    tcase_add_test(test_sort, sort_couple_el);
    tcase_add_test(test_sort, sort_sorted_list);
    tcase_add_test(test_sort, sort_reverse_list);
    tcase_add_test(test_sort, sort_random_list);
    tcase_add_test(test_sort, sort_another_comparator);

    suite_add_tcase(suite, test_sort);
    return suite;
}
