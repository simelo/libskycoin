#include <stdio.h>
#include <stdlib.h>

#include <check.h>
#include "libskycoin.h"
#include "skyerrors.h"
#include "skyassert.h"
#include "skystring.h"
#include "skytest.h"

// TestSuite(cipher_hash, .init = setup, .fini = teardown);

void freshSumRipemd160(GoSlice bytes, cipher__Ripemd160* rp160)
{
    SKY_cipher_HashRipemd160(bytes, rp160);
}

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

START_TEST(TestHashRipemd160)
{
    cipher__Ripemd160 tmp;
    cipher__Ripemd160 r;
    cipher__Ripemd160 r2;
    unsigned char buff[257];
    GoSlice slice = {buff, 0, 257};

    randBytes(&slice, 128);
    SKY_cipher_HashRipemd160(slice, &tmp);
    randBytes(&slice, 160);
    SKY_cipher_HashRipemd160(slice, &r);
    ck_assert(!isU8Eq(tmp, r, sizeof(cipher__Ripemd160)));

    unsigned char buff1[257];
    GoSlice b = {buff1, 0, 257};
    randBytes(&b, 256);
    SKY_cipher_HashRipemd160(b, &r2);
    ck_assert(!isU8Eq(tmp, r2, sizeof(cipher__Ripemd160)));
    freshSumRipemd160(b, &tmp);
    ck_assert(isU8Eq(tmp, r2, sizeof(cipher__Ripemd160)));
}
END_TEST

// define test suite and cases
Suite *common_check_cipher_hash(void)
{
  Suite *s = suite_create("Load common check_cipher.hash");
  TCase *tc;

  tc = tcase_create("check_cipher.hash");
  tcase_add_test(tc, TestAddSHA256);
  tcase_add_test(tc, TestHashRipemd160);
  suite_add_tcase(s, tc);
  tcase_set_timeout(tc, 150);

  return s;
}
