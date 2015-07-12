struct GCObjectBase {
    char size;
    GCObjectBase(char _size) : size(_size) {}
};
template<typename T> struct GCObject {
    GCObject() : GCObjectBase(sizeof(T)) {}
};
struct Cons : GCObject<Cons> {
};
struct Int : GCObject<Int> {
};
// etc