typedef struct {
    cipher__SHA256 Hash;
    GoUint64_ BkSeq;
    GoUint64_ Time;
    cipher__Address Address;
    GoUint64_ Coins;
    GoUint64_ InitialHours;
    GoUint64_ Hours;
    cipher__SHA256 SrcTransaction;
} transaction__UxBalance;