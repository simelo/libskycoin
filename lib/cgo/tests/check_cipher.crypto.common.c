#include <stdio.h>
#include <stdlib.h>

#include "libskycoin.h"
#include "skyassert.h"
#include "skyerrors.h"
#include "skystring.h"
#include "skytest.h"
#include <check.h>

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
    GoString tmp_s3 = {buff_s3, 0};
    err = SKY_cipher_PubKey_Hex(&p, &tmp_s3);
    ck_assert(err == SKY_OK);
    s3.n = tmp_s3.n;
    s3.p = tmp_s3.p;
    registerMemCleanup((void*)s3.p);
    errorcode = SKY_cipher_PubKeyFromHex(s3, &p2);
    ck_assert(errorcode == SKY_OK);
    ck_assert(isPubKeyEq(&p, &p2));

    unsigned char s4_buff[50];
    GoString tmp_s4 = {s4_buff, 0};
    err = SKY_cipher_PubKey_Hex(&p2, &tmp_s4);
    ck_assert(err == SKY_OK);
    s4.n = s4.n;
    s4.p = s4.p;
    registerMemCleanup((void*)s4.p);
    // // TODO: Translate into cr_assert(eq(type(GoString), s3, s4));
    ck_assert(isGoStringEq(s3, s4) == 0);
}
END_TEST

START_TEST(TestPubKeyVerify)
{
    cipher__PubKey p;
    unsigned char buff[50];
    GoSlice slice = {buff, 0, 50};
    unsigned int errorcode;
    int failed = 1;

    int i = 0;
    for (; i < 10; i++) {
        randBytes(&slice, 33);
        memcpy((void*)&p, slice.data, 33);
        failed = 1 || (errorcode = SKY_cipher_PubKey_Verify(&p));
    }
    ck_assert(failed);
}
END_TEST

START_TEST(TestPubKeyVerifyNil)
{
    cipher__PubKey p = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0};
    unsigned int errorcode;

    errorcode = SKY_cipher_PubKey_Verify(&p);
    ck_assert(errorcode == SKY_ErrInvalidPubKey);
}
END_TEST

START_TEST(TestPubKeyVerifyDefault1)
{
    cipher__PubKey p;
    cipher__SecKey s;

    SKY_cipher_GenerateKeyPair(&p, &s);
    GoUint32 errorcode = SKY_cipher_PubKey_Verify(&p);
    ck_assert(errorcode == SKY_OK);
}
END_TEST

START_TEST(TestNewSig)
{
    unsigned char buff[101];
    GoSlice b;
    cipher__Sig s;
    int errorcode;

    b.data = buff;
    b.len = 0;
    b.cap = 101;

    randBytes(&b, 64);
    errorcode = SKY_cipher_NewSig(b, &s);
    ck_assert(errorcode == SKY_ErrInvalidLengthSig);

    randBytes(&b, 66);
    errorcode = SKY_cipher_NewSig(b, &s);
    ck_assert(errorcode == SKY_ErrInvalidLengthSig);

    randBytes(&b, 67);
    errorcode = SKY_cipher_NewSig(b, &s);
    ck_assert(errorcode == SKY_ErrInvalidLengthSig);

    randBytes(&b, 0);
    errorcode = SKY_cipher_NewSig(b, &s);
    ck_assert(errorcode == SKY_ErrInvalidLengthSig);

    randBytes(&b, 100);
    errorcode = SKY_cipher_NewSig(b, &s);
    ck_assert(errorcode == SKY_ErrInvalidLengthSig);

    randBytes(&b, 65);
    errorcode = SKY_cipher_NewSig(b, &s);
    ck_assert(errorcode == SKY_OK);
    ck_assert(isU8Eq(buff, s, 65));
}
END_TEST

START_TEST(TestMustSigFromHex)
{
    unsigned char buff[101];
    char strBuff[257];
    GoSlice b = {buff, 0, 101};
    GoString str;
    cipher__Sig s, s2;
    int errorcode;

    // Invalid hex
    str.p = "";
    str.n = strlen(str.p);
    errorcode = SKY_cipher_SigFromHex(str, &s2);
    ck_assert(errorcode == SKY_ErrInvalidLengthSig);

    str.p = "cascs";
    str.n = strlen(str.p);
    errorcode = SKY_cipher_SigFromHex(str, &s2);
    ck_assert(errorcode == SKY_ErrInvalidSig);

    // Invalid hex length
    randBytes(&b, 65);
    errorcode = SKY_cipher_NewSig(b, &s);
    ck_assert(errorcode == SKY_OK);
    str.p = strBuff;
    str.n = 0;
    bytesnhex(s, (char*)str.p, 32);
    str.n = strlen(str.p);
    errorcode = SKY_cipher_SigFromHex(str, &s2);
    ck_assert(errorcode == SKY_ErrInvalidLengthSig);

    // Valid
    bytesnhex(s, (char*)str.p, 65);
    str.n = strlen(str.p);
    errorcode = SKY_cipher_SigFromHex(str, &s2);
    ck_assert(errorcode == SKY_OK);
    ck_assert(isU8Eq(s2, s, 65));
}
END_TEST

START_TEST(TestSigHex)
{
    unsigned char buff[66];
    GoSlice b = {buff, 0, 66};
    char strBuff[150],
        strBuff2[150];
    GoString str = {NULL, 0},
             str2 = {NULL, 0};
    cipher__Sig s, s2;
    int errorcode;

    randBytes(&b, 65);
    errorcode = SKY_cipher_NewSig(b, &s);

    ck_assert(errorcode == SKY_OK);
    char buffer[100];
    GoString tmp_str = {buffer, 0};
    SKY_cipher_Sig_Hex(&s, &tmp_str);
    str.p = tmp_str.p;
    str.n = tmp_str.n;
    registerMemCleanup((void*)str.p);
    errorcode = SKY_cipher_SigFromHex(str, &s2);

    ck_assert(errorcode == SKY_OK);
    ck_assert(isU8Eq(s, s2, 65));

    char buffer2[100];
    GoString_ tmp_str2 = {buffer, 0};
    SKY_cipher_Sig_Hex(&s2, &tmp_str);
    str2.p = tmp_str.p;
    str2.n = tmp_str.n;
    registerMemCleanup((void*)str2.p);
    // ck_assert(isGoStringEq(str, str2));
    ck_assert_str_eq(str.p, str2.p);
}
END_TEST

START_TEST(TestPubKeyFromSecKey)
{
    cipher__PubKey pk, pk2;
    cipher__SecKey sk;
    unsigned char buff[101];
    GoSlice b = {buff, 0, 101};
    int errorcode;

    SKY_cipher_GenerateKeyPair(&pk, &sk);
    errorcode = SKY_cipher_PubKeyFromSecKey(&sk, &pk2);
    ck_assert(errorcode == SKY_OK);
    ck_assert(isU8Eq(pk, pk2, 33));

    memset(&sk, 0, sizeof(sk));
    errorcode = SKY_cipher_PubKeyFromSecKey(&sk, &pk);
    ck_assert(errorcode == SKY_ErrPubKeyFromNullSecKey);

    randBytes(&b, 99);
    errorcode = SKY_cipher_NewSecKey(b, &sk);
    ck_assert(errorcode == SKY_ErrInvalidLengthSecKey);

    randBytes(&b, 31);
    errorcode = SKY_cipher_NewSecKey(b, &sk);
    ck_assert(errorcode == SKY_ErrInvalidLengthSecKey);
}
END_TEST

// define test suite and cases
Suite* common_check_cipher_crypto(void)
{
    Suite* s = suite_create("Load common check_cipher.crypto");
    TCase* tc;

    tc = tcase_create("check_cipher.crypto");
    tcase_add_test(tc, TestNewPubKey);
    tcase_add_test(tc, TestPubKeyFromHex);
    tcase_add_test(tc, TestPubKeyHex);
    tcase_add_test(tc, TestPubKeyVerify);
    tcase_add_test(tc, TestPubKeyVerifyNil);
    tcase_add_test(tc, TestPubKeyVerifyDefault1);
    tcase_add_test(tc, TestNewSig);
    tcase_add_test(tc, TestMustSigFromHex);
    tcase_add_test(tc, TestSigHex);
    tcase_add_test(tc, TestPubKeyFromSecKey);
    suite_add_tcase(s, tc);
    tcase_set_timeout(tc, 150);

    return s;
}
