#include <iostream>

void foo() { std::cout << "No, Alex. It isn't.\n"; }
void bar() { return foo(); }

int main()
{
    bar();
}