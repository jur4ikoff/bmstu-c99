#include "check_copy.h"
#include "auto.h"
#include "check_pop_front.h"
#include "linked_list.h"
#include <check.h>

// Копирование пустого массива
START_TEST(pos_copy_01)
{
    node_t *head = NULL;
    node_t *new_list = NULL;
    int rc = copy(head, &new_list);
    ck_assert_int_eq(rc, 8);
}

END_TEST

// Копирование массива из 1 элемента
START_TEST(pos_copy_02)
{
    node_t *head = NULL;
    auto_t *temp = create_auto("1", 1980, 10);
    add_to_list(&head, temp);

    node_t *new_list = NULL;
    int rc = copy(head, &new_list);
    ck_assert_int_eq(rc, 0);

    rc = compare_lists(head, new_list);

    free_list(new_list);
    free_full(head);
    ck_assert_int_eq(rc, 0);
}

END_TEST

// Копирование массива из нескольких элементов
START_TEST(pos_copy_03)
{
    node_t *head = NULL;
    auto_t *temp = create_auto("1", 1980, 10);
    add_to_list(&head, temp);
    temp = create_auto("2", 1990, 20);
    add_to_list(&head, temp);
    temp = create_auto("3", 2000, 30);
    add_to_list(&head, temp);

    node_t *new_list = NULL;
    int rc = copy(head, &new_list);
    ck_assert_int_eq(rc, 0);

    rc = compare_lists(head, new_list);

    free_list(new_list);
    free_full(head);
    ck_assert_int_eq(rc, 0);
}

END_TEST

Suite *get_copy_suite(void)
{
    Suite *suite = suite_create("Copy");
    TCase *test_copy = tcase_create("copy");

    tcase_add_test(test_copy, pos_copy_01);
    tcase_add_test(test_copy, pos_copy_02);
tcase_add_test(test_copy, pos_copy_03);

    suite_add_tcase(suite, test_copy);

    return suite;
}
