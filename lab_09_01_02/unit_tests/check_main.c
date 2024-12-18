#include "check.h"
#include "check_find_same_beginning_string.h"
#include "check_sort.h"
#include <stdlib.h>

int main(void)
{
    Suite *same_beg = get_check_same_beg_str();
    Suite *sort_suite = get_sort_suite();

    SRunner *srunner = srunner_create(same_beg);
    srunner_add_suite(srunner, sort_suite);

    srunner_run_all(srunner, CK_NORMAL);

    int fails = srunner_ntests_failed(srunner);
    srunner_free(srunner);
    return (fails) ? EXIT_FAILURE : EXIT_SUCCESS;
}
