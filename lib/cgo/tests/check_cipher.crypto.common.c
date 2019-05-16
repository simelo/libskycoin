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

START_TEST(TestPubKeyHex)
{
    cipher__PubKey p, p2;
    cipher__SecKey sk;
    GoString s3, s4;
    unsigned char buff[50];
    unsigned char buff_s3[50];
    GoSlice slice = {buff, 0, 50};
    unsigned int errorcode;

    GoUint32 err = SKY_cipher_GenerateKeyPair(&p, &sk);
    ck_assert(err == SKY_OK);
    GoString_ tmp_s3 = {buff_s3, 0};
    err = SKY_cipher_PubKey_Hex(&p, &tmp_s3);
    ck_assert(err == SKY_OK);
    s3.n = tmp_s3.n;
    s3.p = tmp_s3.p;
    registerMemCleanup((void*)s3.p);
    errorcode = SKY_cipher_PubKeyFromHex(s3, &p2);
    ck_assert(errorcode == SKY_OK);
    ck_assert(isPubKeyEq(&p, &p2));

    unsigned char s4_buff[50];
    GoString_ tmp_s4 = {s4_buff, 0};
    err = SKY_cipher_PubKey_Hex(&p2, &tmp_s4);
    ck_assert(err == SKY_OK);
    s4.n = s4.n;
    s4.p = s4.p;
    registerMemCleanup((void*)s4.p);
    // // TODO: Translate into cr_assert(eq(type(GoString), s3, s4));
    ck_assert(isGoStringEq(s3, s4) == 0);
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
  tcase_add_test(tc, TestPubKeyHex);
  suite_add_tcase(s, tc);
  tcase_set_timeout(tc, 150);

  return s;
}
 
