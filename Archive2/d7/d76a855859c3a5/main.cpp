#include <iostream>

struct X { X(int n) : n_(n) { } int n_; };

template <typename T>
void f(T& x, int n)
{
    x.~T();
    new (&x) T(n);
}

int main()
{
    X x(12);
	f(x, 42);
	std::cout << x.n_ << '\n';
}