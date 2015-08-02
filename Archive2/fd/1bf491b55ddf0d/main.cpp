#include <iostream>
struct S {
    S() = default;
    S(const S&) { std::cout << "copy ctor" << '\n'; }
    S(S&&) { std::cout << "move ctor" << '\n'; }
};

int main() {
    S s = S(); 
}