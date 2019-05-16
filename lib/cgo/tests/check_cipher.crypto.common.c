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

START_TEST(TestPubKeyFromHex)
{
    cipher__PubKey p, p1;
    cipher__SecKey sk;
    GoString s;
    unsigned char buff[51];
    char sbuff[101];
    GoSlice slice = {(void*)buff, 0, 51};
    unsigned int errorcode;

    // Invalid hex
    s.n = 0;
    errorcode = SKY_cipher_PubKeyFromHex(s, &p1);
    ck_assert_msg(errorcode == SKY_ErrInvalidLengthPubKey, "TestPubKeyFromHex: Invalid hex. Empty string");

    s.p = "cascs";
    s.n = strlen(s.p);
    errorcode = SKY_cipher_PubKeyFromHex(s, &p1);
    ck_assert_msg(errorcode == SKY_ErrInvalidPubKey, "TestPubKeyFromHex: Invalid hex. Bad chars");

    // Invalid hex length
    SKY_cipher_GenerateKeyPair(&p, &sk);
    memcpy(slice.data, (void*)p, sizeof(p));
    slice.len = sizeof(p);
    bytesnhex(&p[0], sbuff, slice.len >> 1);
    s.p = sbuff;
    s.n = strlen(s.p);
    errorcode = SKY_cipher_PubKeyFromHex(s, &p1);
    ck_assert_msg(errorcode == SKY_ErrInvalidLengthPubKey, "TestPubKeyFromHex: Invalid hex length");

    // Valid
    bytesnhex(p, sbuff, sizeof(p));
    s.p = sbuff;
    s.n = sizeof(p) << 1;
    errorcode = SKY_cipher_PubKeyFromHex(s, &p1);
    ck_assert_msg(errorcode == SKY_OK, "TestPubKeyFromHex: Valid. No panic.");
    ck_assert(isPubKeyEq(&p, &p1));
}
END_TEST

// define test suite and cases
Suite *common_check_cipher_crypto(void)
{
  Suite *s = suite_create("Load common check_cipher.crypto");
  TCase *tc;

  tc = tcase_create("check_cipher.crypto");
  tcase_add_test(tc, TestNewPubKey);
  tcase_add_test(tc, TestPubKeyFromHex);
  suite_add_tcase(s, tc);
  tcase_set_timeout(tc, 150);

  return s;
}
 
