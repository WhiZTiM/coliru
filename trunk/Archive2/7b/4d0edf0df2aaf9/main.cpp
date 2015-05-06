#include <iostream>
#include <functional>
#include <future>
#include <string>
#include <utility>

int main() {
    auto lambda = [] (std::string&& message) {
        std::cout << message << std::endl;
    };
    auto bound = std::bind(lambda, std::bind(static_cast<std::string&&(*)(std::string&)>(std::move),
                                             std::string{"hello world"}));
    auto future = std::async(bound);
    future.get();
}
