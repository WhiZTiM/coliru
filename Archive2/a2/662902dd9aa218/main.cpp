#include <stdio.h>

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

typedef std::function<void()> fn;

int f2(fn f) {
    f();
    return 0;
}

class Foo {
public:
 Foo() : x(f2([this]() { myf(); return 0;})) {
 }

void myf() {
     printf("Hello world\n");
 }
 int x;
};

class Bar : public Foo {
    void myf() {
     printf("Hello world from Bar.\n");
    }
};

int main()
{
    Bar ff;
}
