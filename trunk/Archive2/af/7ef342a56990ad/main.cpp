#include <functional>
#include <iostream>
#include <string>

int func(std::string) { return 0; }
int func(int i) { return i; }

int main() {
    using namespace std::placeholders;
    auto f = std::bind((int(*)(int))func, _1);
    std::cout << f(1);
}