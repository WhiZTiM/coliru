#include <iostream>
#include <string>
#include <vector>

struct A {
    template <class T>
    void fun(T t);
};

template <class T>
void A::fun(T t) {
    std::cout << t;
}

int main()
{
    A a;
    a.fun(5);
}
