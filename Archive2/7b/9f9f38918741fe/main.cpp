#include <iostream>

void foo()
{
}

template<typename T>
T bar()
{
    return foo();
}

void baz()
{
    return foo();
}
 
int main() {
    bar<void>();
    baz();
    std::cout << "Success" << std::endl;
}