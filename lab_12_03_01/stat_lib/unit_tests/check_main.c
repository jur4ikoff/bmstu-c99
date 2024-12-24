
#include "check_sort.h"
#include "check_key.h"
#include <stdlib.h>


int main(void)
{
    Suite *sort = get_sort_suite();
    Suite *key = get_key_suite();
    
    SRunner *srunner = srunner_create(sort);
    srunner_add_suite(srunner, key);
    srunner_run_all(srunner, CK_NORMAL); //CK_VERBOSE

    int fails = srunner_ntests_failed(srunner);
    srunner_free(srunner);
    return (fails) ? EXIT_FAILURE : EXIT_SUCCESS;
}
