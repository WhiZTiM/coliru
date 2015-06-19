#include <iostream>

class A
{
public:
    void foo(){ std::cout << &a << '\n'; }
private:
    static const int a = 1;
};

int main ()
{
    A a;
    a.foo();
}
