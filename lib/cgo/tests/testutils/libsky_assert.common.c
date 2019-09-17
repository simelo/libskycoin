#include "check.h"
#include "skyassert.h"
#include "skystring.h"
#include <string.h>

GoInt isAddressEq(cipher__Address* addr1, cipher__Address* addr2)
{
    return (addr1->Version == addr2->Version && isRipemd160Eq(&addr1->Key, &addr2->Key));
}

GoInt isGoStringEq(GoString string1, GoString string2)
{
    return (string1.n == string2.n) &&
           (strncmp(string1.p, string2.p, string1.n) == 0);
}

GoInt isPubKeyEq(cipher__PubKey* pubkey1, cipher__PubKey* pubkey2)
{
    return isU8Eq(*pubkey1, *pubkey2, sizeof(cipher__PubKey));
}

GoInt isRipemd160Eq(cipher__Ripemd160* rip1, cipher__Ripemd160* rip2)
{
    return isU8Eq(*rip1, *rip2, sizeof(cipher__Ripemd160));
}
