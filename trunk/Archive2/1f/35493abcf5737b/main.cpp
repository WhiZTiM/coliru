#include <iostream>
#include <string>
#include <utility>

class A {
public:
    A(int x ) { }
};
        
void foo(const A&  a) { std::cout << "Reference" << std::endl; }

void foo(      A&& a) { std::cout << "Move" << std::endl; }

struct Bar
{
    template <typename T,
              typename = decltype(foo(std::forward<T>(std::declval<T&>())))>
    Bar(T&& a) {
        foo(std::forward<T>(a));
    }
};

void test(Bar x) { std::cout << "Bar" << std::endl; }

void test(std::string x) { std::cout << "String: " << x << std::endl; }
    
int main() {
    A a(1);
    Bar b(a);
    Bar c(A(1));
    Bar d(std::move(a));
    
    test("Hallo");
    test(A(1));
    test(b);
}