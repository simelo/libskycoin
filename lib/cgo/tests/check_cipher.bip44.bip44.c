#include <stdio.h>
#include <stdlib.h>

#include "libskycoin.h"
#include "skyerrors.h"
#include "skystring.h"
#include "skytest.h"
#include <check.h>

GoUint32 CoinTypeBitcoin = 0;
GoUint32 CoinTypeBitcoinTestnet = 1;
GoUint32 CoinTypeSkycoin = 8000;
GoUint32 ExternalChainIndex = 0;
GoUint32 ChangeChainIndex = 1;
GoUint32 FirstHardenedChild = 0x80000000;

void mustDefaultSeed(GoSlice* seed)
{
    GoString mnemonic = {"dizzy cigar grant ramp inmate uniform gold success able payment faith practice", 78};
    GoString passphrase = {"", 0};
    GoUint8 bufferTmp[1024];
    coin__UxArray Tmp = {bufferTmp, 0, 1024};
    GoUint32 err = SKY_bip39_NewSeed(mnemonic, passphrase, &Tmp);
    ck_assert_int_eq(err, SKY_OK);
    copycoin_UxArraytoGoSlice(seed, &Tmp, sizeof(Tmp));
    GoUint8 strTmp[1024];
    GoString_ str = {strTmp, 0};
    err = SKY_base58_Hex2String(*seed, &str);
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
    GoUint8 bufferBad[1024];
    GoSlice Bad = {bufferBad, 0, 1024};
    mustDefaultSeed(&Bad);
    err = SKY_bip44_NewCoin(Bad, FirstHardenedChild, &coin);
    ck_assert_int_eq(err, SKY_ErrInvalidCoinType);
    err = SKY_bip44_NewCoin(Bad, (FirstHardenedChild + 1), &coin);
    ck_assert_int_eq(err, SKY_ErrInvalidCoinType);

    Coin__Handle c = 0;
    err = SKY_bip44_NewCoin(Bad, CoinTypeBitcoin, &c);
    ck_assert_int_eq(err, SKY_OK);

    Account__Handle account = 0;
    err = SKY_bip44_Coin_Account(c, 0, &account);
    ck_assert_int_eq(err, SKY_OK);
    GoUint8 bufferAccStr[1024];
    GoString acc_string = {bufferAccStr, 0};
    err = SKY_bip44_Account_String(account, &acc_string);
    ck_assert_int_eq(err, SKY_OK);
    ck_assert_str_eq(acc_string.p, "xprv9yKAFQtFghZSe4mfdpdqFm1WWmGeQbYMB4MSGUB85zbKGQgSxty4duZb8k6hNoHVd2UR7Y3QhWU3rS9wox9ewgVG7gDLyYTL4yzEuqUCjvF");
    PrivateKey__Handle privk = 0;
    PublicKey__Handle pubk = 0;
    err = SKY_bip44_Account_GetPrivateKey(account, &privk);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_bip32_Private_Publickey(privk, &pubk);
    ck_assert_int_eq(err, SKY_OK);
    GoUint8 bufferPubKStr[1024];
    GoString pubk_string = {bufferPubKStr, 0};
    err = SKY_bip32_Public_String(pubk, &pubk_string);
    ck_assert_int_eq(err, SKY_OK);
    ck_assert_str_eq(pubk_string.p, "xpub6CJWevR9X57jrYr8jrAqctxF4o78p4GCYHH34rajeL8J9D1bWSHKBht4yzwiTQ4FP4HyQpx99iLxvU54rbEbcxBUgxzTGGudBVXb1N2gcHF");

    err = SKY_bip44_Coin_Account(c, 1, &account);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_bip44_Account_String(account, &acc_string);
    ck_assert_int_eq(err, SKY_OK);
    ck_assert_str_eq(acc_string.p, "xprv9yKAFQtFghZSgShGXkxHsYQfFaqMyutf3izng8tV4Tmp7gidQUPB8kCuv66yukidivM2oSaUvGus8ffnYvYKChB7DME2H2AvUq8LM2rXUzF");
    privk = 0;
    pubk = 0;
    err = SKY_bip44_Account_GetPrivateKey(account, &privk);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_bip32_Private_Publickey(privk, &pubk);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_bip32_Public_String(pubk, &pubk_string);
    ck_assert_int_eq(err, SKY_OK);
    ck_assert_str_eq(pubk_string.p, "xpub6CJWevR9X57jtvmjdnVJEgMPocfrPNcWQwvPUXJ6coJnzV3mx1hRgYXPmQJh5vLQvrVCY8LtJB5xLLiPJVmpSwBe2yhonQLoQuSsCF8YPLN");

    Account__Handle account_temp = 0;
    err = SKY_bip44_Coin_Account(c, 0x80000000, &account_temp);
    ck_assert_int_eq(err, SKY_ErrInvalidAccount);
    err = SKY_bip44_Coin_Account(c, 0x80000001, &account_temp);
    ck_assert_int_eq(err, SKY_ErrInvalidAccount);

    PrivateKey__Handle external = 0;
    err = SKY_bip44_Account_External(account, &external);
    ck_assert_int_eq(err, SKY_OK);
    GoUint8 bufferPrivKStr[1024];
    GoString privk_string = {bufferPrivKStr, 0};
    err = SKY_bip32_Private_String(external, &privk_string);
    ck_assert_int_eq(err, SKY_OK);
    
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