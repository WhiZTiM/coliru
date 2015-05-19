#include <memory>
#include <iostream>

int main() {
    auto foo = std::make_unique<int>(2);
    auto bar = std::move(foo);
    std::cout << *foo;
}