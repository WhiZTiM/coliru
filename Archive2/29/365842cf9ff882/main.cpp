#include <iostream>
using namespace std;

class A
{
    int id;
public:
    A(int i): id(i) {}
    int callFoo() { cout << "in A callFoo()" << endl; return foo(); }
    virtual int foo() = 0;
};

class B: public A
{
public:
    B(): A(callFoo()) {}
    int foo() { cout << "in B foo()" << endl;return 3; }
};

int main() {
    B b; // <-- this should call a pure virtual function
    cout << b.callFoo() << endl;
    return 0;
}