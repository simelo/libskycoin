#include <stdio.h>
#include <stdlib.h>

#include <check.h>
#include <string.h>

#include "libskycoin.h"
#include "skyerrors.h"
#include "skyassert.h"
#include "skystring.h"
#include "skytest.h"

#define SKYCOIN_ADDRESS_VALID "2GgFvqoyk9RjwVzj8tqfcXVXB4orBwoc9qv"

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

START_TEST(TestAddressNull)
{
    cipher__Address a;
    memset(&a, 0, sizeof(cipher__Address));
    GoUint32 result;
    GoUint8 isNull;
    result = SKY_cipher_Address_Null(&a, &isNull);
    ck_assert_msg(result == SKY_OK, "SKY_cipher_Address_Null");
    ck_assert(isNull == 1);

    cipher__PubKey p;
    cipher__SecKey s;

    result = SKY_cipher_GenerateKeyPair(&p, &s);
    ck_assert_msg(result == SKY_OK, "SKY_cipher_GenerateKeyPair failed");

    result = SKY_cipher_AddressFromPubKey(&p, &a);
    ck_assert_msg(result == SKY_OK, "SKY_cipher_AddressFromPubKey failed");
    result = SKY_cipher_Address_Null(&a, &isNull);
    ck_assert_msg(result == SKY_OK, "SKY_cipher_Address_Null");
    ck_assert(isNull == 0);
}
END_TEST

START_TEST(TestAddressFromBytes)
{
    cipher__Address addr, addr2;
    cipher__SecKey sk;
    cipher__PubKey pk;
    GoSlice bytes;
    GoSlice_ tempBytes;
    GoUint8 buff[1024];
    GoUint32 err = SKY_cipher_GenerateKeyPair(&pk, &sk);
    ck_assert(err == SKY_OK);
    SKY_cipher_AddressFromPubKey(&pk, &addr);

    tempBytes.data = buff;
    tempBytes.len = 0;
    tempBytes.cap = sizeof(buff);

    SKY_cipher_Address_Bytes(&addr, &tempBytes);
    ck_assert_msg(tempBytes.len > 0, "address bytes written");
    copyGoSlice_toGoSlice(&bytes, &tempBytes, tempBytes.len);
    err = SKY_cipher_AddressFromBytes(bytes, &addr2);
    ck_assert_msg(err == SKY_OK, "convert bytes to SKY address");

    ck_assert_msg(isAddressEq(&addr, &addr2), "Not equal Address");

    int bytes_len = bytes.len;

    bytes.len = bytes.len - 2;
    ck_assert_msg(SKY_cipher_AddressFromBytes(bytes, &addr2) ==
                      SKY_ErrAddressInvalidLength,
        "no SKY address due to short bytes length");

    bytes.len = bytes_len;
    ((char*)bytes.data)[bytes.len - 1] = '2';
    err = SKY_cipher_AddressFromBytes(bytes, &addr2);
    ck_assert_msg(err == SKY_ErrAddressInvalidChecksum,
        "no SKY address due to corrupted bytes %X", err);

    addr.Version = 2;
    SKY_cipher_Address_Bytes(&addr, &tempBytes);
    copyGoSlice_toGoSlice(&bytes, &tempBytes, tempBytes.len);
    err = SKY_cipher_AddressFromBytes(bytes, &addr2);
    ck_assert_msg(err == SKY_ErrAddressInvalidVersion, "Invalid version");
}
END_TEST

// define test suite and cases
Suite* common_check_cipher_address(void)
{
    Suite* s = suite_create("Load common_check_cipher_address.address");
    TCase* tc;

    tc = tcase_create("check_cipher.address.common");
    tcase_add_checked_fixture(tc, setup, teardown);
    tcase_add_test(tc, TestAddressVerify);
    tcase_add_test(tc, TestAddressNull);
    tcase_add_test(tc, TestAddressFromBytes);
    suite_add_tcase(s, tc);
    tcase_set_timeout(tc, 150);

    return s;
}
