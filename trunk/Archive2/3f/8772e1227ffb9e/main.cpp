#include <sstream>
#include <iostream>
#include <string>
#include <utility>
#include <functional>
#include <vector>
struct A {
    int propose();
};

struct A1 { // : A {
    int propose(int);
    int propose();// using A::propose;
};

struct B1 { // : A1 {
protected:
    int propose(int);
    int propose();
//    using A1::propose;
public:
    int propose();
//    using A::propose;
};

int main() {
    B1().propose();
}
