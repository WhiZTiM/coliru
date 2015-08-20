#include <iostream>
#include <string>
#include <functional>

class Foo
{
    private:
        int x;
    public:
        Foo(int x) : x(x) {};
        void bar() { std::cout << x << std::endl; }
};

int main()
{
    Foo f(5);
    auto func = &Foo::bar;
    auto func2 = std::bind(func, f);
    func2();
}
