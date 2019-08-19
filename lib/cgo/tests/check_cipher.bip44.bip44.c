#include <stdio.h>
#include <stdlib.h>

#include "libskycoin.h"
#include "skyerrors.h"
#include "skystring.h"
#include "skytest.h"
#include <check.h>

GoUint32 CoinTypeBitcoin = 0;
GoUint32 CoinTypeBitcoinTestnet = 1;
#define CoinTypeSkycoin = 8000
#define ExternalChainIndex = 0
#define ChangeChainIndex = 1

void mustDefaultSeed(GoSlice* seed)
{
    GoString mnemonic = {"dizzy cigar grant ramp inmate uniform gold success able payment faith practice", 78};
    GoString passphrase = {"", 0};
    GoUint32 err = SKY_bip39_NewSeed(mnemonic, passphrase, &seed);
    ck_assert_int_eq(err, SKY_OK);
    GoUint8 bufferTmp[1024];
    GoSlice Tmp = {bufferTmp, 0, 1024};
    copycoin_UxArraytoGoSlice(&Tmp, &seed, sizeof(seed));
    GoUint8 strTmp[1024];
    GoString_ str = {strTmp, 0};
    err = SKY_base58_Hex2String(Tmp, &str);
    ck_assert_int_eq(err, SKY_OK);
    ck_assert_str_eq("24e563fb095d766df3862c70432cc1b2210b24d232da69af7af09d2ec86d28782ce58035bae29994c84081836aebe36a9b46af1578262fefc53e37efbe94be57", str.p);
}

START_TEST(TestNewCoin)
{
    //    bad seed
    GoUint8 bufferTmp[1024];
    GoSlice tmp = {bufferTmp, 0, 1024};
    randBytes(&tmp, 3);
    Coin__Handle coin = 0;
    GoUint32 err = SKY_bip44_NewCoin(tmp, CoinTypeBitcoin, &coin);
    ck_assert_int_eq(err, SKY_ErrInvalidSeedLength);
    // bad coin_type
    // GoUint8 
}
END_TEST

Suite* cipher_bip44(void)
{
    Suite* s = suite_create("Load cipher.bip44");
    TCase* tc;

    tc = tcase_create("cipher.bip44");
    tcase_add_checked_fixture(tc, setup, teardown);
    tcase_add_test(tc, TestNewCoin);
    suite_add_tcase(s, tc);
    tcase_set_timeout(tc, 150);

    return s;
}