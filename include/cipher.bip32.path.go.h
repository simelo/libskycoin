typedef struct {
    GoSlice_ Elements; // Goslice de PathNote
} Path;

// PathNode is an element of an HD wallet path
typedef struct {
    BOOL Master;
    GoUint32_ ChildNumber;
} PathNode;