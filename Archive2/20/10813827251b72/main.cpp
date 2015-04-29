#include <utility>
#include <iostream>

struct other {};
struct noisy {
    noisy() { std::cout << "ctor\n"; }
    ~noisy() { std::cout << "dtor\n"; }
    noisy(noisy&&) { std::cout << "move ctor\n"; }
    noisy(noisy const&) { std::cout << "copy ctor\n"; }
    void operator=(noisy&&) { std::cout << "move asgn\n"; }
    void operator=(noisy const&) { std::cout << "copy asgn\n"; }
    
    noisy(other&&) { std::cout << "other move ctor\n"; }
    noisy(other const&) { std::cout << "other copy ctor\n"; }
};

noisy test() {
    other o;
    return o;
}

int main() {
    test();
}