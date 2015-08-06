#include <iostream>
struct X{
    X(){}
//  X(X&&) = default;
    X(X&);
//  X& operator=(const X& x);
//  ~X() = default;
};
X f() { X x; return x; }
X y = f();
X z = X();
int main(){}
