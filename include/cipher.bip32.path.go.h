typedef struct {
    GoSlice_ Elements; // Goslice de bip32__PathNode
} bip32__Path;

// PathNode is an element of an HD wallet path
typedef struct {
    BOOL Master;
    GoUint32_ ChildNumber;
} bip32__PathNode;