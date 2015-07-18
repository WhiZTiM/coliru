#include <iostream>

template<int& a>
void f() { std::cout << a << "\n"; }

int cool;
int main(int argc, char** argv) {
    cool = 0; f<cool>();
    cool = 1; f<cool>();
    return 0;
}