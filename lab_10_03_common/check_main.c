#include "check_each_min_max.h"
#include "associative_array.h"
#include "check_clear.h"
#include "check_find.h"
#include "check_insert.h"
#include "check_remove.h"
#include <stdio.h>

#define EXIT_OK 0
#define EXIT_FAIL 1

int main(void)
{
    Suite *suite_insert = get_insert_suite();
    Suite *suite_find = get_find_suite();
    Suite *suite_remove = get_remove_suite();
    Suite *suite_clear = get_clear_suite();
    Suite *suite_each = get_each_suite();
    Suite *suite_min = get_min_suite();
    Suite *suite_max = get_max_suite();

    SRunner *srunner = srunner_create(suite_insert);
    srunner_add_suite(srunner, suite_find);
    srunner_add_suite(srunner, suite_remove);
    srunner_add_suite(srunner, suite_clear);
    srunner_add_suite(srunner, suite_each);
    srunner_add_suite(srunner, suite_min);
    srunner_add_suite(srunner, suite_max);

    srunner_run_all(srunner, CK_NORMAL);
    int fails = srunner_ntests_failed(srunner);
    srunner_free(srunner);
    return (fails) ? EXIT_FAIL : EXIT_OK;
}
