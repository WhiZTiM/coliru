#include <iostream>

struct int_wrap {
    const int wrapped;
    int_wrap(int x)
        : wrapped(x)
        {}
        
    int_wrap operator^(int_wrap const& rhs) {
        return (*this);
    }
    
    operator int() { return wrapped; }
};

int main() {
    auto y = int_wrap(1);
    int x = y ^  y;
    std::cout << "       " << x;
}