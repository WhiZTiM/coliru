#include <iostream>
#include <memory>
 
struct Foo { // object to manage
    Foo() { std::cout << "Foo ctor\n"; }
    Foo(const Foo&) { std::cout << "Foo copy ctor\n"; }
    Foo(Foo&&) { std::cout << "Foo move ctor\n"; }
    ~Foo() { std::cout << "~Foo dtor\n"; }
};

struct Exception {};

struct InternalPtr {
    Foo *ptr = nullptr;
    InternalPtr(Foo *p) : ptr(p) {}
    InternalPtr() = default;
    
    Foo& operator*() const {
        std::cout << "Checking for a null pointer.." << std::endl;
        if(ptr == nullptr)
            throw Exception();
        return *ptr;
    }
    
    bool operator != (Foo *p) {
        if(p != ptr)
            return false;
        else
            return true;
    }
    void cleanup() {
        delete ptr;
    }
};
 
struct D { // deleter
    using pointer = InternalPtr;
    D() {};
    D(const D&) { std::cout << "D copy ctor\n"; }
    D(D&) { std::cout << "D non-const copy ctor\n";}
    D(D&&) { std::cout << "D move ctor \n"; }
    void operator()(InternalPtr& p) const {
        std::cout << "D is deleting a Foo\n";
        p.cleanup();
    };
};
 
int main()
{
    std::unique_ptr<Foo, D> up(nullptr, D()); // deleter is moved
    
    try {
      auto& e = *up;      
    } catch(Exception&) {
        std::cout << "null pointer exception detected" << std::endl;
    }

}