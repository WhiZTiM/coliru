#include <vector>
#include <iostream>

template<int& i> int f() { return i;}

int a = 0;
int main(int argc, char** argv) {
    std::cout << f<a>() << "\n";
    a = 1;
    std::cout << f<a>() << "\n";
    return 0;
}