#include <string>
#include <iostream>

int main() {
    std::string a = "hello";
    std::string b = '!' + a; // no problem

    std::cout << b;
}
