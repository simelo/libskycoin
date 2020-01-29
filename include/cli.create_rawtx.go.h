typedef struct {
    GoString_ Addr;
    GoUint64_ Coins;
} cli__SendAmount;
typedef struct {
    GoString_ Addr;
    GoString_ Coins;
} cli__sendAmountJSON;
typedef struct {
    GoString_ Wallet;
    GoString_ Address;
} cli__walletAddress;
typedef GoInterface_ cli__GetOutputser;
typedef struct {
    GoString_ WalletID;
    GoString_ Address;
    GoString_ ChangeAddress;
    GoSlice_ SendAmounts;
    cli__PasswordReader Password;
} cli__createRawTxnArgs;