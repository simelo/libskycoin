#include <stdio.h>
#include <stdlib.h>

#include <check.h>
#include "libskycoin.h"
#include "skyerrors.h"
#include "skyassert.h"
#include "skystring.h"
#include "skytest.h"

START_TEST(TestAddressVerify)
{
    cipher__PubKey pubkey;
    cipher__SecKey seckey;
    cipher__PubKey pubkey2;
    cipher__SecKey seckey2;
    cipher__Address addr;

    SKY_cipher_GenerateKeyPair(&pubkey, &seckey);
    SKY_cipher_AddressFromPubKey(&pubkey, &addr);

    // Valid pubkey+address
    ck_assert_msg(SKY_cipher_Address_Verify(&addr, &pubkey) == SKY_OK,
        "Valid pubkey + address");

    SKY_cipher_GenerateKeyPair(&pubkey, &seckey2);
     Invalid pubkey
    ck_assert_msg(SKY_cipher_Address_Verify(&addr, &pubkey) ==
                      SKY_ErrAddressInvalidPubKey,
        " Invalid pubkey");

    // Bad version
    addr.Version = 0x01;
    ck_assert_msg(SKY_cipher_Address_Verify(&addr, &pubkey) ==
                      SKY_ErrAddressInvalidVersion,
        "  Bad version");
}
END_TEST

// define test suite and cases
Suite *common_check_cipher_address(void)
{
  Suite *s = suite_create("Load common check_cipher.address");
  TCase *tc;

  tc = tcase_create("check_cipher.address");
  tcase_add_test(tc, TestAddressVerify);
  suite_add_tcase(s, tc);
  tcase_set_timeout(tc, 150);

  return s;
}
