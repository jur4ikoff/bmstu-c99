#include "check_mul.h"
#include "check_sqrt.h"
#include "check_div.h"
#include <check.h>

#define EXIT_FAIL 1
#define EXIT_OK 0

int main(void)
{

    Suite *mult = get_mult_suite();
    Suite *sqrt = get_sqrt_suite();
    Suite *div = get_div_suite();

    SRunner *srunner = srunner_create(mult);
    srunner_add_suite(srunner, sqrt);
    srunner_add_suite(srunner, div);

    srunner_run_all(srunner, CK_NORMAL);
    int fails = srunner_ntests_failed(srunner);
    srunner_free(srunner);

    return (fails) ? EXIT_FAIL : EXIT_OK;
}
