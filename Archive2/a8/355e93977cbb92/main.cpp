#include <iostream>

struct S {
    S &setFoo() {std::cout << "Setting foo for " << this << '\n'; return *this;}  
    S &setBar() {std::cout << "Setting bar for " << this << '\n'; return *this;}
};

int main() {
    S s;
    s.setFoo().setBar();
}