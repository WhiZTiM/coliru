#include <iostream>
#include <string>
#include <vector>

void foo(std::string&) { std::cout << "This one"; }
void foo(const std::string&) {std::cout << "The other one";}

int main() {
    const std::string x;
    foo(x);
}