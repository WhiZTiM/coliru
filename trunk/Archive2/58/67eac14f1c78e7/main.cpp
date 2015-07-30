#include <initializer_list>

struct S {
    S(std::initializer_list<double>) {} // #1
    S(std::initializer_list<int>);    // #2
};
S s1 = { 1.f }; // invoke #1 

int main() {}