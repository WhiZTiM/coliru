#include <iostream>
#include <string>
#include <vector>

template<typename... Args> inline void pass(Args&&...) {}

template<class T>
int printc()
{
    std::cout << T{} << std::endl;
    return 0;
}

template<class... T>
void lol()
{
    pass( printc<T>()... );
}


int main()
{
    lol();
}
