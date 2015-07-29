// For std::function
#include <functional>

// For std::iostream
#include <iostream>

// For std::unique_ptr
#include <memory>

auto make_foo() {
    auto x = std::make_unique <int> (3);
    return [x=std::move(x)]() {
        std::cout << *x << std::endl;
    };
}

int main() {
    auto x = std::make_unique <int> (3);
    auto foo = [x=std::move(x)]() {
        std::cout << *x << std::endl;
    };
    foo();
    make_foo()();
}
