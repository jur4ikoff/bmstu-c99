#include "check_find.h"
#include "check_pop_front.h"
#include "check_copy.h"
#include "check_sort.h"

#define EXIT_FAIL 1
#define EXIT_OK 0

int main(void)
{
    Suite *find = get_find_suite();
    Suite *pop = get_pop_front_suite();
    Suite *copy = get_copy_suite();
    Suite *sort = get_sort_suite();

    SRunner *srunner = srunner_create(find);
    srunner_add_suite(srunner, pop);
    srunner_add_suite(srunner, copy);
    srunner_add_suite(srunner, sort);

    srunner_run_all(srunner, CK_NORMAL);
    int fails = srunner_ntests_failed(srunner);
    srunner_free(srunner);

    return (fails) ? EXIT_FAIL : EXIT_OK;
}
