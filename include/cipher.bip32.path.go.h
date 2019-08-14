typedef struct {
    GoSlice_ Elements;
} Path;

// PathNode is an element of an HD wallet path
typedef struct PathNode {
    bool Master;
    GoUint32_ ChildNumber;
}