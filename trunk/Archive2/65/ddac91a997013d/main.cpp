#include <iostream>
#include <cmath>
using namespace std;

class Foo
{
    int i;
public:
    Foo(int ii) : i(ii) { cout << "in Foo constructor\n"; }
    Foo(const Foo & f) : i(f.i) { cout << "in Foo copy constructor\n"; }
    Foo& operator=(const Foo & f) { i = f.i; cout << "in Foo assignment\n"; return *this; }
};

class Bar
{
    Foo f;
public:
    Bar(Foo ff) : f(ff) { cout << "in Bar constructor\n"; }
    Bar(const Bar & b) : f(b.f) { cout << "in Bar copy constructor\n"; }
    Bar& operator=(const Bar & b) { f = b.f; cout << "in Bar assignment\n"; return *this; }
};

int main() {
    Bar temp1(Foo(10));
    Bar temp2 = Foo(10);
    return 0;
}