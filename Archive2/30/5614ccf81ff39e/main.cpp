#include <iostream>

int f()
{
    static const char c [[gnu::unused]] = (std::cout << "ping\n", '\0');
    return 42;
}

int main()
{
    f();
    f();
    f();
}
