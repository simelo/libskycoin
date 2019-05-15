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

void freshSumSHA256(GoSlice bytes, cipher__SHA256* sha256)
{
    SKY_cipher_SumSHA256(bytes, sha256);
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

START_TEST(TestSHA256KnownValue)
{
    typedef struct
    {
        char* input;
        char* output;
    } tmpstruct;

    tmpstruct vals[3];

    vals[0].input = "skycoin";
    vals[0].output =
        "5a42c0643bdb465d90bf673b99c14f5fa02db71513249d904573d2b8b63d353d";

    vals[1].input = "hello world";
    vals[1].output =
        "b94d27b9934d3e08a52e52d7da7dabfac484efe37a5380ee9088f7ace2efcde9";

    vals[2].input = "hello world asd awd awd awdapodawpokawpod ";
    vals[2].output =
        "99d71f95cafe05ea2dddebc35b6083bd5af0e44850c9dc5139b4476c99950be4";
    int i;
    for (i = 0; i < 3; ++i) {
        GoSlice slice_input;
        GoSlice slice_output;

        slice_input.data = vals[i].input;
        slice_input.len = strlen(vals[i].input);
        slice_input.cap = strlen(vals[i].input) + 1;

        cipher__SHA256 sha;

        SKY_cipher_SumSHA256(slice_input, &sha);

        GoString_ tmp_output;

        SKY_cipher_SHA256_Hex(&sha, &tmp_output);
        registerMemCleanup((void*)tmp_output.p);

        ck_assert(strcmp(tmp_output.p, vals[i].output) == SKY_OK);
    }
}
END_TEST

START_TEST(TestSumSHA256)
{
    unsigned char bbuff[257], cbuff[257];
    GoSlice b = {bbuff, 0, 257};
    cipher__SHA256 h1;
    randBytes(&b, 256);
    SKY_cipher_SumSHA256(b, &h1);
    cipher__SHA256 tmp;
    ck_assert(!isU8Eq(h1, tmp, 32));
    GoSlice c = {cbuff, 0, 257};
    randBytes(&c, 256);
    cipher__SHA256 h2;
    SKY_cipher_SumSHA256(c, &h2);
    ck_assert(!isU8Eq(h1, tmp, 32));
    cipher__SHA256 tmp_h2;
    freshSumSHA256(c, &tmp_h2);
    ck_assert(isU8Eq(h2, tmp_h2, 32));
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
  tcase_add_test(tc, TestSHA256KnownValue);
  tcase_add_test(tc, TestSumSHA256);
  suite_add_tcase(s, tc);
  tcase_set_timeout(tc, 150);

  return s;
}
