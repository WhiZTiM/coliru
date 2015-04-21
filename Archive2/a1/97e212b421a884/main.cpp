#include <string>
#include <iostream>

auto foo (int x) { return x; }
const auto bar = [] (int x) { return x; };

int main ()
{
    foo (1);
    bar (1);
}