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
    GoSlice_ Tmp = {bufferTmp, 0, 1024};
    GoUint32 err = SKY_bip39_NewSeed(mnemonic, passphrase, &Tmp);
    ck_assert_int_eq(err, SKY_OK);
    copyGoSlice_toGoSlice(seed, &Tmp, sizeof(Tmp));
    GoUint8 strTmp[1024];
    GoString_ str = {strTmp, 0};
    err = SKY_base58_Hex2String(*seed, &str);
    ck_assert_int_eq(err, SKY_OK);
    ck_assert(strncmp(str.p, "24e563fb095d766df3862c70432cc1b2210b24d232da69af7af09d2ec86d28782ce58035bae29994c84081836aebe36a9b46af1578262fefc53e37efbe94be57", 128) == SKY_OK);
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
    err = SKY_bip32_PrivateKey_Publickey(privk, &pubk);
    ck_assert_int_eq(err, SKY_OK);
    GoUint8 bufferPubKStr[1024];
    GoString pubk_string = {bufferPubKStr, 0};
    err = SKY_bip32_PublicKey_String(pubk, &pubk_string);
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
    err = SKY_bip32_PrivateKey_Publickey(privk, &pubk);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_bip32_PublicKey_String(pubk, &pubk_string);
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
    err = SKY_bip32_PrivateKey_String(external, &privk_string);
    ck_assert_int_eq(err, SKY_OK);
    ck_assert_str_eq(privk_string.p, "xprv9zjsvjLiqSerDzbeRXPeXwz8tuQ7eRUABkgFAgLPHw1KzGKkgBhJhGaMYHM8j2KDXBZTCv4m19qjxrrD7gusrtdpZ7xzJywdXHaMZEjf3Uv");
    pubk = 0;
    err = SKY_bip32_PrivateKey_Publickey(external, &pubk);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_bip32_PublicKey_String(pubk, &pubk_string);
    ck_assert_int_eq(err, SKY_OK);
    ck_assert_str_eq(pubk_string.p, "xpub6DjELEscfpD9SUg7XYveu5vsSwEc3tC1Yybqy4jzrGYJs4euDj1ZF4tqPZYvViMn9cvBobHyubuuh69PZ1szaBBx5oxPiQzD492B6C4QDHe");

    PublicKey__Handle external0 = 0;
    err = SKY_bip32_PrivateKey_NewPublicChildKey(external, 0, &external0);
    ck_assert_int_eq(err, SKY_OK);
    GoUint8 bufferKey[1024];
    GoUint8 bufferKeyStr[1024];
    GoSlice_ Key = {bufferKey, 0, 1024};
    GoString_ KeyStr = {bufferKeyStr, 0};
    err = SKY_bip32_PublicKey_GetKey(external0, &Key);
    ck_assert_int_eq(err, SKY_OK);
    GoUint8 bufferKeySlice[1024];
    GoSlice KeySlice = {bufferKeySlice, 0, 1024};
    copyGoSlice_toGoSlice(&KeySlice, &Key, sizeof(Key));
    SKY_base58_Hex2String(KeySlice, &KeyStr);
    ck_assert_str_eq(KeyStr.p, "034d36f3bcd74e19204e75b81b9c0726e41b799858b92bab73f4cd7498308c5c8b");

    PublicKey__Handle external1 = 0;
    err = SKY_bip32_PrivateKey_NewPublicChildKey(external, 1, &external1);
    ck_assert_int_eq(err, SKY_OK);
    GoUint8 bufferKey1[1024];
    GoUint8 bufferKey1Str[1024];
    GoSlice_ Key1 = {bufferKey, 0, 1024};
    GoString_ Key1Str = {bufferKeyStr, 0};
    err = SKY_bip32_PublicKey_GetKey(external1, &Key1);
    ck_assert_int_eq(err, SKY_OK);
    GoUint8 bufferKey1Slice[1024];
    GoSlice Key1Slice = {bufferKey1Slice, 0, 1024};
    copyGoSlice_toGoSlice(&Key1Slice, &Key1, sizeof(Key1));
    SKY_base58_Hex2String(Key1Slice, &Key1Str);
    ck_assert(strncmp(Key1Str.p, "02f7309e9f559d847ee9cc9ee144cfa490791e33e908fdbde2dade50a389408b01", 66) == 0);

    PrivateKey__Handle change = 0;
    err = SKY_bip44_Account_Change(account, &change);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_bip32_PrivateKey_String(change, &privk_string);
    ck_assert_int_eq(err, SKY_OK);
    ck_assert(strncmp(privk_string.p, "xprv9zjsvjLiqSerGzJyBrpZgCaGpQCeFDnZEuAV714WigmFyHT4nFLhZLeuHzLNE19PgkZeQ5Uf2pjFZjQTHbkugDbmw5TAPAvgo2jsaTnZo2A", 66) == 0);
    pubk = 0;
    err = SKY_bip32_PrivateKey_Publickey(change, &pubk);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_bip32_PublicKey_String(pubk, &pubk_string);
    ck_assert_int_eq(err, SKY_OK);
    ck_assert(strncmp(pubk_string.p, "xpub6DjELEscfpD9VUPSHtMa3LX1NS38egWQc865uPU8H2JEr5nDKnex78yP9GxhFr5cnCRgiQF1dkv7aR7moraPrv73KHwSkDaXdWookR1Sh9p", 66) == 0);

    PublicKey__Handle change0 = 0;
    err = SKY_bip32_PrivateKey_NewPublicChildKey(change, 0, &change0);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_bip32_PublicKey_GetKey(change0, &Key);
    ck_assert_int_eq(err, SKY_OK);
    copyGoSlice_toGoSlice(&KeySlice, &Key, sizeof(Key));
    SKY_base58_Hex2String(KeySlice, &KeyStr);
    ck_assert(strncmp(KeyStr.p, "026d3eb891e81ecabedfa8560166af383457aedaf172af9d57d00508faa5f57c4c", 66) == 0);

    PublicKey__Handle change1 = 0;
    err = SKY_bip32_PrivateKey_NewPublicChildKey(change, 1, &change1);
    ck_assert_int_eq(err, SKY_OK);
    err = SKY_bip32_PublicKey_GetKey(change1, &Key1);
    ck_assert_int_eq(err, SKY_OK);
    copyGoSlice_toGoSlice(&Key1Slice, &Key1, sizeof(Key1));
    SKY_base58_Hex2String(Key1Slice, &Key1Str);
    ck_assert(strncmp(Key1Str.p, "02681b301293fdf0292cd679b37d60b92a71b389fd994b2b57c8daf99532bfb4a5", 66) == 0);
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