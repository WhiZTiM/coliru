#include <iostream>
#include <string>


int main() {
    auto lambda = [message = std::string{"hello world"}] () {
        std::cout << message << std::endl;
    };
    lambda();
}