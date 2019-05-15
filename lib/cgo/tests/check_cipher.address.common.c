#include <stdio.h>
#include <stdlib.h>

#include <check.h>
#include "libskycoin.h"
#include "skyerrors.h"
#include "skyassert.h"
#include "skystring.h"
#include "skytest.h"

// buffer big enough to hold all kind of data needed by test cases
unsigned char buff[1024];

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
    // Invalid pubkey
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

START_TEST(TestAddressString)
{
    cipher__PubKey pk;
    cipher__SecKey sk;
    cipher__Address addr, addr2, addr3;
    GoString str = {buff, 0};

    GoUint32 err = SKY_cipher_GenerateKeyPair(&pk, &sk);
    ck_assert(err == SKY_OK);
    err = SKY_cipher_AddressFromPubKey(&pk, &addr);
    ck_assert(err == SKY_OK);
    GoString_ tmpstr = {str.p, str.n};

    err = SKY_cipher_Address_String(&addr, &tmpstr);
    ck_assert(err == SKY_OK);
    str.n = tmpstr.n;
    str.p = tmpstr.p;
    ck_assert(SKY_cipher_DecodeBase58Address(str, &addr2) == SKY_OK);
    ck_assert(isAddressEq(&addr, &addr2));

    SKY_cipher_Address_String(&addr2, (GoString_*)&str);
    ck_assert(SKY_cipher_DecodeBase58Address(str, &addr3) == SKY_OK);
    ck_assert(isAddressEq(&addr, &addr2));
}
END_TEST

// define test suite and cases
Suite *common_check_cipher_address(void)
{
  Suite *s = suite_create("Load common check_cipher.address");
  TCase *tc;

  tc = tcase_create("check_cipher.address");
  tcase_add_test(tc, TestAddressVerify);
  tcase_add_test(tc, TestAddressString);
  suite_add_tcase(s, tc);
  tcase_set_timeout(tc, 150);

  return s;
}
