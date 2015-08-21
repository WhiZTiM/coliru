#include <iostream>
#include <map>
#include <utility>

class Foo
{
private:
    int x;
public:
    Foo()               : x(0)     { std::cout << "Foo()"               << std::endl; }
    Foo(int x)          : x(x)     { std::cout << "Foo(int x)"          << std::endl; }
    Foo(const Foo& foo) : x(foo.x) { std::cout << "Foo(const Foo& foo)" << std::endl; }
    Foo(Foo&& foo)      : x(foo.x) { std::cout << "Foo(Foo&& foo)"      << std::endl; }
    
    Foo& operator=(const Foo&  foo) { x = foo.x; std::cout << "operator=(const Foo& foo)" << std::endl; return *this; };
    Foo& operator=(Foo&& foo)       { x = foo.x; std::cout << "operator=(Foo&& foo)"      << std::endl; return *this; };
};

int main()
{
    std::map<int, Foo> map;
    map[0] = std::move(Foo(3));
}
