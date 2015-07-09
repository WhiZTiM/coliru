#include <iostream>
#include <string>
#include <vector>

struct foo {
    ~foo() noexcept(false) {
        throw 42;
    }
};

int main() {
    try {
        foo _;
        return 0;
    } catch (...) {
        std::cout << "caught" << std::endl;
    }
}
