template<typename T> struct GCObject {
    char size;
    GCObject() : size(sizeof(T)) {}
};
struct Cons : GCObject<Cons> {
};
struct Int : GCObject<Int> {
};

void sweep(char* heap) {
    // Ok, what now?
    GCObject* o = reinterpret_cast<GCObject*>(heap); // this is UB because GCObject might not be in front of memory layout of Cons
    
}

int main(int argc, char** argv) {
    char heap[512];
    
    // ignoring alignment
    Cons* c = new (heap) Cons();
}