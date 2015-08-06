#include <functional>
#include <iostream>
#include <memory>
#include <string>

void runFunc(std::function<void()>&& f) {
    auto ff = std::move(f);
    ff();
}

int main() {
    auto ptr = std::make_unique<std::string>("hello world\n");
    runFunc([captured_ptr = std::move(ptr)]() {
        std::cout << *captured_ptr;
    });
}