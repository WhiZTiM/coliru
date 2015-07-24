#include <iostream>

int main() {
    void(*p)() = [&]{};
    (void)p;
}