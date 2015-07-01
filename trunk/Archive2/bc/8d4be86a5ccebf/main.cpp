#include <iostream>
using namespace std;

class F {
public:
    F() { cout << "ctor1\n"; }
    F(int) { cout << "ctor2\n"; }
    ~F() { cout << "dtor\n"; }
};
class Foo {
    F f;
public:
    Foo() : f() { cout << "1\n"; }
    Foo(int i) { Foo(); cout << "2\n"; }
};

int main() {
    Foo object(1); 
    return 0;
}