#include <stdio.h>
#include <stdlib.h>

#include <check.h>
#include "libskycoin.h"
#include "skyerrors.h"
#include "skyassert.h"
#include "skystring.h"
#include "skytest.h"

// TestSuite(cipher_hash, .init = setup, .fini = teardown);

START_TEST(TestAddSHA256)
{

    unsigned char bbuff[130];
    GoSlice b = {bbuff, 0, 130};
    randBytes(&b, 128);
    cipher__SHA256 h;
    SKY_cipher_SumSHA256(b, &h);

    unsigned char cbuff[130];
    GoSlice c = {cbuff, 0, 130};
    randBytes(&c, 64);
    cipher__SHA256 i;
    SKY_cipher_SumSHA256(c, &i);

    cipher__SHA256 add;
    cipher__SHA256 tmp;

    SKY_cipher_AddSHA256(&h, &i, &add);
    ck_assert(!isU8Eq(add, tmp, 32));
    ck_assert(!isU8Eq(add, h, 32));
    ck_assert(!isU8Eq(add, i, 32));
}
END_TEST

// define test suite and cases
Suite *common_check_cipher_hash(void)
{
  Suite *s = suite_create("Load common check_cipher.hash");
  TCase *tc;

  tc = tcase_create("check_cipher.hash");
  tcase_add_test(tc, TestAddSHA256);
  suite_add_tcase(s, tc);
  tcase_set_timeout(tc, 150);

  return s;
}
