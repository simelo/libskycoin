#include <check.h>
#include <stdlib.h>

#include "test_main_common.h"

// run suite
int main(void)
{
    int number_failed = 0;
    SRunner* sr = srunner_create(common_check_cipher_hash());
    srunner_add_suite(sr, common_check_cipher_address());
    srunner_add_suite(sr, common_check_cipher_crypto());
    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    sr = NULL;
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
