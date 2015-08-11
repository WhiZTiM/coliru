#include <iostream>
#include <string>
#include <vector>

template<typename T>
struct Foo {
    virtual void bar(T const &t) = 0;
};

struct Boo : Foo<int> {
    void bar(int const &t) { std::cout << "#: " << t << std::endl; }
};

int main()
{
    Foo<int>* foo = new Boo;
    foo->bar(5);
}
