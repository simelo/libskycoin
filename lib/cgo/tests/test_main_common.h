#ifndef TEST_MAIN_COMMON_H
#define TEST_MAIN_COMMON_H

#include <check.h>
#include <stdlib.h>

Suite *common_check_cipher_hash(void);
Suite *common_check_cipher_address(void);
Suite *common_check_cipher_crypto(void);

#endif  // TEST_MAIN_COMMON_H
