#include "check_shift.h"
#include "check_filter.h"
#include <check.h>

#define EXIT_FAIL 1
#define EXIT_OK 0

int main(void)
{
    Suite *shift = get_shift_suite();
    Suite *filter = get_filter_suite();

    SRunner *srunner = srunner_create(shift);
    srunner_add_suite(srunner, filter);

    srunner_run_all(srunner, CK_NORMAL);

    int fails = srunner_ntests_failed(srunner);
    srunner_free(srunner);
    return (fails) ? EXIT_FAIL : EXIT_OK;
}
