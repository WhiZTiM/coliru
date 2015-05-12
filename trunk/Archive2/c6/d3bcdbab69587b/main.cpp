#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct A{
    A(){cout << "lofazs" << endl;}
    ~A(){cout << "~A() D-tor" << endl;}
};

struct B : public A{
    B(){}
    ~B(){cout << "~B() D-tor" << endl;}
};

int main()
{
    B b;
}
