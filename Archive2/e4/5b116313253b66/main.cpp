#include <vector>
#include <iostream>

void foo (std::nullptr_t) { std::cout << "a" << std::endl; }
void foo (std::vector<int>::value_type*) { std::cout << "b" << std::endl; }

int main ()
{
    foo (nullptr);
    foo (&std::vector<int>{1,2,3}.front());
}