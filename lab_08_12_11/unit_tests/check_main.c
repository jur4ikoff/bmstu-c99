#include "check_find_determinant.h"
#include "check_add.h"
#include "check_mult.h"
#include <stdlib.h>

int main(void)
{
    Suite *det = get_determ_suite();
    Suite *add = get_add_suite();
    Suite *mult = get_mult_suite();

    SRunner *srunner = srunner_create(det);
    srunner_add_suite(srunner, add);
    srunner_add_suite(srunner, mult);

    srunner_run_all(srunner, CK_NORMAL);

    int fails = srunner_ntests_failed(srunner);
    srunner_free(srunner);
    return (fails) ? EXIT_FAILURE : EXIT_SUCCESS;
}
