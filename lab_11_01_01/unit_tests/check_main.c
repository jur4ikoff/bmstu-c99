#include "check_my_snprintf.h"

#define EXIT_FAIL 1
#define EXIT_OK 0

int main(void)
{
    Suite *test = get_my_snprintf_suite();
    
    SRunner *srunner = srunner_create(test);

    srunner_run_all(srunner, CK_NORMAL);
    
    int fails = srunner_ntests_failed(srunner);
    srunner_free(srunner);
    return (fails) ? EXIT_FAIL : EXIT_OK;
}
