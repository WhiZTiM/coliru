#include <iostream>

typedef long int intptr_t;

template <typename T>
class MockPointer {
    public:
        // Constructors
        explicit MockPointer(T* p) : ptr(p) {}
        
        // Comparison operators
        bool operator==(const MockPointer<T>& rhs) { return ptr == rhs.ptr; }
        
        // Conversion operators
        operator T*() { return ptr; }
        operator intptr_t() { return reinterpret_cast<intptr_t>(ptr); }
        
    private:
        T* ptr;
};

int main() {
    int x = 3;
    MockPointer<int> mp(&x);
    
    intptr_t ip1 = mp;
    int* ip2 = mp;
    
    if (ip1 == mp) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }
    
    if (ip2 == mp) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }
    
    int* a = nullptr;
    if (mp == a) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }
    
    MockPointer<int> mp2(&x);
    if (mp == mp2) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }
    
    return 0;
}
