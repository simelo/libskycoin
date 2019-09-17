#include <stdio.h>
#include <stdlib.h>

#include "libskycoin.h"
#include "skyassert.h"
#include "skyerrors.h"
#include "skystring.h"
#include "skytest.h"
#include <check.h>

extern void freshSumSHA256(GoSlice bytes, cipher__SHA256* sha256);



START_TEST(TestSumSHA256)
{
    GoUint8 bbuff[257];
    GoUint8 cbuff[257];
    GoSlice b = {bbuff, 0, 257};
    cipher__SHA256 h1;
    // randBytes(&b, 256);
    SKY_cipher_RandByte(256, &b);
    SKY_cipher_SumSHA256(b, &h1);
    cipher__SHA256 tmp = "";
    ck_assert_int_eq(isU8Eq(h1, tmp, 32), 0);
    GoSlice c = {cbuff, 0, 257};
    randBytes(&c, 256);
    cipher__SHA256 h2;
    SKY_cipher_SumSHA256(c, &h2);
    ck_assert_int_eq(isU8Eq(h1, tmp, 32), 0);
    cipher__SHA256 tmp_h2;
    freshSumSHA256(c, &tmp_h2);
    ck_assert(isU8Eq(h2, tmp_h2, 32));
}
END_TEST

START_TEST(TestRipemd160Set)
{
    cipher__Ripemd160 h;
    unsigned char buff[101];
    GoSlice slice = {buff, 0, 101};
    int error;

    memset(h, 0, sizeof(cipher__Ripemd160));
    randBytes(&slice, 21);

    error = SKY_cipher_Ripemd160_Set(&h, slice);
    ck_assert(error == SKY_ErrInvalidLengthRipemd160);

    randBytes(&slice, 100);
    error = SKY_cipher_Ripemd160_Set(&h, slice);
    ck_assert(error == SKY_ErrInvalidLengthRipemd160);

    randBytes(&slice, 19);
    error = SKY_cipher_Ripemd160_Set(&h, slice);
    ck_assert(error == SKY_ErrInvalidLengthRipemd160);

    randBytes(&slice, 0);
    error = SKY_cipher_Ripemd160_Set(&h, slice);
    ck_assert(error == SKY_ErrInvalidLengthRipemd160);

    randBytes(&slice, 20);
    error = SKY_cipher_Ripemd160_Set(&h, slice);
    ck_assert(error == SKY_OK);
    ck_assert(isU8Eq(h, buff, 20));
}
END_TEST

START_TEST(TestDoubleSHA256)
{
    unsigned char bbuff[130];
    GoSlice b = {bbuff, 0, 130};
    randBytes(&b, 128);
    cipher__SHA256 h;
    cipher__SHA256 tmp;
    SKY_cipher_DoubleSHA256(b, &h);
    ck_assert_int_eq(isU8Eq(tmp, h, 32), 0);
    freshSumSHA256(b, &tmp);
    ck_assert_int_eq(isU8Eq(tmp, h, 32), 0);
}
END_TEST

START_TEST(TestXorSHA256)
{
    unsigned char bbuff[129], cbuff[129];
    GoSlice b = {bbuff, 0, 129};
    GoSlice c = {cbuff, 0, 129};
    cipher__SHA256 h, i;

    randBytes(&b, 128);
    SKY_cipher_SumSHA256(b, &h);
    randBytes(&c, 128);
    SKY_cipher_SumSHA256(c, &i);

    cipher__SHA256 tmp_xor1;
    cipher__SHA256 tmp_xor2;
    cipher__SHA256 tmp;

    SKY_cipher_SHA256_Xor(&h, &i, &tmp_xor1);
    SKY_cipher_SHA256_Xor(&i, &h, &tmp_xor2);
    ck_assert_int_eq(isU8Eq(tmp_xor1, h, 32), 0);
    ck_assert_int_eq(isU8Eq(tmp_xor1, i, 32), 0);
    ck_assert_int_eq(isU8Eq(tmp_xor1, tmp, 32), 0);
    ck_assert(isU8Eq(tmp_xor1, tmp_xor2, 32));
}
END_TEST

START_TEST(TestMerkle)
{
    unsigned char buff[129];
    cipher__SHA256 hashlist[5];
    GoSlice b = {buff, 0, 129}, hashes = {hashlist, 0, 5};
    cipher__SHA256 h, zero, out, out1, out2, out3, out4;
    int i;

    memset(zero, 0, sizeof(zero));

    for (i = 0; i < 5; i++) {
        randBytes(&b, 128);
        SKY_cipher_SumSHA256(b, &hashlist[i]);
    }

    // Single hash input returns hash
    hashes.len = 1;
    SKY_cipher_Merkle(&hashes, &h);
    ck_assert(isU8Eq(hashlist[0], h, 32));

    // 2 hashes should be Addcipher__SHA256 of them
    hashes.len = 2;
    SKY_cipher_AddSHA256(&hashlist[0], &hashlist[1], &out);
    SKY_cipher_Merkle(&hashes, &h);
    ck_assert(isU8Eq(out, h, 32));

    // 3 hashes should be Add(Add())
    hashes.len = 3;
    SKY_cipher_AddSHA256(&hashlist[0], &hashlist[1], &out1);
    SKY_cipher_AddSHA256(&hashlist[2], &zero, &out2);
    SKY_cipher_AddSHA256(&out1, &out2, &out);
    SKY_cipher_Merkle(&hashes, &h);
    ck_assert(isU8Eq(out, h, 32));

    // 4 hashes should be Add(Add())
    hashes.len = 4;
    SKY_cipher_AddSHA256(&hashlist[0], &hashlist[1], &out1);
    SKY_cipher_AddSHA256(&hashlist[2], &hashlist[3], &out2);
    SKY_cipher_AddSHA256(&out1, &out2, &out);
    SKY_cipher_Merkle(&hashes, &h);
    ck_assert(isU8Eq(out, h, 32));

    // 5 hashes
    hashes.len = 5;
    SKY_cipher_AddSHA256(&hashlist[0], &hashlist[1], &out1);
    SKY_cipher_AddSHA256(&hashlist[2], &hashlist[3], &out2);
    SKY_cipher_AddSHA256(&out1, &out2, &out3);
    SKY_cipher_AddSHA256(&hashlist[4], &zero, &out1);
    SKY_cipher_AddSHA256(&zero, &zero, &out2);
    SKY_cipher_AddSHA256(&out1, &out2, &out4);
    SKY_cipher_AddSHA256(&out3, &out4, &out);
    SKY_cipher_Merkle(&hashes, &h);
    ck_assert(isU8Eq(out, h, 32));
}
END_TEST

Suite* cipher_hash(void)
{
    Suite* s = suite_create("Load cipher.hash");
    TCase* tc;

    tc = tcase_create("cipher.hash");
    tcase_add_checked_fixture(tc, setup, teardown);
    tcase_add_test(tc, TestSumSHA256);
    tcase_add_test(tc, TestRipemd160Set);
    tcase_add_test(tc, TestDoubleSHA256);
    tcase_add_test(tc, TestXorSHA256);
    tcase_add_test(tc, TestMerkle);
    suite_add_tcase(s, tc);
    tcase_set_timeout(tc, 150);

    return s;
}
