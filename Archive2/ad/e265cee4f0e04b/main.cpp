#include <functional>
#include <vector>
#include <cstdint>
#include <iostream>


struct GCRef {
    GCRef(void* obj);
    ~GCRef();
    void* obj;
    int ref_id;
};

struct GC {
private:
    void add_ref(GCRef* ref) {
        ref->ref_id = refs.size();
        refs.push_back(ref);
    }
    
    void remove_ref(GCRef* ref) {
        refs.back()->ref_id = ref->ref_id;
        refs[ref->ref_id] = std::move(refs.back());
        refs.pop_back();
    }
    
    std::vector<GCRef*> refs;
    friend class GCRef;
} gc;

GCRef::GCRef(void* obj) : obj(obj) { gc.add_ref(this); }
GCRef::~GCRef() { gc.remove_ref(this); }

int main() {
    return 0;
}