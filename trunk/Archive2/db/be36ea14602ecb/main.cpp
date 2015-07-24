#include <iostream>

const int size = 42;
int A<:::size:>;

int main()
{
    std::cout << sizeof A << '\n';
    return 0;
}
