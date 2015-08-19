#include <iostream>

struct X {
    X& operator=(const X&) = delete;
    X& operator=(X&&) = delete;

    static X make() {
        return X();
    }
    
    void increment() {
        ++i;
    }
  
    void print() {
        std::cout << i << std::endl;
    }

private:
    X() = default;
    X(const X&) = default;
    X(X&&) = default;

    int i = 0;
};

int main() {
// Area of edit - BEGIN

// X::print() output: 1
// no cast or lambda allowed
// <your code>

// Area of edit - END
}
