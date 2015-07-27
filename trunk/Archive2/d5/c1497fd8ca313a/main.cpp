#include <iostream>
#include <string>
#include <vector>

void foo(std::string&) { std::cout << "This one"; }
void foo(const std::string&) {}

int main() {
    std::string x;
    foo(x);
}