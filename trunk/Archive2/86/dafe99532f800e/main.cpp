#include <iostream>
#include <functional>
#include <memory>

typedef std::function<int(std::unique_ptr<int>&&)> func;

int impl(std::unique_ptr<int>&& x) {
    return *x;
}

int main() {
	func f = impl;
    
    auto val = std::make_unique<int>(7);
    std::cout << f(std::move(val)) << std::endl;
}