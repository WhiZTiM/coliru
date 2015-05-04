#include <iostream>
using namespace std;

struct A {
    A() = default;
    A(const A&) = delete;
    A(const A&&) = delete;
};

A &fun() {
    A *a = new A;
    return *a;
}

int main () {
   const auto &a = fun();
}