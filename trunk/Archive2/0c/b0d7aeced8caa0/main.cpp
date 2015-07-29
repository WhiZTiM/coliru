#include <iostream>
#include <memory>

struct base {
    virtual ~base() {}
};

struct derived : base {
    static void operator delete(void* p) {
        std::cout << "custom deleter called\n";
        ::operator delete(p);
    }
};

int main() {
    base* b = new derived;
    delete b;
}