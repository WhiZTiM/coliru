#include <functional>

template<typename T>
void foo(T obj)
{
    obj.bar();
}

struct X
{
    void bar() { }
};

int main()
{
    X x;
    foo(x); // Yep
    //foo(std::ref(x)); // Nope
}