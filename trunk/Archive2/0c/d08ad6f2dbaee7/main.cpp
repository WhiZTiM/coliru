#include <iostream>

typedef long int intptr_t;

template <typename T>
class MockPointer {
    public:
        // Constructors
        MockPointer(T* p) : ptr(p) {}
        
        // Conversion operators
        operator T*() { return ptr; }
        operator intptr_t() { return static_cast<intptr_t>(ptr); }
        
    private:
        T* ptr;
};

int main() {
    int x = 3;
    MockPointer<int> mp(&x);
    
    intptr_t ip1 = mp;
    int* ip2 = mp;
    
    assert(ip1 == ip2);
    
    return 0;
}
