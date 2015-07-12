#include <cstddef>
#include <memory>
#include <cassert>

enum TypeId : unsigned char {
    CONS = 0
};

struct GCObject {
    GCObject(TypeId id) : type(id), some_flag(0), other_flag(0) { }
    TypeId type;
    bool some_flag;
    bool other_flag;
};

struct Cons {
    Cons *car, *cdr;
};

void* after_obj(GCObject* obj) {
    void* p = reinterpret_cast<char*>(obj) + sizeof(*obj);
    std::size_t dummy = 1;
    return std::align(alignof(std::max_align_t), 0, p, dummy);
}

Cons* as_cons(GCObject* obj) {
    assert(obj->type == CONS);
    return static_cast<Cons*>(after_obj(obj));
}

GCObject* alloc(char* heap, TypeId id) {
    auto obj = new (heap) GCObject(id);
    return obj;
}

int main(int argc, char** argv) {
    char heap[512];
    GCObject* obj = alloc(heap, CONS);
    new (after_obj(obj)) Cons();
    auto cons = as_cons(obj);
}