#include <iostream>

struct Base;
struct Wrapper;

static Base* sBase = nullptr;
static Wrapper* sWrapper = nullptr;

struct Wrapper {
    Wrapper(Base& base) : base_(base) { std::cout << "Wrapper consturctor" << std::endl; }
    ~Wrapper() { std::cout << "Wrapper desturctor" << std::endl; }
    
    void f() { std::cout << "Wrapper f" << std::endl; }

    Base& base_;
};

struct Base {
    Base() : wrapper_(*this) {
        std::cout << "Base constructor" << std::endl;
        //sBase = this;
    }
    ~Base() { std::cout << "Base destructor" << std::endl; }
    void f() { std::cout << "Base f" << std::endl; }
    void g() { std::cout << "Base g" << std::endl; }

    Wrapper wrapper_;
};

int main() {
    sBase->f();
    sBase->g();
    sWrapper->f();
}