#include <iostream>
#include <string>
#include <vector>

// begin of header file

struct A {
    template <class T>
    void fun(T t);
};

template <class T>
void A::fun(T t) {
    std::cout << t;
}

// end of header file

int main()
{
    A a;
    a.fun(5);
}
