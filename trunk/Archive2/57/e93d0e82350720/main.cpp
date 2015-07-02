#include <iostream>

struct Foo {
    Foo(int) {}
    
    operator bool() {
        return true;
    }
};

int main() {
    
    if(Foo f = 0) {
        std::cout << "foo !\n";
    }
    
//    if(Foo f(0)) {
//      std::cout << "foo !\n";
//    }
    
    return 0;
}
