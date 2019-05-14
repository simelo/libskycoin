#include <check.h>
#include <stdlib.h>

Suite *common_check_cipher_hash(void);

// run suite
int main(void)
{
    int number_failed = 0;
    int number_failed_fork = 0;
    SRunner *sr = srunner_create(common_check_cipher_hash());
    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    sr = NULL;
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
    // return 0;
} 
