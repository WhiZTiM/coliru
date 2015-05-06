#include <iostream>

#define HAI std::cout << __PRETTY_FUNCTION__ << '\n'

struct S {
    S() { HAI; }
    ~S() { HAI; }
    
    S(S const &) { HAI; }
    S(S &&) { HAI; }
    
    S &operator = (S const &) { HAI; return *this; }
    S &operator = (S&&) { HAI; return *this; }
};

void v(S s) {}

void rv(S &&s) {
    v(s);
}

void rvm(S &&s) {
    v(std::move(s));
}

int main() {
    std::cout << "rv\n";
    rv(S{});
    std::cout << "rvm\n";
    rvm(S{});
}