#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include <iterator>

struct X { virtual void foo()=0; };
void X::foo() { std::cout << "hello world\n"; }

struct Y:X { virtual void foo(){ X::foo(); } };

int main() {
    Y{}.foo();
}
