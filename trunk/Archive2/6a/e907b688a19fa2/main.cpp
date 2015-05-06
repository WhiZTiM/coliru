#include <iostream>
#include <functional>
#include <future>
#include <string>


int main() {
    auto lambda = [] (std::string&& message) {
        std::cout << message << std::endl;
    };
    auto bound = std::bind(lambda, std::string{"hello world"});
    bound();
}