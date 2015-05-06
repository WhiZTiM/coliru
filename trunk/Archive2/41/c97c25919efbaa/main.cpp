#include <iostream>
#include <functional>
#include <future>
#include <string>


int main() {
    auto lambda = [] (std::string&& message) {
        std::cout << message << std::endl;
        };
    auto future = std::async(lambda, std::string{"hello world"});
    future.get();
}