#include <iostream>

struct foo {
    foo() = default;
    foo(const foo&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    foo(foo&&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    foo& operator=(const foo&) { std::cout << __PRETTY_FUNCTION__ << std::endl; return *this; }
    foo& operator=(foo&&) { std::cout << __PRETTY_FUNCTION__ << std::endl; return *this; }
    
    foo& operator+=(int) { return *this; }
};

foo operator+(const foo& l, int r) {
    //return foo(l) += r;
    foo nrv(l); nrv += r; return nrv;
}

int main(){
    foo f;
    f + 1;
}