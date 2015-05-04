#include <iostream>
using namespace std;

struct A {
    A() = default;
    A(const A&) = delete;
    A(const A&&) = delete;
};

A fun() {
    A a;
    return a;
}

int main () {
   auto a = fun();
}