#include <iostream>
#include <string>
#include <vector>

void foo(int * bar)
{
    int foobar = 10;
    bar = &foobar;
}

int main()
{
    int x = 5;
    foo(&x);
    std::cout << x;
}
