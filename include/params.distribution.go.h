typedef struct {
    GoUint64_ MaxCoinSupply;
    GoUint64_ InitialUnlockedCount;
    GoUint64_ UnlockAddressRate;
    GoUint64_ UnlockTimeInterval;
    GoSlice_ Addresses;
    GoSlice_ addressesDecoded;
} params__Distribution;