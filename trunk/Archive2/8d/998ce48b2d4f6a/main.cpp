#include <iostream>

template<class C, class F>
auto test(C c, F f) -> decltype((void)(c.*f)(), void())
    { std::cout << "hi\n"; }

struct X { int f() { return 42; } };

struct Y { double f(int) { return 3.14; } };

int main()
{
    X x;
    test(x, &X::f);
    Y y;
    test(y, &Y::f);
    test(y, 99);
}
