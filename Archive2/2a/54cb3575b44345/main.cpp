template<typename T> struct GCObject {
    char size;
    GCObject() : size(sizeof(T)) {}
};
struct Cons : GCObject<Cons> {
};
struct Int : GCObject<Int> {
};
// etc