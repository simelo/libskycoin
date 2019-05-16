#include <stdio.h>
#include <stdlib.h>

#include <check.h>
#include "libskycoin.h"
#include "skyerrors.h"
#include "skyassert.h"
#include "skystring.h"
#include "skytest.h"

START_TEST(TestNewPubKey)
{
    unsigned char buff[101];
    GoSlice slice;
    cipher__PubKey pk, pk2;
    cipher__SecKey sk;

    slice.data = buff;
    slice.cap = 101;

    randBytes(&slice, 31);
    slice.len = 31;
    unsigned int errorcode = SKY_cipher_NewPubKey(slice, &pk);
    ck_assert_msg(errorcode == SKY_ErrInvalidLengthPubKey, "31 random bytes");

    randBytes(&slice, 32);
    errorcode = SKY_cipher_NewPubKey(slice, &pk);
    ck_assert_msg(errorcode == SKY_ErrInvalidLengthPubKey, "32 random bytes");

    randBytes(&slice, 34);
    errorcode = SKY_cipher_NewPubKey(slice, &pk);
    ck_assert_msg(errorcode == SKY_ErrInvalidLengthPubKey, "34 random bytes");

    slice.len = 0;
    errorcode = SKY_cipher_NewPubKey(slice, &pk);
    ck_assert_msg(errorcode == SKY_ErrInvalidLengthPubKey, "0 random bytes");

    randBytes(&slice, 100);
    errorcode = SKY_cipher_NewPubKey(slice, &pk);
    ck_assert_msg(errorcode == SKY_ErrInvalidLengthPubKey, "100 random bytes");

    randBytes(&slice, 33);
    errorcode = SKY_cipher_NewPubKey(slice, &pk);
    ck_assert_msg(errorcode != SKY_OK, "33 random bytes");

    SKY_cipher_GenerateKeyPair(&pk, &sk);
    GoSlice buffer = {pk, sizeof(pk), sizeof(pk)};
    errorcode = SKY_cipher_NewPubKey(buffer, &pk2);
    ck_assert_msg(errorcode == SKY_OK);

    ck_assert(isPubKeyEq(&pk, &pk2));
}
END_TEST

// define test suite and cases
Suite *common_check_cipher_crypto(void)
{
  Suite *s = suite_create("Load common check_cipher.crypto");
  TCase *tc;

  tc = tcase_create("check_cipher.crypto");
  tcase_add_test(tc, TestNewPubKey);
  suite_add_tcase(s, tc);
  tcase_set_timeout(tc, 150);

  return s;
}
 
