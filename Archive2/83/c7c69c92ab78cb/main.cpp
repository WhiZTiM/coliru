#include <iostream>
using namespace std;
struct Base {
    Base (int a = 0, int b = 1) { cout << "Base" << a << b << endl; }
};
struct Derived : Base {
    Derived(int c) { cout << "Derived" << c << endl; }
    using Base::Base;
};
int main()
{
    Derived d1(3);
    Derived d2(4,5);
}