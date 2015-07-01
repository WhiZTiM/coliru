#include <iostream>
#include <cmath>
using namespace std;

class A
{
public:
    A(int i) {}
};

template <typename T>
class B : public A
{
public:
    B(int i) : A(i) {}
    T test() {return T(10);}
};

class C : public B<C>
{
public:
    C(int i) : B(i) {}
};

int main()
{
    C c(5);
}