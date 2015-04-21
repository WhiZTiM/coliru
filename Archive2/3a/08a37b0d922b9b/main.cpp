#include <iostream>

void(*f())()
{
    std::cout << __PRETTY_FUNCTION__;
    return nullptr;
}

int main() {
    f();
}