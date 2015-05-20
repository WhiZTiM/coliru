#include <iostream>
#include <string>

struct X { X(std::string s) : s_(s) { } std::string s_; };

template <typename T>
void f(T x, const char* p)
{
    x.~T();
    new (&x) T(p);
}

int main()
{
    X x("hello");
	f<X&>(x, "goodbye");
	std::cout << x.s_ << '\n';
}