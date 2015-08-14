#include <iostream>
void foo(const std::string &) {}
int main() 
{
    foo(false);
}