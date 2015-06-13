#include <iostream>

template<typename... Args>
void test(Args&... args)
{
    ((std::cin >> args) , ...);
    ((std::cout << args) , ...);
}

int main()
{
    int i, j, k, l, m;
    test(i, j, k, l, m);
}
