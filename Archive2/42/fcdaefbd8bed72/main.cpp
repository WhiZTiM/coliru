#include <iostream>

struct foo {
    foo() = default;
    foo(const foo&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    foo(foo&&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    foo& operator=(const foo&) { std::cout << __PRETTY_FUNCTION__ << std::endl; return *this; }
    foo& operator=(foo&&) { std::cout << __PRETTY_FUNCTION__ << std::endl; return *this; }
    
    foo& operator+=(const foo&) { return *this; }
};

foo operator+(const foo& l, const foo& r) {
    foo nrv(l); nrv += r; return nrv;
}

int main(){
    foo f1, f2, f3, f4, f5;
    f1 + f2 + f3 + f4 + f5;
}